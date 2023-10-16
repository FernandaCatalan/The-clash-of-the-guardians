#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura para representar una carta
typedef struct Carta {
    char nombre[50];
    char tipo[50];
    int vidac;
    int ataque;
    int defensa;
    struct Carta* next;
} Carta;

// Estructura para representar un jugador
typedef struct Jugador {
    char nombre[50];
    int vida;
} Jugador;

// Estructura para representar una entrada en el historial
typedef struct HistorialEntry {
    char accion[100];
    struct HistorialEntry* next;
} HistorialEntry;

// Función para crear una carta
Carta* crearCarta(const char* nombre, const char* tipo, int vidac, int ataque, int defensa) {
    Carta* nuevaCarta = (Carta*)malloc(sizeof(Carta));
    strcpy(nuevaCarta->nombre, nombre);
    strcpy(nuevaCarta->tipo, tipo);
    nuevaCarta->vidac = vidac;
    nuevaCarta->ataque = ataque;
    nuevaCarta->defensa = defensa;
    nuevaCarta->next = NULL;
    return nuevaCarta;
}

// Función para agregar una carta a la lista
void agregarCarta(Carta** lista, Carta* nuevaCarta) {
    if (*lista == NULL) {
        *lista = nuevaCarta;
    } else {
        Carta* temp = *lista;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nuevaCarta;
    }
}

// Función para eliminar una carta por índice
void eliminarCartaPorIndice(Carta** lista, int indice) {
    if (indice < 0) {
        return;
    }
    if (indice == 0) {
        Carta* temp = *lista;
        *lista = (*lista)->next;
        free(temp);
    } else {
        Carta* temp = *lista;
        int i = 0;
        while (temp != NULL && i < indice - 1) {
            temp = temp->next;
            i++;
        }
        if (temp == NULL || temp->next == NULL) {
            return;
        }
        Carta* siguiente = temp->next->next;
        free(temp->next);
        temp->next = siguiente;
    }
}

// Función para contar las cartas en una lista
int contarCartas(Carta* lista) {
    int contador = 0;
    while (lista != NULL) {
        contador++;
        lista = lista->next;
    }
    return contador;
}

// Función para obtener una carta por índice
Carta* obtenerCartaPorIndice(Carta* lista, int indice) {
    int i = 0;
    while (lista != NULL) {
        if (i == indice) {
            return lista;
        }
        lista = lista->next;
        i++;
    }
    return NULL;
}

// Función para jugar una carta de la mano y eliminarla de la lista de cartas en mano
Carta* jugarCarta(Carta** lista, int indice) {
    Carta* carta = obtenerCartaPorIndice(*lista, indice - 1);
    if (carta != NULL) {
        eliminarCartaPorIndice(lista, indice - 1);
    }
    return carta;
}

// Función para imprimir una lista de cartas
void imprimirCartas(Carta* lista) {
    int i = 1;
    while (lista != NULL) {
        printf("%d. Nombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n", i, lista->nombre, lista->tipo, lista->vidac, lista->ataque, lista->defensa);
        lista = lista->next;
        i++;
    }
}

// Función para liberar la memoria de una lista de cartas
void liberarCartas(Carta** lista) {
    while (*lista != NULL) {
        Carta* temp = *lista;
        *lista = (*lista)->next;
        free(temp);
    }
}

// Función para agregar una entrada al historial de la partida
void agregarAlHistorial(HistorialEntry** historial, const char* accion) {
    HistorialEntry* nuevaEntrada = (HistorialEntry*)malloc(sizeof(HistorialEntry));
    strcpy(nuevaEntrada->accion, accion);
    nuevaEntrada->next = *historial;
    *historial = nuevaEntrada;
}

// Función para imprimir el historial de la partida
void imprimirHistorial(HistorialEntry* historial) {
    printf("Historial de la partida:\n");
    while (historial != NULL) {
        printf("%s\n", historial->accion);
        historial = historial->next;
    }
}

// Función para liberar la memoria del historial de la partida
void liberarHistorial(HistorialEntry** historial) {
    while (*historial != NULL) {
        HistorialEntry* temp = *historial;
        *historial = (*historial)->next;
        free(temp);
    }
}

