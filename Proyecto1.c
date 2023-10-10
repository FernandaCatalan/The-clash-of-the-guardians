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

int main() {
    int opcion;
    //Crear un jugador con nombre y vida
    Jugador jugador;
    strcpy(jugador.nombre, "Messi");
    jugador.vida = 5;

    //Leer las cartas desde el archivo "file.txt" y almacernarlas en una lista
    FILE* archivoCartas = fopen("file.txt", "r");
    if(archivoCartas == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    fclose(archivoCartas);

    do {
        printf("\nMenú:\n");
        printf("1. Crear una nueva carta\n");
        printf("2. Jugar (Usuario vs. Máquina)\n");
        printf("3. Imprimir historial de la partida\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);    

        switch (opcion)
        {
            case 1:
                //Solicitar al usuario ingresar los datos de la nueva carta
            
                //Crear la nueva carta

                //Agregar la nueva carta a la lista del file.txt
            
                printf("Nueva carta creada con exito\n");
                break;
        
            case 2:
                //Repartir las cartas

                //Juego
                break;

            case 3:
                //Imprimir historial
                printf("Historial de la partida:\n");
                break;

            case 4:
                printf("¡Hata pronto, %s!\n", jugador.nombre);
                break;
        
            default:
                printf("Opcion no valida. Por favor, seleccione una valida\n");
                break;
       
        }

    }while(opcion != 4);

    // Liberar memoria de las cartas restantes
    liberarCartas(&listaCartas);

    return 0;
}