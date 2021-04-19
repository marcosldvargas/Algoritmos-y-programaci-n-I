#include <stdio.h>
#include <stdlib.h>
#include "batalla.h"

const int FILA_INICIO_HOMBRE = MAX_TERRENO_FIL - 1;
const int LLEGADAS_PARA_GANAR = 3;

//Recibe el juego inicializado.
personaje_t generar_personaje_maquina (juego_t* juego){

	personaje_t hombre;
	personaje_t orco;

	(hombre.codigo) = CODIGO_HOMBRE;
	(hombre.vida) = 100 - juego->plus_rohan;
	(hombre.ataque) = 50 + juego->plus_rohan;
	(hombre.esta_vivo) = true;
	(hombre.fila) = FILA_INICIO_HOMBRE;

	(orco.codigo) = CODIGO_ORCO;
	(orco.vida) = 100 - juego->plus_isengard;
	(orco.ataque) = 50 + juego->plus_isengard;
	(orco.esta_vivo) = true;
	(orco.fila) = FILA_INICIO_ORCO;

	if ((juego->bando_maquina) == DEFENSIVA){
		do{
		(hombre.columna) = rand () %(MAX_TERRENO_COL-1) +MINIMA_COLUMNA;
		} while (juego->terreno[hombre.fila][hombre.columna] == CODIGO_HOMBRE);
		return (hombre);
	}else {
		do{
		(orco.columna) = rand () %(MAX_TERRENO_COL-1) +MINIMA_COLUMNA;
		} while (juego->terreno[orco.fila][orco.columna] == CODIGO_HOMBRE);
		return (orco);
	}
}
//Personaje con todos sus campos correctamente cargados.

//Recibe el juego inicializado.
personaje_t generar_personaje_rohan (juego_t* juego){

	personaje_t elfo;
	personaje_t hombre;
	
	char respuesta_rohan;

	(elfo.codigo) = CODIGO_ELFO;
	(elfo.vida) = 200 - juego->plus_rohan;
	(elfo.ataque) = 10 + juego->plus_rohan;
	(elfo.esta_vivo) = true;

	(hombre.codigo) = CODIGO_HOMBRE;
	(hombre.vida) = 100 - juego->plus_rohan;
	(hombre.ataque) = 50 + juego->plus_rohan;
	(hombre.esta_vivo) = true;
	(hombre.fila) = FILA_INICIO_HOMBRE;

	do {
		printf("\nQuéres posicionar un elfo (E) o un hombre (H)? Respondé con su respectivo código en mayúscula por favor.\n");
		scanf(" %c", &respuesta_rohan);

		if ((respuesta_rohan == CODIGO_ELFO) && (((juego->cant_energia_rohan) - COSTO_ELFO) < 0)){
			printf("Lo siento, no tenés suficiente energía para crear un elfo.\n");
		}
	} while (((respuesta_rohan != CODIGO_ELFO) && (respuesta_rohan != CODIGO_HOMBRE)) || ((respuesta_rohan == CODIGO_ELFO) && (((juego->cant_energia_rohan) - COSTO_ELFO) < 0)));

	if (respuesta_rohan == CODIGO_ELFO){	
		do {
			printf("\nNumero de fila?\n");
			scanf("%i", &(elfo.fila));
			if (((elfo.fila) <= (MAX_TERRENO_FIL / 2)) || ((elfo.fila) >= (FILA_INICIO_HOMBRE))){
				printf("Lo siento no podes ubicar al elfo en esa fila.\n");
			}
		} while (((elfo.fila) <= (MAX_TERRENO_FIL / 2)) || ((elfo.fila) >= (FILA_INICIO_HOMBRE)));

		do {
			printf("\nNumero de columna?\n");
			scanf("%i", &(elfo.columna));
			if (((elfo.columna) < MINIMA_COLUMNA) || ((elfo.columna) > MAX_TERRENO_COL)){
				printf("Lo siento no podes ubicar al elfo en esa columna.\n");
			}
		} while (((elfo.columna) < MINIMA_COLUMNA) || ((elfo.columna) > MAX_TERRENO_COL));

		return (elfo);
	}else {
		do {
			printf("\nNumero de columna?\n");
			scanf("%i", &(hombre.columna));
			if (((hombre.columna) < MINIMA_COLUMNA) || ((hombre.columna) > MAX_TERRENO_COL)){
				printf("Lo siento no podes ubicar al hombre en esa columna.\n");
			}
		} while (((hombre.columna) < MINIMA_COLUMNA) || ((hombre.columna) > MAX_TERRENO_COL));
	
		return (hombre);
	}
}
//Personaje hombre o elfo con todos sus campos correctamente cargados.