// Función para repartir cartas al jugador y dejar el resto en la mesa
void repartirCartas(Carta** listaTodasCartas, Carta** listaManoJugador, Carta** listaMesa) {
    srand(time(NULL));

    *listaManoJugador = NULL;
    *listaMesa = NULL;

    int numCartasDisponibles = contarCartas(*listaTodasCartas);
    int numCartasEnMano = 0;

    if (numCartasDisponibles < 15) {
        printf("No hay suficientes cartas disponibles para repartir.\n");
        return;
    }

    while (numCartasEnMano < 15) {
        int cartaAleatoria = rand() % numCartasDisponibles;
        Carta* cartaElegida = obtenerCartaPorIndice(*listaTodasCartas, cartaAleatoria);

        if (cartaElegida == NULL) {
            // La carta elegida no es válida, sal del bucle
            break;
        }

        agregarCarta(listaManoJugador, cartaElegida);
        eliminarCartaPorIndice(listaTodasCartas, cartaAleatoria);

        numCartasEnMano++;
        numCartasDisponibles = contarCartas(*listaTodasCartas);
    }

    printf("Cartas repartidas al jugador:\n");
    imprimirCartas(*listaManoJugador);

    printf("Cartas restantes en la mesa:\n");
    imprimirCartas(*listaMesa);
}

// Función para que el jugador tome una carta de la mesa
void tomarCartaDeMesa(Carta** listaManoJugador, Carta** listaMesa) {
    int numCartasEnMesa = contarCartas(*listaMesa);

    if (numCartasEnMesa > 0) {
        printf("Cartas en la mesa:\n");
        imprimirCartas(*listaMesa);

        int opcionCarta;
        do {
            printf("Seleccione una carta para tomar (1-%d) o ingrese 0 para no tomar ninguna: ", numCartasEnMesa);
            scanf("%d", &opcionCarta);
        } while (opcionCarta < 0 || opcionCarta > numCartasEnMesa);

        if (opcionCarta > 0) {
            Carta* cartaElegida = jugarCarta(listaMesa, opcionCarta);
            agregarCarta(listaManoJugador, cartaElegida);
        }
    }
}

// Función para el turno de la máquina (jugada aleatoria)
void turnoMaquina(Carta* manoJugador, Carta** listaManoMaquina, HistorialEntry** historial) {
    int numCartasEnManoMaquina = contarCartas(*listaManoMaquina);
    if (numCartasEnManoMaquina > 0) {
        int cartaAleatoria = rand() % numCartasEnManoMaquina;
        Carta* cartaJugada = jugarCarta(listaManoMaquina, cartaAleatoria + 1); // +1 porque el índice es 1-based
        printf("La maquina juega la carta: %s\n", cartaJugada->nombre);
        char accion[100];
        sprintf(accion, "La maquina juega la carta: %s", cartaJugada->nombre);
        agregarAlHistorial(historial, accion);
    }
}

