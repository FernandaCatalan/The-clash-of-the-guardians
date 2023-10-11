#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//Struct para representar una carta
typedef struct Carta {
    char nombre[50];
    char tipo[50];
    int ataque;
    int vidac;
    int defensa;
    struct Carta* next;
} Carta;

//Struct para representar un jugador
typedef struct Jugador {
    char nombre[50];
    int vida;
} Jugador;

//Struct para representar una entrada en el historial
typedef struct HistorialEntry {
    char accion[100];
    struct HistorialEntry* next;
} HistorialEntry;

//Función para crear una carta
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

//Función para agregar una carta a la lista
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

//Función para eliminar una carta por índice
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

//Función para contar las cartas en una lista
int contarCartas(Carta* lista) {
    int contador = 0;
    while (lista != NULL) {
        contador++;
        lista = lista->next;
    }
    return contador;
}

//Función para obtener una carta por índice
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

//Función para jugar una carta de la mano y eliminarla de la lista de cartas en mano
Carta* jugarCarta(Carta** lista, int indice) {
    Carta* carta = obtenerCartaPorIndice(*lista, indice - 1);
    if (carta != NULL) {
        eliminarCartaPorIndice(lista, indice - 1);
    }
    return carta;
}

//Función para imprimir una lista de cartas
void imprimirCartas(Carta* lista) {
    int i = 1;
    while (lista != NULL) {
        printf("%d. Nombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n", i, lista->nombre, lista->tipo, lista->vidac, lista->ataque, lista->defensa);
        lista = lista->next;
        i++;
    }
}

//Función para liberar la memoria de una lista de cartas
void liberarCartas(Carta** lista) {
    while (*lista != NULL) {
        Carta* temp = *lista;
        *lista = (*lista)->next;
        free(temp);
    }
}

//Función para agregar una entrada al historial de la partida
void agregarAlHistorial(HistorialEntry** historial, const char* accion) {
    HistorialEntry* nuevaEntrada = (HistorialEntry*)malloc(sizeof(HistorialEntry));
    strcpy(nuevaEntrada->accion, accion);
    nuevaEntrada->next = *historial;
    *historial = nuevaEntrada;
}

//Función para imprimir el historial de la partida
void imprimirHistorial(HistorialEntry* historial) {
    printf("Historial de la partida:\n");
    while (historial != NULL) {
        printf("%s\n", historial->accion);
        historial = historial->next;
    }
}

//Función para liberar la memoria del historial de la partida
void liberarHistorial(HistorialEntry** historial) {
    while (*historial != NULL) {
        HistorialEntry* temp = *historial;
        *historial = (*historial)->next;
        free(temp);
    }
}

//Función para repartir cartas al jugador y dejar el resto en la mesa
void repartirCartas(Carta** listaTodasCartas, Carta** listaManoJugador, Carta** listaMesa){
    srand(time(NULL));

    //Inicializar listas de manoJugador y listaMesa
    *listaManoJugador = NULL;
    *listaMesa = NULL;

    int numCartasDisponibles = contarCartas(listaTodasCartas);
    int numCartasEnMano = 0;

    //Darle al jugador las 15 cartas
    while (numCartasEnMano < 15 && numCartasDisponibles > 0) {
        int cartaAleatoria = rand() % numCartasDisponibles;
        Carta* cartaElegida = obtenerCartaPorIndice(*listaTodasCartas, cartaAleatoria);

        //Mover la carta elegida a la mano del jugador
        agregarCarta(listaManoJugador, cartaElegida);

        //Eliminar la carta elegida de la lista de todas las cartas
        eliminarCartaPorIndice(listaTodasCartas, cartaAleatoria);

        numCartasEnMano++;
        numCartasDisponibles--;
    }

    //Permitir al jugador elegir 3 cartas de las 15 para mantener en la mano
    printf("Seleccione 3 cartas para mantener en la mano:\n");
    for (int i = 0; i < 3; i++) {
        printf("Carta %d: ", i + 1);
        int opcionCarta;
        do {
            scanf("%d", &opcionCarta);
        } while (opcionCarta < 1 || opcionCarta > 15);

        //Mover la carta seleccionada de la mano a la mesa
        Carta* cartaSeleccionada = jugarCarta(listaManoJugador, opcionCarta);
        agregarCarta(listaMesa, cartaSeleccionada);
    }
    
}

//Función para que el jugador tome una carta de la mesa
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

