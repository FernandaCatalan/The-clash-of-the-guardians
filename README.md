# Proyecto1
 
## Problematica
Como primer proyecto de Algoritmos y estructuras de datos debiamos crear un juego de cartas donde el usuario podia: Crear una carta nueva, jugar contra la maquina, ver el historial y salir del juego. 

## Link al video
https://youtu.be/WKyzeT27-rg

### Detalles
Cada carta eran unos guardianes lo cuales tenian atributos como: Nombre, Tipo, Vida, Ataque y Defensa, el primer que le reste vida a los otros guardianes, ya sea los del jugador o la maquina, gana.

## typedef struct 
De este tipo de estructura hay para Carta, donde se representa la informacion de las cartas, Jugador, donde representa la informacion del jugador y HistorialEntry, donde se representa la entrada del historial.

## crearCarta();
Esta funcion es para crear una carta nueva a base de pedir informacion al usuario. Solicitando: Nombre, Tipo, Vida, Ataque y Defensa. 

## agregarCarta();
Esta funcion es para añadir la carta creada al archivo "file.txt".

## eliminarCartaPorIndice();
Es para eliminar una carta que ya no sea necesaria en la lista de cartas.

## jugarCarta();
Esta funcion es para jugar una carta que este en mano, para luego eliminarla de las cartas en mano que tenga el jugador con la funcion eliminarCartaPorIndice();.

## imprimirCartas();
Esta funcion es para imprimir las cartas existentes.

## liberarCartas();
Esta funcion es para eliminar la memoria en la lista de cartas.

## agregarAlHistorial();
Esta funcion es para añadir las partidas a la entrada del historial.

## imprimirHistorial();
Esta funcion es para imprimir el historial de partidas que exista.

## liberarHistorial();
Esta funcion es para que el historial que exista al cerrar el programa se borre.

## repartirCartas();
Esta funcion es para repartir cartas entre el jugador, la maquina y el resto dejarla en la mesa, esta funcion no me funciono del todo bien y se queda sin hacer nada.

## tomarCartaDeMesa();
Esta funcion es para que el jugador pueda decidir si tomar una de las 12 cartas que deja en la mesa o dejarla en cada una de las rondas que juegue.

## turnoMaquina();
Esta funcion es para que la maquina juegue de manera al azar basado en un random. 







