#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "enanos.h"

const char INTEGRANTES_MISION[] = {'i','n','t','e','g','r','a','n','t','e','s','_','m','i','s','i','o','n','\0'};
const char ACTUALIZAR_CENSO[] = {'a','c','t','u','a','l','i','z','a','r','_','c','e','n','s','o','\0'};
const char LISTAR_ENANOS[] = {'l','i','s','t','a','r','_','e','n','a','n','o','s','\0'};
const char PROMOVER_ENANOS[] = {'p','r','o','m','o','v','e','r','_','e','n','a','n','o','s','\0'};
const char AYUDA[] = {'a','y','u','d','a','\0'};

int main (int argc, const char* argv[]){

	if (strcmp(argv[1], ACTUALIZAR_CENSO) == IGUALES){
		if (argc != 3){
			printf("Me diste menos o más argumentos de lo que esperaba, probá de nuevo.\n");
		}else {
			actualizar_censo (argv[2]);
		}
	}else if (strcmp(argv[1], INTEGRANTES_MISION) == IGUALES){
			if ((argc != 6) && (argc != 5)){
				printf("Me diste menos o más argumentos de lo que esperaba, probá de nuevo.\n");
			}else {
				if (argc == 6){
					integrantes_mision (atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
				}else {
					integrantes_mision (atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), "mision.dat");
				}
			}
	}else if (strcmp(argv[1], PROMOVER_ENANOS) == IGUALES){
			if (argc == 2){
				promover_enanos ();
			}else {
				printf("Me diste más argumentos de los que esperaba\n");
			}
	}else if (strcmp(argv[1], LISTAR_ENANOS) == IGUALES){
			if (argc != 3){
				printf("Me diste menos o más argumentos de lo que esperaba, probá de nuevo.\n");
			}else {
				if (atoi(argv[2]) > 0 && atoi(argv[2]) <= 5){
					listar_enanos (atoi(argv[2]));
				}else {
					printf("El id de rango que pasaste no existe, por favor ingresá uno válido.\n");
				}
			}
	}else if (strcmp(argv[1], AYUDA) == IGUALES){
			mostrar_ayuda();

	}else {
		printf("Argumento/s desconocidos. Podés leer las opciones de argumentos y su información ingresando './miniestadisticas ayuda'\n");
	}

	return 0;
}
