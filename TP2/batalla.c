#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "perfil.h"
#include "batalla.h"

#define MIN_BARRA 3
#define MAX_BARRA 12
#define MAX_PERSONAJES 500
#define MAX_STRING_RESPUESTA 10
#define UN_JUGADOR 1
#define DOS_JUGADORES 2

const int MIN_POSICION_FIL = 0;
const char VACIO = ' ';
const int VUELTA_UNO = 0;
const int VUELTA_DOS = 1;
const int VUELTA_TRES = 2;
const int LANZADORES_MANHATTAN = 3;
const int MAX_CANT_PELEAS = 1;

void mostrar_terreno (juego_t* juego);

void actualizar_interfaz (juego_t* juego);

//Recibe el juego inicializado con el vector de personajes de Rohan y de Isengard correctamente cargados.
void limpiar_personajes_muertos (juego_t* juego){

	personaje_t auxiliar_borrado_rohan;
	personaje_t auxiliar_borrado_isen;

	for (int i = 0; i < (juego->cantidad_rohan); i++){
		if ((juego->rohan[i].esta_vivo) == false){
			if (i == (juego->cantidad_rohan-1)){
				auxiliar_borrado_rohan = juego->rohan[i];
				(juego->cantidad_rohan)--;
			}else {
				auxiliar_borrado_rohan = juego->rohan[i];
				(juego->rohan[i]) = (juego->rohan[juego->cantidad_rohan-1]);
				(juego->cantidad_rohan)--;
			}
			(juego->terreno[auxiliar_borrado_rohan.fila][auxiliar_borrado_rohan.columna]) = VACIO;
		}
	}

	for (int j = 0; j < (juego->cantidad_isengard); j++){
		if ((juego->isengard[j].esta_vivo) == false){
			if (j == (juego->cantidad_isengard-1)){
				auxiliar_borrado_isen = juego->isengard[j];
				(juego->cantidad_isengard)--;
			}else {
				auxiliar_borrado_isen = juego->isengard[j];
				(juego->isengard[j]) = (juego->isengard[juego->cantidad_isengard-1]);
				(juego->cantidad_isengard)--;
			}
			(juego->terreno[auxiliar_borrado_isen.fila][auxiliar_borrado_isen.columna]) = VACIO;
		}
	}
}
//Devuelve el juego con el vector de personajes de Rohan y de Isengard sin personajes muertos.

/*Recibe el juego inicializado, el bando del jugador que tiene que atacar y la posición del personaje (uruk o elfo) en el vector 
de personajes perteneciente al bando que tiene que efectuar el ataque correctamente cargados.*/
void atacar_con_lanzadores (juego_t* juego, char bando, int posicion_personaje){

	int distancia_manhattan = 0;
	int modulo_fila = 0;
	int modulo_columna = 0;

	if (bando == OFENSIVA){
		for (int i = 0; i < MAX_TERRENO_FIL; i++){
			for (int j = 0; j < MAX_TERRENO_COL; j++){
				modulo_fila = abs (i - juego->isengard[posicion_personaje].fila);
				modulo_columna = abs (j - juego->isengard[posicion_personaje].columna);
				distancia_manhattan = modulo_columna + modulo_fila;
				if ((distancia_manhattan <= LANZADORES_MANHATTAN) && ((juego->terreno[i][j] == CODIGO_ELFO) || (juego->terreno[i][j] == CODIGO_HOMBRE))){
					for (int k = 0; k < (juego->cantidad_rohan); k++){
						if (((juego->rohan[k].esta_vivo) == true) && (((juego->rohan[k].fila) == i) && ((juego->rohan[k].columna) == j))){
							(juego->rohan[k].vida) = (juego->rohan[k].vida) - (juego->isengard[posicion_personaje].ataque);
							if (juego->rohan[k].vida <= 0){
								(juego->rohan[k].esta_vivo) = false;
							}
						}
					}
				}
			}
		}
	}

	if (bando == DEFENSIVA){
		for (int i = 0; i < MAX_TERRENO_FIL; i++){
			for (int j = 0; j < MAX_TERRENO_COL; j++){
				modulo_fila = abs (i - juego->rohan[posicion_personaje].fila);
				modulo_columna = abs (j - juego->rohan[posicion_personaje].columna);
				distancia_manhattan = modulo_columna + modulo_fila;
				if ((distancia_manhattan <= LANZADORES_MANHATTAN) && ((juego->terreno[i][j] == CODIGO_URUK) || (juego->terreno[i][j] == CODIGO_ORCO))){
					for (int k = 0; k < (juego->cantidad_isengard); k++){
						if (((juego->isengard[k].esta_vivo) == true) && (((juego->isengard[k].fila) == i) && ((juego->isengard[k].columna) == j))){
							(juego->isengard[k].vida) = (juego->isengard[k].vida) - (juego->rohan[posicion_personaje].ataque);
							if (juego->isengard[k].vida <= 0){
								(juego->isengard[k].esta_vivo) = false;
							}
						}
					}
				}
			}
		}
	}			
}
//El personaje realizó su ataque.

