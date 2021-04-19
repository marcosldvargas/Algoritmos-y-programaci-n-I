#include <stdio.h>
#include <stdlib.h>
#include "perfil.h"
#include "batalla.h"
#define OFENSIVO 'O'
#define DEFENSIVO 'D'
#define INDEFINIDO 'I'

const int SIGNO_MAX=12;
const int SIGNO_MIN=1;
const char ACCION='A';
const char COMEDIA='C';
const char DRAMA='D';
const char TERROR='T';
const int MASCOTAS_MAX=5;
const int MASCOTAS_MIN=0;
const int MIN_INTERVALO1=0;
const int MAX_INTERVALO1=9;
const int MIN_INTERVALO2=10;
const int MAX_INTERVALO2=19;
const int MIN_INTERVALO3=20;
const int MAX_INTERVALO3=29;
const int MIN_INTERVALO4=30;
const int MAX_INTERVALO4=39;
const int MIN_INTERVALO5=40;
const int MAX_INTERVALO5=49;
const int MIN_INTERVALO6=50;
const int MAX_INTERVALO6=59;
const int MIN_INTERVALO7=60;
const int MAX_INTERVALO7=69;
const int MIN_INTERVALO8=70;
const int MAX_INTERVALO8=79;
const int MIN_INTERVALO9=80;
const int MAX_INTERVALO9=89;
const int MIN_INTERVALO10=90;
const int MAX_INTERVALO10=99;
const int LIMITE_MALDADES_BANDO=50;

/* El usuario ingresa un número positivo. */
void preguntar_signo(int* signo){

	printf("\nIngrese el valor del orden de su signo del zodiaco considerando la siguiente tabla:\n\nSIGNO            N°ORDEN\n\nAries ---------> 1\nTauro ---------> 2\nGéminis -------> 3\nCáncer --------> 4\nLeo -----------> 5\nVirgo ---------> 6\nLibra ---------> 7\nEscorpio ------> 8\nSagitario -----> 9\nCapricornio ---> 10\nAcuario -------> 11\nPiscis --------> 12\n");
	scanf("%i", signo);

	while(*signo<SIGNO_MIN || *signo>SIGNO_MAX){
		printf("el valor ingresado no se encuentra en el rango aceptable, intentelo denuevo.\n");
		scanf("%i", signo);
	}
}
/* Dependiendo del valor se conoce el signo. */

/* El usuario ingresa un caracter en mayúscula. */
void preguntar_genero_cine(char* genero){

	printf("\nIngrese la letra que identifique su genero de cine preferido considerando la siguiente tabla:\n\nGÉNERO           LETRA\n\nAcción --------> A\nComedia -------> C\nDrama ---------> D\nTerror --------> T\n");
	scanf(" %c", genero);

	while(*genero!=ACCION && *genero!=COMEDIA && *genero!=DRAMA && *genero!=TERROR){
		printf("la letra ingresada no se encuentra en el rango aceptable, intentelo denuevo.\n");
		scanf(" %c", genero);
	}
}
/* Dependiendo del valor se conoce el genero preferido. */

/* El usuario ingresa un número positivo. */
void preguntar_cant_maldades(int* maldades){
	
	printf("\nIngrese, en una escala del 0 al 99, la cantidad de maldades que hizo en el ultimo mes:\n");
	scanf("%i", maldades);

	while(*maldades<MIN_INTERVALO1 || *maldades>MAX_INTERVALO10){
		printf("el valor ingresado no se encuentra en el rango aceptable, intentelo denuevo.\n");
		scanf("%i", maldades);
	}
}
/* Dependiendo del valor se conoce la cantidad de maldades. */

/* El usuario ingresa un número positivo. */
void preguntar_cant_mascotas(int* mascotas){
	
	printf("\nIngrese la cantidad de mascotas que tiene considerando el rango del 0 al 5, en donde 0 indica que no tiene mascotas y 5 que tiene cinco o más mascotas.\n");
	scanf("%i", mascotas);

	while(*mascotas<MASCOTAS_MIN || *mascotas>MASCOTAS_MAX){
		printf("el valor ingresado no se encuentra en el rango aceptable, intentelo denuevo.\n");
		scanf ("%i", mascotas);
	}
}
/* Dependiendo del valor se conoce la cantidad de mascotas. */

/* Se ingresa el signo y genero de la persona y la cantidad de maldades que hizo la misma antes ya preguntadas. */
char bando(int signo, char genero, int maldades){
	char resultado;
	if((signo%2!=0) && (genero==COMEDIA || genero==TERROR) && (maldades>=LIMITE_MALDADES_BANDO)){
		resultado=OFENSIVO;
	}else if((signo%2==0) && (genero==ACCION || genero==DRAMA) && (maldades<LIMITE_MALDADES_BANDO)){
		resultado=DEFENSIVO;
	}else{
		resultado=INDEFINIDO;
	}
	return resultado;
}
/* Dependiendo del resultado de las comparaciones determina el bando de la persona. */

/* Se ingresa la cantidad de maldades preguntada anteriormente. */
int maldades(int maldades){
	int puntos=0;
	if((maldades>=MIN_INTERVALO1 && maldades<=MAX_INTERVALO1) || (maldades>=MIN_INTERVALO6 && maldades<=MAX_INTERVALO6)){
		puntos=1;
	}else if((maldades>=MIN_INTERVALO2 && maldades<=MAX_INTERVALO2) || (maldades>=MIN_INTERVALO7 && maldades<=MAX_INTERVALO7)){
		puntos=2;
	}else if((maldades>=MIN_INTERVALO3 && maldades<=MAX_INTERVALO3) || (maldades>=MIN_INTERVALO8 && maldades<=MAX_INTERVALO8)){
		puntos=3;
	}else if((maldades>=MIN_INTERVALO4 && maldades<=MAX_INTERVALO4) || (maldades>=MIN_INTERVALO9 && maldades<=MAX_INTERVALO9)){
		puntos=4;
	}else if((maldades>=MIN_INTERVALO5 && maldades<=MAX_INTERVALO5) || (maldades>=MIN_INTERVALO10 && maldades<=MAX_INTERVALO10)){
		puntos=5;
	}
	return puntos;
}
/* Dependiendo de en que intervalo se encuentra la cantidad se determina los puntos que tiene por maldades. */

//Recibe bando e intensidad sin cargar.
void perfil (char* tipo, int* intensidad){
	int signo_recibido=0;
	char genero_recibido; 
	int mascotas_recibidas=0;
	int maldades_recibidas=0;
	char bando_determinado;
	int puntos_totales=0;

	do{
		printf("\nCUESTIONARIO:\n");
		preguntar_signo(&signo_recibido);
		preguntar_genero_cine(&genero_recibido);
		preguntar_cant_maldades(&maldades_recibidas);
		preguntar_cant_mascotas(&mascotas_recibidas);
		bando_determinado = bando(signo_recibido, genero_recibido, maldades_recibidas);
		if (bando_determinado == INDEFINIDO){
			printf("\nAlgo salió mal, por favor realizá nuevamente el cuestionario.\n");
		}
		
	} while(bando_determinado==INDEFINIDO);
	
	puntos_totales = maldades(maldades_recibidas) + mascotas_recibidas;
	(*tipo)=bando_determinado;
	(*intensidad)=puntos_totales;
	system("clear");
}
//Bando e intensidad estan correctamente cargados.