int main() {
    int opcion;
    Carta* listaCartas = NULL;
    HistorialEntry* historialPartida = NULL;

    // Crear un jugador con nombre y vida
    Jugador jugador;
    strcpy(jugador.nombre, "Messi");
    jugador.vida = 5;

    // Declarar las variables de manoJugador y manoMaquina
    Carta* manoJugador = NULL;
    Carta* manoMaquina = NULL;

    // Declarar variable mesa
    Carta* mesa = NULL;

    FILE* archivoCartas = fopen("file.txt", "r");
    if (archivoCartas == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Leer las cartas desde el archivo "file.txt" y almacenarlas en una lista
    char nombre[50];
    char tipo[50];
    int vidac, ataque, defensa;

    while (fscanf(archivoCartas, " %49[^,], %49[^,], %d, %d, %d\n", nombre, tipo, &vidac, &ataque, &defensa) == 5) {
        Carta* nuevaCarta = crearCarta(nombre, tipo, vidac, ataque, defensa);
        agregarCarta(&listaCartas, nuevaCarta);
    }

    fclose(archivoCartas); // Cierra el archivo después de leerlo

    do {
        printf("\nBienvenido a The Clash of the Guardians:\n");
        printf("Escoge que deseas hacer:\n");
        printf("1. Crear una nueva carta\n");
        printf("2. Jugar (Usuario vs. Maquina)\n");
        printf("3. Imprimir historial de la partida\n");
        printf("4. Salir\n");
        scanf("%d", &opcion);

        char nuevaNombre[50];
        char nuevaTipo[50];
        int nuevaVidaC, nuevaAtaque, nuevaDefensa;

        switch (opcion) {
            case 1: 
                // Solicitar al usuario ingresar los datos de la nueva carta
                printf("Ingrese el nombre de la carta: ");
                scanf(" %49s", nuevaNombre);

                printf("Ingrese el tipo de la carta: ");
                scanf(" %49s", nuevaTipo);

                printf("Ingrese los puntos de vida de la carta: ");
                scanf("%d", &nuevaVidaC);

                printf("Ingrese los puntos de ataque de la carta: ");
                scanf("%d", &nuevaAtaque);

                printf("Ingrese los puntos de defensa de la carta: ");
                scanf("%d", &nuevaDefensa);

                // Crear la nueva carta
                Carta* nuevaCarta = crearCarta(nuevaNombre, nuevaTipo, nuevaVidaC, nuevaAtaque, nuevaDefensa);
                agregarCarta(&listaCartas, nuevaCarta);

                // Abrir el archivo "file.txt" en modo de escritura (sobrescritura)
                FILE* archivoCartas = fopen("file.txt", "w");
                if (archivoCartas == NULL) {
                    printf("No se pudo abrir el archivo\n");
                    return 1;
                }

                // Escribir todas las cartas en el archivo
                Carta* cartaActual = listaCartas;
                while (cartaActual != NULL) {
                    fprintf(archivoCartas, "%s,%s,%d,%d,%d\n", cartaActual->nombre, cartaActual->tipo, cartaActual->vidac, cartaActual->ataque, cartaActual->defensa);
                    cartaActual = cartaActual->next;
                }

                // Cerrar el archivo
                fclose(archivoCartas);

                printf("Nueva carta creada con exito y guardada en el archivo.\n");
                break;

            case 2:
                printf("Repartiendo cartas...\n");
                repartirCartas(&listaCartas, &manoJugador, &mesa);

                printf("Comienza el juego: %s vs. Máquina\n", jugador.nombre);

                int turno = 0; // 0 para turno del jugador, 1 para turno de la máquina
                while (1) {
                    if (turno == 0) {
                        printf("\n%s, es tu turno:\n", jugador.nombre);
                        printf("Cartas en tu mano:\n");
                        imprimirCartas(manoJugador);

                        int accion;
                        do {
                            printf("Escoge una accion:\n");
                            printf("1. Jugar una carta\n");
                            printf("2. Tomar una carta de la mesa\n");
                            printf("3. Terminar turno\n");
                            scanf("%d", &accion);
                        } while (accion < 1 || accion > 3);

                        if (accion == 1) {
                            int indiceCarta;
                            do {
                                printf("Ingresa el numero de la carta que deseas jugar: ");
                                scanf("%d", &indiceCarta);
                            } while (indiceCarta < 1 || indiceCarta > contarCartas(manoJugador));

                            Carta* cartaJugada = jugarCarta(&manoJugador, indiceCarta);
                            printf("Juegas la carta: %s\n", cartaJugada->nombre);
                        } else if (accion == 2) {
                            tomarCartaDeMesa(&manoJugador, &mesa);
                        }

                        // Cambiar al turno de la máquina
                        turno = 1;
                    } else {
                        printf("\nTurno de la Maquina:\n");
                        turnoMaquina(manoJugador, &manoMaquina, &historialPartida);

                        // Cambiar al turno del jugador
                        turno = 0;
                    }

                    // Verificar si el juego ha terminado
                    if (jugador.vida <= 0 || (contarCartas(manoJugador) == 0 && contarCartas(manoMaquina) == 0)) {
                        printf("\n¡Fin del juego!\n");

                        if (jugador.vida <= 0) {
                            printf("¡Has perdido! La Maquina gana.\n");
                        } else if (contarCartas(manoJugador) == 0 && contarCartas(manoMaquina) == 0) {
                            printf("¡Empate! Ambos jugadores se quedaron sin cartas.\n");
                        } else {
                            printf("¡Has ganado! La Maquina se quedo sin cartas.\n");
                        }

                        // Imprimir el historial de la partida
                        imprimirHistorial(historialPartida);

                        // Liberar la memoria de las cartas
                        liberarCartas(&manoJugador);
                        liberarCartas(&manoMaquina);
                        liberarCartas(&listaCartas);
                        liberarCartas(&mesa);

                        // Liberar la memoria del historial
                        liberarHistorial(&historialPartida);

                        // Salir del juego
                        return 0;
                    }
                }
                break;

            case 3:
                imprimirHistorial(historialPartida);
                break;

            case 4:
                // Liberar la memoria de las cartas
                liberarCartas(&manoJugador);
                liberarCartas(&manoMaquina);
                liberarCartas(&listaCartas);
                liberarCartas(&mesa);

                // Liberar la memoria del historial
                liberarHistorial(&historialPartida);

                printf("Saliendo del juego...\n");
                return 0;

            default:
                printf("Opcion no valida. Por favor, selecciona una opcion valida.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}