/*Recibe el juego inicializado, el bando del jugador que tiene que atacar y la posición del personaje (hombre u orco) en el vector 
de personajes perteneciente al bando que tiene que efectuar el ataque correctamente cargados.*/
void accionar_infanteria (juego_t* juego, char bando, int posicion_personaje){
	
	int cont_peleas = 0;
	int fila_anterior_rohan = (juego->rohan[posicion_personaje].fila) - 1;
	int fila_siguiente_rohan = (juego->rohan[posicion_personaje].fila) + 1;
	int columna_anterior_rohan = (juego->rohan[posicion_personaje].columna) - 1;
	int columna_siguiente_rohan = (juego->rohan[posicion_personaje].columna) + 1;
	int fila_anterior_isen = (juego->isengard[posicion_personaje].fila) - 1;
	int fila_siguiente_isen = (juego->isengard[posicion_personaje].fila) + 1;
	int columna_anterior_isen = (juego->isengard[posicion_personaje].columna) - 1;
	int columna_siguiente_isen = (juego->isengard[posicion_personaje].columna) + 1;

	personaje_t auxiliar_rohan;
	personaje_t auxiliar_isengard;

	if (bando == DEFENSIVA){
		for (int i = fila_anterior_rohan; i < (fila_siguiente_rohan + 1); i++){
			for (int j = columna_anterior_rohan; j < (columna_siguiente_rohan + 1); j++){
				if ((cont_peleas < MAX_CANT_PELEAS) && ((juego->terreno[i][j] == CODIGO_URUK) || (juego->terreno[i][j] == CODIGO_ORCO)) && (j <= MAX_TERRENO_COL) && (i >= 0) && (i <= MAX_TERRENO_FIL)){
					for (int m = 0; m < (juego->cantidad_isengard); m++){
						if ((juego->isengard[m].esta_vivo == true) && ((juego->isengard[m].fila == i) && (juego->isengard[m].columna == j))){
							(juego->isengard[m].vida) = (juego->isengard[m].vida) - (juego->rohan[posicion_personaje].ataque);
							if ((juego->isengard[m].vida) <= 0){
								(juego->isengard[m].esta_vivo) = false;
							}
							cont_peleas ++;
						} 
					}
				}
			}
		}

		if (cont_peleas < MAX_CANT_PELEAS){
			while (((juego->rohan[posicion_personaje].fila) > 0) && (cont_peleas < MAX_CANT_PELEAS)){
				if (((juego->terreno[fila_anterior_rohan][juego->rohan[posicion_personaje].columna]) == CODIGO_ELFO) || ((juego->terreno[fila_anterior_rohan][juego->rohan[posicion_personaje].columna]) == CODIGO_HOMBRE)){
					auxiliar_rohan = juego->rohan[posicion_personaje];
					(juego->rohan[posicion_personaje].fila) = (juego->rohan[posicion_personaje].fila) - 2; //hombre saltea a elfo y hombre
					(juego->terreno[(juego->rohan[posicion_personaje].fila)][(juego->rohan[posicion_personaje].columna)]) = CODIGO_HOMBRE;
					(juego->terreno[(auxiliar_rohan.fila)][(auxiliar_rohan.columna)]) = VACIO;
					cont_peleas++;
				}else {
					auxiliar_rohan = juego->rohan[posicion_personaje];
					(juego->rohan[posicion_personaje].fila)--;
					(juego->terreno[(juego->rohan[posicion_personaje].fila)][(juego->rohan[posicion_personaje].columna)]) = CODIGO_HOMBRE;
					(juego->terreno[(auxiliar_rohan.fila)][(auxiliar_rohan.columna)]) = VACIO;
					cont_peleas++;
				}

				if (juego->rohan[posicion_personaje].fila == 0){
					(juego->llegadas_rohan)++;
					(juego->terreno[(juego->rohan[posicion_personaje].fila)][(juego->rohan[posicion_personaje].columna)]) = VACIO;
					(juego->rohan[posicion_personaje].esta_vivo) = false;
				}
			}
		}
	}


	if (bando == OFENSIVA){
		for (int i = fila_anterior_isen; i < (fila_siguiente_isen + 1); i++){
			for (int j = columna_anterior_isen; j < (columna_siguiente_isen + 1); j++){
				if ((cont_peleas < MAX_CANT_PELEAS) && ((juego->terreno[i][j] == CODIGO_ELFO) || (juego->terreno[i][j] == CODIGO_HOMBRE)) && (j <= MAX_TERRENO_COL) && (i >= 0) && (i <= MAX_TERRENO_FIL)){
					for (int m = 0; m < (juego->cantidad_rohan); m++){
						if ((juego->rohan[m].esta_vivo == true) && ((juego->rohan[m].fila == i) && (juego->rohan[m].columna == j))){
							(juego->rohan[m].vida) = (juego->rohan[m].vida) - (juego->isengard[posicion_personaje].ataque);
							if ((juego->rohan[m].vida) <= 0){
								(juego->rohan[m].esta_vivo) = false;
							}
							cont_peleas ++;
						}
					}
				}
			}
		}

		if (cont_peleas < MAX_CANT_PELEAS){
			while (((juego->isengard[posicion_personaje].fila) < (MAX_TERRENO_FIL-1)) && (cont_peleas < MAX_CANT_PELEAS)){
				if (((juego->terreno[fila_siguiente_isen][juego->isengard[posicion_personaje].columna]) == CODIGO_URUK) || ((juego->terreno[fila_siguiente_isen][juego->isengard[posicion_personaje].columna]) == CODIGO_ORCO)){
					auxiliar_isengard = juego->isengard[posicion_personaje];
					(juego->isengard[posicion_personaje].fila) = (juego->isengard[posicion_personaje].fila) + 2; //orco saltea a uruk o a orco
					(juego->terreno[(juego->isengard[posicion_personaje].fila)][(juego->isengard[posicion_personaje].columna)]) = CODIGO_ORCO;
					(juego->terreno[(auxiliar_isengard.fila)][(auxiliar_isengard.columna)]) = VACIO;
					cont_peleas++;
				} else {
					auxiliar_isengard = juego->isengard[posicion_personaje];
					(juego->isengard[posicion_personaje].fila)++; //avanza orco
					(juego->terreno[(juego->isengard[posicion_personaje].fila)][(juego->isengard[posicion_personaje].columna)]) = CODIGO_ORCO;
					(juego->terreno[(auxiliar_isengard.fila)][(auxiliar_isengard.columna)]) = VACIO;
					cont_peleas++;
				}
			}

			if (juego->isengard[posicion_personaje].fila == (MAX_TERRENO_FIL-1)){
				(juego->llegadas_isengard)++;
				(juego->terreno[juego->isengard[posicion_personaje].fila][juego->isengard[posicion_personaje].columna]) = VACIO;
				(juego->isengard[posicion_personaje].esta_vivo) = false;
			}	
		}
	}
}
//El personaje atacó si debia o avanzó.

