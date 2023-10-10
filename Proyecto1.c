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

    return 0;
}