//Recibe el juego inicializado.
personaje_t generar_personaje_isengard (juego_t* juego){

	personaje_t uruk;
	personaje_t orco;

	char respuesta_isengard;

	(uruk.codigo) = CODIGO_URUK;
	(uruk.vida) = 200 - juego->plus_isengard;
	(uruk.ataque) = 10 + juego->plus_isengard;
	(uruk.esta_vivo) = true;

	(orco.codigo) = CODIGO_ORCO;
	(orco.vida) = 100 - juego->plus_isengard;
	(orco.ataque) = 50 + juego->plus_isengard;
	(orco.esta_vivo) = true;
	(orco.fila) = FILA_INICIO_ORCO;

	do {
		printf("\nQuéres posicionar un uruk-hai (U) o un orco (O)? Respondé con su respectivo código en mayúscula por favor.\n");
		scanf(" %c", &respuesta_isengard);
		if ((respuesta_isengard == CODIGO_URUK) && (((juego->cant_energia_isengard) - COSTO_URUK) < 0)){
			printf("Lo siento, no tenés suficiente energía para crear un uruk-hai.\n");
		}
	} while (((respuesta_isengard != CODIGO_URUK) && (respuesta_isengard != CODIGO_ORCO)) || ((respuesta_isengard == CODIGO_URUK) && (((juego->cant_energia_isengard) - COSTO_URUK) < 0)));

	if (respuesta_isengard == CODIGO_URUK){

		do{
			printf("\nNumero de fila?\n");
			scanf("%i", &(uruk.fila));
			if (((uruk.fila) >= (MAX_TERRENO_FIL / 2)) || ((uruk.fila) <= FILA_INICIO_ORCO)){
				printf("Lo siento no podes ubicar al uruk-hai en esa fila.\n");
			}		
		} while (((uruk.fila) >= (MAX_TERRENO_FIL / 2)) || ((uruk.fila) <= FILA_INICIO_ORCO));

		do{
			printf("\nNumero de columna?\n");
			scanf("%i", &(uruk.columna));
			if (((uruk.columna) < MINIMA_COLUMNA) || ((uruk.columna) > MAX_TERRENO_COL)){
				printf("Lo siento no podes ubicar al uruk-hai en esa columna.\n");
			}
		} while (((uruk.columna) < MINIMA_COLUMNA) || ((uruk.columna) > MAX_TERRENO_COL));

		return (uruk);
	}else {
		do {
			printf("\nNumero de columna?\n");
			scanf("%i", &(orco.columna));
			if (((orco.columna) < MINIMA_COLUMNA) || ((orco.columna) > MAX_TERRENO_COL)){
				printf("Lo siento no podes ubicar al orco en esa columna.\n");
			}
		} while (((orco.columna) < MINIMA_COLUMNA) || ((orco.columna) > MAX_TERRENO_COL));

		return (orco);
	}	
}
//Personaje orco o uruk con todos sus campos correctamente cargados.