/*Recibe el juego inicializado, el bando del jugador que tiene que atacar y la posición del personaje en el vector 
de personajes perteneciente al bando que tiene que efectuar el ataque correctamente cargados.*/
void jugar (juego_t* juego, char bando, int posicion_personaje){

	if (((juego->rohan[posicion_personaje].codigo) == CODIGO_ELFO) && (bando == DEFENSIVA)){
		atacar_con_lanzadores (juego, bando, posicion_personaje);
	}else if (((juego->rohan[posicion_personaje].codigo) == CODIGO_HOMBRE) && (bando == DEFENSIVA)){
		accionar_infanteria (juego, bando, posicion_personaje);
	}else if (((juego->isengard[posicion_personaje].codigo) == CODIGO_URUK) && (bando == OFENSIVA)){
		atacar_con_lanzadores (juego, bando, posicion_personaje);
	}else if (((juego->isengard[posicion_personaje].codigo) == CODIGO_ORCO) && (bando == OFENSIVA)){
		accionar_infanteria (juego, bando, posicion_personaje);
	}
}	
//Ambos bandos realizaron sus acciones con sus respectivos personajes, ya sea ataque o movimiento.

//Recibe el juego inicializado y un personaje con todos sus campos correctamente cargados.
void posicionar_personaje (juego_t* juego, personaje_t personaje){

	if (personaje.codigo == CODIGO_ELFO){
		(juego->rohan[juego->cantidad_rohan]) = personaje;
		(juego->terreno[personaje.fila][personaje.columna]) = CODIGO_ELFO;
		(juego->cantidad_rohan)++;
		(juego->cant_energia_rohan) = (juego->cant_energia_rohan) - COSTO_ELFO;
	}else if (personaje.codigo == CODIGO_HOMBRE){
		(juego->rohan[juego->cantidad_rohan]) = personaje;
		(juego->terreno[personaje.fila][personaje.columna]) = CODIGO_HOMBRE;
		(juego->cantidad_rohan)++;
		(juego->cant_energia_rohan) = (juego->cant_energia_rohan) - COSTO_HOMBRE;
	}else if (personaje.codigo == CODIGO_URUK){
		(juego->isengard[juego->cantidad_isengard]) = personaje;
		(juego->terreno[personaje.fila][personaje.columna]) = CODIGO_URUK;
		(juego->cantidad_isengard)++;
		(juego->cant_energia_isengard) = (juego->cant_energia_isengard) - COSTO_URUK;
	}else if (personaje.codigo == CODIGO_ORCO){
		(juego->isengard[juego->cantidad_isengard]) = personaje;
		(juego->terreno[personaje.fila][personaje.columna]) = CODIGO_ORCO;
		(juego->cantidad_isengard)++;
		(juego->cant_energia_isengard) = (juego->cant_energia_isengard) - COSTO_ORCO;
	}
}
//Se posicionó al personaje en el terreno.