//Función para el turno de la máquina (jugada aleatoria)
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

    //Crear un jugador con nombre y vida
    Jugador jugador;
    strcpy(jugador.nombre, "Messi");
    jugador.vida = 5;

     //Declarar las variables de manoJugador y manoMaquina
    Carta* manoJugador = NULL;
    Carta* manoMaquina = NULL;

    //Declarar variable mesa
    Carta* mesa = NULL;


    //Leer las cartas desde el archivo "file.txt" y almacernarlas en una lista
    FILE* archivoCartas = fopen("file.txt", "r");
    if(archivoCartas == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    char nombre[50];
    char tipo[50];
    int vidac, ataque, defensa;

    while (fscanf(archivoCartas, " %49[^,], %49[^,], %d, %d, %d\n", nombre, tipo, &vidac, &ataque, &defensa) == 5) {
        Carta* nuevaCarta = crearCarta(nombre, tipo, vidac, ataque, defensa);
        agregarCarta(&listaCartas, nuevaCarta);
    }

    fclose(archivoCartas);

    do {
        printf("\nBienvenido a The clash of the guardians:\n");
        printf("Escoge que deseas hacer: \n");
        printf("1. Crear una nueva carta\n");
        printf("2. Jugar (Usuario vs. Maquina)\n");
        printf("3. Imprimir historial de la partida\n");
        printf("4. Salir\n");
        scanf("%d", &opcion);    

        switch (opcion)
        {
            case 1:
                //Solicitar al usuario ingresar los datos de la nueva carta
                printf("Ingrese el nombre de la carta: ");
                scanf(" %49s", nombre);

                printf("Ingrese el tipo de la carta: ");
                scanf(" %49s", tipo);

                printf("Ingrese los puntos de vida de la carta: ");
                scanf("%d", &vidac);

                printf("Ingrese los puntos de ataque de la carta: ");
                scanf("%d", &ataque);

                printf("Ingrese los puntos de defensa de la carta: ");
                scanf("%d", &defensa);

                //Crear la nueva carta
                Carta* nuevaCarta = crearCarta(nombre, tipo, vidac, ataque, defensa);

                //Agregar la nueva carta a la lista del file.txt
                agregarCarta(&listaCartas, nuevaCarta);
                
                printf("Nueva carta creada con exito\n");
                break;
        
            case 2:
                //Repartir cartas al jugador y dejar el resto en la mesa al inicio
                repartirCartas(&listaCartas, &manoJugador, &mesa);

                printf("Comienza el juego: %s vs. Maquina\n", jugador.nombre);

                int turno = 0; //0 para turno del jugador, 1 para turno de la máquina
                while (1) {
                    if (turno == 0) {
                        //Turno del jugador
                        printf("\nTurno de %s. Cartas en la mano:\n", jugador.nombre);
                        imprimirCartas(manoJugador);

                        //El jugador decide si toma una carta de la mesa
                        tomarCartaDeMesa(&manoJugador, &mesa);

                        //El jugador elige una carta para jugar
                        int opcionCarta;
                        do {
                            printf("Seleccione una carta para jugar (1-%d): ", contarCartas(manoJugador));
                            scanf("%d", &opcionCarta);
                        } while (opcionCarta < 1 || opcionCarta > contarCartas(manoJugador));

                        //El jugador juega la carta seleccionada
                        Carta* cartaJugada = jugarCarta(&manoJugador, opcionCarta);
                        printf("%s juega la carta: %s\n", jugador.nombre, cartaJugada->nombre);

                        //La máquina juega su turno
                        turnoMaquina(manoJugador, &manoMaquina, &historialPartida);
                    } else {
                        //Turno de la máquina
                        printf("\nTurno de la maquina.\n");
                        turnoMaquina(manoJugador, &manoMaquina, &historialPartida);
                    }

                    //Verificar si hay un ganador o continuar
                    if (contarCartas(manoJugador) == 0 || contarCartas(manoMaquina) == 0) {
                        printf("Fin del juego.\n");

                        if (contarCartas(manoJugador) == 0) {
                            printf("¡La maquina gana!\n");
                        } else {
                            printf("¡%s gana!\n", jugador.nombre);
                        }

                        //Mostrar el historial de la partida
                        imprimirHistorial(historialPartida);

                        //Liberar memoria de las manos y el historial
                        liberarCartas(&manoJugador);
                        liberarCartas(&manoMaquina);
                        liberarCartas(&mesa);
                        liberarHistorial(&historialPartida);
                        break;
                    }

                    //Cambiar el turno
                    turno = 1 - turno;
                }
                break;

            case 3:
                //Imprimir historial
                printf("Historial de la partida:\n");
                imprimirHistorial(historialPartida);
                break;

            case 4:
                printf("¡Hasta pronto, %s!\n", jugador.nombre);
                break;
        
            default:
                printf("Opcion no valida. Por favor, seleccione una valida\n");
                break;
       
        }

    }while(opcion != 4);

    //Liberar memoria de las cartas restantes
    liberarCartas(&listaCartas);

    return 0;
}