//Recibe el juego inicializado.
void pedir_personaje_dos_jugadores (juego_t* juego){

	personaje_t personaje_rohan_obtenido;
	personaje_t personaje_isen_obtenido;

	int respuesta_rohan;
	int respuesta_isengard;

	do{
		printf("Lider de las tropas de Rohan deseas posicionar un personaje? Ingresá 1 (si) o 2 (no) por favor.\n");
		scanf("%i", &respuesta_rohan);
	} while ((respuesta_rohan != SI) && (respuesta_rohan != NO));

	if ((juego->cant_energia_rohan < COSTO_HOMBRE)){
		printf("Lider de las tropas de Rohan no tenes la suficiente energía como para crear un personaje. Esperá el siguiente turno.\n");
	}

	if ((respuesta_rohan == SI) && (juego->cant_energia_rohan >= COSTO_HOMBRE)){
		personaje_rohan_obtenido = generar_personaje_rohan (juego);
		posicionar_personaje (juego, personaje_rohan_obtenido);	
	}
	
	actualizar_interfaz (juego);

	do{
		printf("Lider de las tropas de Isengard deseas posicionar un personaje? Ingresá 1 (si) o 2 (no) por favor.\n");
		scanf("%i", &respuesta_isengard);
		} while ((respuesta_isengard != SI) && (respuesta_isengard != NO));

	if ((juego->cant_energia_isengard < COSTO_ORCO)){
			printf("Lider de las tropas de Isengard no tenes la suficiente energía como para crear un personaje. Esperá el siguiente turno.\n");
		}

	if ((respuesta_isengard == SI) && (juego->cant_energia_isengard >= COSTO_ORCO)){
		personaje_isen_obtenido = generar_personaje_isengard (juego);
		posicionar_personaje (juego, personaje_isen_obtenido);
	}

	actualizar_interfaz (juego);		
}
//Cada jugador posicionó un personaje si lo deseó y cumplió las condiciones necesarias.

//Recibe el juego inicializado.
void pedir_personaje_un_jugador (juego_t* juego){

	personaje_t personaje_isen_obtenido;
	personaje_t personaje_rohan_obtenido;

	int ya_pregunto = NO;
	int respuesta_rohan;
	int respuesta_isengard;

	if ((juego->bando_maquina) == OFENSIVA){
		
		while ((juego->cant_energia_rohan >= COSTO_HOMBRE) && (ya_pregunto == NO)){
			do{
				printf("Lider de las tropas de Rohan deseas posicionar un personaje? Ingresá 1 (si) o 2 (no) por favor.\n");
				scanf("%i", &respuesta_rohan);
			} while ((respuesta_rohan != SI) && (respuesta_rohan != NO));

			if (respuesta_rohan == SI){
				personaje_rohan_obtenido = generar_personaje_rohan (juego);
				posicionar_personaje (juego, personaje_rohan_obtenido);
				ya_pregunto = SI;
			}else {
				ya_pregunto = SI;
			}
		}

		if ((juego->cant_energia_rohan < COSTO_HOMBRE) && (ya_pregunto == NO)){
			printf("Lider de las tropas de Rohan no tenes la suficiente energía como para crear un personaje. Esperá el siguiente turno.\n");
		}

		if (juego->cant_energia_isengard >= COSTO_ORCO){
			personaje_isen_obtenido = generar_personaje_maquina	(juego);
			posicionar_personaje (juego, personaje_isen_obtenido);
		}else {
			return;
		}
		
		actualizar_interfaz (juego);

	}else {
			if (juego->cant_energia_rohan >= COSTO_HOMBRE){
				personaje_rohan_obtenido = generar_personaje_maquina (juego);
				posicionar_personaje (juego, personaje_rohan_obtenido);
			}

			while ((juego->cant_energia_isengard >= COSTO_ORCO) && (ya_pregunto == NO)){
				do{
					printf("Lider de las tropas de Isengard deseas posicionar un personaje? ingrese si o no por favor:\n");
					scanf("%i", &respuesta_isengard);
				} while ((respuesta_isengard != SI) && (respuesta_isengard != NO));

				if (respuesta_isengard == SI){
					personaje_isen_obtenido = generar_personaje_isengard (juego);
					posicionar_personaje (juego, personaje_isen_obtenido);
					ya_pregunto = SI;
				}else {
					ya_pregunto = SI;
				}	
			}

			if ((juego->cant_energia_isengard < COSTO_ORCO) && (ya_pregunto == NO)){
					printf("Lider de las tropas de Isengard no tenes la suficiente energía como para crear un personaje. Esperá el siguiente turno.\n");
			}


			if (juego->cant_energia_rohan < COSTO_HOMBRE){
				return;
			}

			actualizar_interfaz (juego);
	}
}
/*El jugador posicionó si lo deseó y cumplió las condiciones necesarias,
 y la máquina posicionó un personaje en caso de cumplir las condiciones necesarias.*/