//Recibe el juego con el campo de energia de Rohan correctamente cargado.
void mostrar_energia_rohan (juego_t* juego){

	char vida[MIN_BARRA][MAX_BARRA];

	for (int k=0; k<MIN_BARRA; k++){
		for (int j=0; j<MAX_BARRA; j++){
			vida[k][j] = VACIO;
		}
	}

	for (int m=1; m<11; m++){
			vida[0][m] = '=';
			vida[2][m] = '=';
		}

	vida[0][0]= '@';
	vida[0][11]= '@';
	vida[2][0]= '@';
	vida[2][11]= '@';
	vida[1][0]= '|';
	vida[1][11]= '|';

	for (int l=1; l<=(juego->cant_energia_rohan); l++){
		vida[1][l]= 'O';
	}

	for (int x=0; x<MIN_BARRA; x++){
		for (int y=0; y<MAX_BARRA; y++){
			printf("%c", vida[x][y]);
		}
		printf("\n");
	}
}
//Muestra la energia de Rohan en pantalla.

//Recibe el juego con el campo de energia de Isengard correctamente cargado.
void mostrar_energia_isengard (juego_t* juego){

	char vida[MIN_BARRA][MAX_BARRA];

	for (int k=0; k<MIN_BARRA; k++){
		for (int j=0; j<MAX_BARRA; j++){
			vida[k][j] = VACIO;
		}
	}

	for (int m=1; m<11; m++){
			vida[0][m] = '=';
			vida[2][m] = '=';
		}

	vida[0][0]= '@';
	vida[0][11]= '@';
	vida[2][0]= '@';
	vida[2][11]= '@';
	vida[1][0]= '|';
	vida[1][11]= '|';

	for (int l=1; l<=(juego->cant_energia_isengard); l++){
		vida[1][l]= 'O';
	}

	for (int x=0; x<MIN_BARRA; x++){
		for (int y=0; y<MAX_BARRA; y++){
			printf("%c", vida[x][y]);
		}
		printf("\n");
	}
}
//Muestra la energia de Isengard en pantalla.

