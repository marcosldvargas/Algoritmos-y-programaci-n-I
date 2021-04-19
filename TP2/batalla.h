#ifndef __BATALLA_H__
#define __BATALLA_H__
#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES 500
#define MAX_ENERGIA 12
#define ENERGIA_INICIAL 5
#define DEFENSIVA 'D'
#define OFENSIVA 'O'
#define CODIGO_HOMBRE 'H'
#define CODIGO_ELFO 'E'
#define CODIGO_ORCO 'O'
#define CODIGO_URUK 'U'
#define COSTO_ORCO 3
#define COSTO_HOMBRE 3
#define COSTO_URUK 8
#define COSTO_ELFO 8
#define FILA_INICIO_ORCO 0
#define MINIMA_COLUMNA 0
#define SI 1
#define NO 2
#define CANTIDAD_INICIAL_PERSONAJES 3
#include <stdbool.h>

typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
	bool esta_vivo;

} personaje_t;

typedef struct juego {
	char terreno [MAX_TERRENO_FIL][MAX_TERRENO_COL];
	personaje_t rohan [MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	personaje_t isengard [MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	int cant_energia_rohan;
	int cant_energia_isengard;
	int cantidad_jugadores;
	char bando_maquina;
	char bando_jugador_uno;
 	char bando_jugador_dos;

} juego_t;

void inicializar_juego (juego_t* juego);

void posicionar_personaje (juego_t* juego, personaje_t personaje);

void jugar (juego_t* juego, char bando, int posicion_personaje);

void limpiar_personajes_muertos (juego_t* juego);

void mostrar_terreno (juego_t* juego);

void actualizar_interfaz (juego_t* juego);

#endif