//Recibe el juego inicializado después de que ambos jugadores realizaron sus acciones.
void aumentar_energia_jugadores (juego_t* juego){
	
	if ((juego->cant_energia_rohan) < 10){
		(juego->cant_energia_rohan)++;
	}

	if ((juego->cant_energia_isengard) < 10){
		(juego->cant_energia_isengard)++;
	}
}
//Ambos jugadores aumentaron su energía.

//Recibe el juego inicializado con cantidad de jugadores correctamente cargado.
void juego_para_dos_jugadores (juego_t* juego){

	char bando_rohan = DEFENSIVA;
	char bando_isengard = OFENSIVA;
	
	while(((juego->llegadas_rohan) < LLEGADAS_PARA_GANAR) && ((juego->llegadas_isengard) < LLEGADAS_PARA_GANAR)){
		pedir_personaje_dos_jugadores (juego);

		for (int i = 0; i < (juego->cantidad_rohan); i++){
			jugar (juego, bando_rohan, i);
		}

		limpiar_personajes_muertos (juego);

		for (int j = 0; j < (juego->cantidad_isengard); j++){
			jugar (juego, bando_isengard, j);
		}

		aumentar_energia_jugadores (juego);

		limpiar_personajes_muertos (juego);

		actualizar_interfaz (juego);
	}
}
//Terminó un turno.

//Recibe el juego inicializado con cantidad de jugadores correctamente cargado.
void juego_versus_maquina (juego_t* juego){

	char bando_rohan = DEFENSIVA;
	char bando_isengard = OFENSIVA;

	while (((juego->llegadas_rohan) < LLEGADAS_PARA_GANAR) && ((juego->llegadas_isengard) < LLEGADAS_PARA_GANAR)){
		pedir_personaje_un_jugador (juego);

		for (int i = 0; i < (juego->cantidad_rohan); i++){
			jugar (juego, bando_rohan, i);
		}

		limpiar_personajes_muertos (juego);

		for (int j = 0; j < (juego->cantidad_isengard); j++){
			jugar (juego, bando_isengard, j);
		}

		limpiar_personajes_muertos (juego);

		aumentar_energia_jugadores (juego);

		actualizar_interfaz (juego);
	}
}
//Terminó un turno.

int main(){
	
	juego_t juego;
	(juego.llegadas_rohan) = 0;
	(juego.llegadas_isengard) = 0;
	(juego.cant_energia_rohan) = ENERGIA_INICIAL;
	(juego.cant_energia_isengard) = ENERGIA_INICIAL;
	(juego.cantidad_rohan) = CANTIDAD_INICIAL_PERSONAJES;
	(juego.cantidad_isengard) = CANTIDAD_INICIAL_PERSONAJES;

	inicializar_juego (&juego);

	if (juego.cantidad_jugadores == 1){
		while(((juego.llegadas_rohan) < LLEGADAS_PARA_GANAR) && ((juego.llegadas_isengard) < LLEGADAS_PARA_GANAR)){
		juego_versus_maquina (&juego);
		}
	}else{
		while(((juego.llegadas_rohan) < LLEGADAS_PARA_GANAR) && ((juego.llegadas_isengard) < LLEGADAS_PARA_GANAR)){
		juego_para_dos_jugadores (&juego);
		}
	}
	
	if (juego.llegadas_rohan >= LLEGADAS_PARA_GANAR){
		printf("Ganó el lider de las tropas de Rohan, felicitaciones.\n");
	}

	if (juego.llegadas_isengard >= LLEGADAS_PARA_GANAR){
		printf("Ganó el lider de las tropas de Isengard, felicitaciones.\n");
	}

	return 0;
}