//Recibe el juego y la intensidad y el bando de ambos jugadores sin cargar.
void determinar_bandos (int* intensidad_j1, int* intensidad_j2, char* tipo_j1, char* tipo_j2, juego_t* juego){

	int cantidad_jugadores = 0;

	printf("\nPor favor realice el siguiente cuestionario para poder determinar su bando y su intensidad\n");
	perfil (tipo_j1, intensidad_j1);

	do {
		printf ("Cuantas personas van a jugar?\n");
		scanf ("%i", &cantidad_jugadores);
		if ((cantidad_jugadores != UN_JUGADOR) && (cantidad_jugadores != DOS_JUGADORES)){	
			printf ("Por favor ingrese una cantidad válida de jugadores.\n");
		}
	} while ((cantidad_jugadores != UN_JUGADOR) && (cantidad_jugadores != DOS_JUGADORES));

	if (cantidad_jugadores == UN_JUGADOR){
		(juego->cantidad_jugadores) = UN_JUGADOR;
		(*intensidad_j2) = 10 - (*intensidad_j1);

		if ((*tipo_j1) == OFENSIVA){
			(*tipo_j2) = DEFENSIVA;
			(juego->bando_maquina) = DEFENSIVA;
			printf ("\nTu rival voy a ser yo, vas a dirigir las tropas de Isengard (ofensivo), tu intensidad será %i. Yo voy a dirigir las tropas de Rohan (defensivo) mi intensidad será %i, buena suerte...\n\n", (*intensidad_j1), (*intensidad_j2));		
		} else {
			(*tipo_j2) = OFENSIVA;
			(juego->bando_maquina) = OFENSIVA;
			printf ("\nTu rival voy a ser yo, vas a dirigir las tropas de Rohan (defensivo), tu intensidad será %i. Yo voy a dirigir las tropas de Isengard (ofensivo) mi intensidad será %i, buena suerte...\n\n", (*intensidad_j1), (*intensidad_j2));
		}
	} else {
		(juego->cantidad_jugadores) = DOS_JUGADORES;
		(*intensidad_j2) = 10 - (*intensidad_j1);
		
		if ((*tipo_j1) == OFENSIVA){
			(juego->bando_jugador_uno) = OFENSIVA;
			(juego->bando_jugador_dos) = DEFENSIVA;
			printf("\nJugador 1 su bando es ofensivo y su intensidad es %i, dirigirá las tropas de Isengard. Jugador 2 su bando es defensivo y su intensidad es %i, dirigirá las tropas de Rohan. \n\n", (*intensidad_j1), (*intensidad_j2));
		} else {
			(juego->bando_jugador_uno) = DEFENSIVA;
			(juego->bando_jugador_dos) = OFENSIVA;
			printf("\nJugador 1 su bando es defensivo y su intensidad es %i, dirigirá las tropas de Rohan. Jugador 2 su bando es ofensivo y su intensidad es %i, dirigirá las tropas de Isengard. \n\n", (*intensidad_j1), (*intensidad_j2));
		}	 
	}
}
//La intensidad y el bando de ambos jugadores estan cargados.

//Recibe el juego y la intensidad y el bando de ambos jugadores cargados correctamente.
void calcular_plus (int* intensidad_j1, int* intensidad_j2, char* tipo_j1, char* tipo_j2, juego_t* juego){

	int numero_random = rand () %5;

	if ((*tipo_j1) == OFENSIVA){
		juego->plus_isengard = (*intensidad_j1) * numero_random;
		juego->plus_rohan = (*intensidad_j2) * numero_random;
	} else {
		juego->plus_isengard = (*intensidad_j2) * numero_random;
		juego->plus_rohan = (*intensidad_j1) * numero_random;
	}
}
//El plus de Rohan y el de Isengard estan cargados correctamente.


//Recibe el juego.
void crear_terreno (juego_t* juego){

	for (int i = 0; i < MAX_TERRENO_FIL; i++){
		for (int j = 0; j < MAX_TERRENO_COL; j++){
			juego->terreno[i][j] = VACIO;
		}
	}
}
//El terreno está creado.

//Recibe el juego con el terreno cargado.
void ubicar_lanzadores_iniciales (juego_t* juego){

	int contador_rohan = 0;
	int contador_isengard = 0;

	while (contador_rohan < (juego->cantidad_rohan)){

		(juego->rohan[contador_rohan].codigo) = CODIGO_ELFO;
		(juego->rohan[contador_rohan].vida) = 200 - juego->plus_rohan;
		(juego->rohan[contador_rohan].ataque) = 10 + juego->plus_rohan;
		(juego->rohan[contador_rohan].esta_vivo) = true;
		do {
			(juego->rohan[contador_rohan].fila) = rand () %((MAX_TERRENO_FIL/2)-2) +(MAX_TERRENO_FIL/2); 
			(juego->rohan[contador_rohan].columna) = rand () %(MAX_TERRENO_COL-1) +MINIMA_COLUMNA;
		} while (juego->terreno[juego->rohan[contador_rohan].fila][juego->rohan[contador_rohan].columna] == CODIGO_ELFO);
		juego->terreno[juego->rohan[contador_rohan].fila][juego->rohan[contador_rohan].columna] = CODIGO_ELFO;
		contador_rohan ++;	
	}

	while (contador_isengard < (juego->cantidad_isengard)){

		(juego->isengard[contador_isengard].codigo) = CODIGO_URUK;
		(juego->isengard[contador_isengard].vida) = 200 - juego->plus_isengard;
		(juego->isengard[contador_isengard].ataque) = 10 + juego->plus_isengard;
		(juego->isengard[contador_isengard].esta_vivo) = true;
		do {
			(juego->isengard[contador_isengard].fila) = rand () %((MAX_TERRENO_FIL/2)-1) +(MIN_POSICION_FIL+1); 
			(juego->isengard[contador_isengard].columna) = rand () %(MAX_TERRENO_COL-1) +MINIMA_COLUMNA;
		} while (juego->terreno[juego->isengard[contador_isengard].fila][juego->isengard[contador_isengard].columna] == CODIGO_URUK);
		juego->terreno[juego->isengard[contador_isengard].fila][juego->isengard[contador_isengard].columna] = CODIGO_URUK;
		contador_isengard ++;	
	}
}
//Los uruks y los elfos estan ubicados en el terreno correctamente.

//Recibe el juego inicializado con todos las acciones de un turno realizadas.
void actualizar_interfaz (juego_t* juego){

	system ("clear"); 
	mostrar_energia_isengard (juego);
	printf("llegadas isengard: %i\n", (juego->llegadas_isengard));
	mostrar_terreno (juego);
	printf("llegadas rohan: %i\n", (juego->llegadas_rohan));
	mostrar_energia_rohan (juego);
}
//Se muestra en pantalla el terreno y la energia actual de ambos jugadores.

//Recibe el juego con el terreno creado.
void mostrar_terreno (juego_t* juego){

	for (int m = 0 ; m < MAX_TERRENO_FIL ; ++m){
		for (int n = 0 ; n < MAX_TERRENO_COL ; ++n){
			printf ("[%c]", juego->terreno[m][n]);
		}
		printf ("\n");
	}
}
//Muestra el terreno.

//Recibe el juego con los campos de llegadas y energia de ambos jugadores inicializados.
void inicializar_juego (juego_t* juego){

	srand ((unsigned) time (NULL));
	int intensidad_j1 = 0;
	int intensidad_j2 = 0;
	char tipo_j1;
	char tipo_j2;

	determinar_bandos (&intensidad_j1, &intensidad_j2, &tipo_j1, &tipo_j2, juego);
	calcular_plus (&intensidad_j1, &intensidad_j2, &tipo_j1, &tipo_j2, juego);
	crear_terreno (juego);
	ubicar_lanzadores_iniciales (juego);
	actualizar_interfaz (juego);
}
//El terreno, bandos, plus de jugadores, uruks y elfos iniciales, y energia inicial de ambos jugadores estan correctamente cargados.

