#include <stdio.h>
#include <string.h>
#include "enanos.h"

const int OBRERO = 1;
const int APRENDIZ = 2;
const int GUERRERO = 3;
const int LIDER = 4;
const int GENERAL = 5;
const int NECESARIAS_PARA_GUERRERO = 10;
const int NECESARIAS_PARA_LIDER = 100;
const int NECESARIAS_PARA_GENERAL = 250;
const int MINIMA_EDAD_LIDER = 40;
const int MAXIMA_EDAD_LIDER = 50;
const int MAXIMA_EDAD_GENERAL = 60;
const int MAXIMO_APRENDICES = 10;
const char MISION_DAT[] = {'m','i','s','i','o','n','.','d','a','t','\0'}; 
const char FORMATO_BINARIO[] = {'.','d','a','t','\0'};
const int MUERTO = -1;

/*Pre: El archivo del censo y el de la misión tienen que estar correctamente creados.
  Post: El archivo del censo está actualizado.
*/
void actualizar_censo (const char* nombre_mision){

	FILE* censo;
	FILE* mision;
	FILE* censo_actualizado;
	enano_t enano_censo;
	enano_t enano_mision;
	int cantidad_leidos;
	char nombre_mision_final[MAX_NOMBRE];

	strcpy(nombre_mision_final, nombre_mision);
	strcat(nombre_mision_final, FORMATO_BINARIO);

	censo = fopen("censo.csv","r");

	if (censo == NULL){
		printf("No se pudo abrir el archivo censo.csv.\n");
		return;
	}

	mision = fopen(nombre_mision_final,"r");

	if (mision == NULL){
		printf("No se pudo abrir el archivo de mision.\n");
		fclose(censo);
		return;
	}

	censo_actualizado = fopen("censo_actualizado.csv","w");

	if (censo_actualizado == NULL){
		printf("No se pudo crear el archivo censo_actualizado.csv.\n");
		fclose(censo);
		fclose(mision);
		return;
	}

	cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
	fread(&enano_mision, sizeof (enano_t), 1, mision);

	while((cantidad_leidos != EOF) && (!feof(mision))){
		if (strcmp(enano_censo.nombre, enano_mision.nombre) == IGUALES){
			if (enano_mision.edad != MUERTO){
				fprintf(censo_actualizado, "%s;%i;%i;%i\n", enano_censo.nombre, enano_censo.edad, (enano_censo.cantidad_misiones + 1), enano_censo.id_rango);
				cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
				fread(&enano_mision, sizeof (enano_t), 1, mision);	
			}else{
				cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
				fread(&enano_mision, sizeof (enano_t), 1, mision);
			}
		}else if (strcmp(enano_censo.nombre, enano_mision.nombre) < IGUALES){
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);
			cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
		}else {
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", enano_mision.nombre, enano_mision.edad, (enano_mision.cantidad_misiones + 1), enano_mision.id_rango);
			fread(&enano_mision, sizeof (enano_t), 1, mision);
		}
	}

	while (cantidad_leidos != EOF){
		fprintf(censo_actualizado, "%s;%i;%i;%i\n", enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);
		cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
	}

	while (!feof(mision)){
		fprintf(censo_actualizado, "%s;%i;%i;%i\n", enano_mision.nombre, enano_mision.edad, (enano_mision.cantidad_misiones + 1), enano_mision.id_rango);
		fread(&enano_mision, sizeof (enano_t), 1, mision);	
	}

	fclose(censo);
	fclose(mision);
	fclose(censo_actualizado);
	remove("censo.csv");
	rename("censo_actualizado.csv", "censo.csv");
}

/*Pre: Cantidad de guerreros, líderes, generales y el nombre de la misión correctamente cargados.
       Si existe una misión con el mismo nombre tiene que estar correctamente creada y se deben tener permisos para abrir el archivo.
  Post: Se creó una lista de enanos para una misión.
*/
void integrantes_mision (int cant_guerreros, int cant_lideres, int cant_generales, const char nombre_mision[MAX_NOMBRE]){
	
	enano_t auxiliar_enano;
	int contador_aprendices = 0;
	int contador_guerreros = 0;
	int contador_lideres = 0;
	int contador_generales = 0;
	int cantidad_leidos = 0;
	FILE* censo;
	FILE* mision;
	char nombre_mision_final[MAX_NOMBRE];

	if (strcmp(nombre_mision, MISION_DAT) == IGUALES){
		strcpy(nombre_mision_final, MISION_DAT);
	}else {
		strcpy(nombre_mision_final, nombre_mision);
		strcat(nombre_mision_final, FORMATO_BINARIO);
	}

	mision = fopen(nombre_mision_final,"r"); //chequeo si ya existía una mision con el mismo nombre.

	if (mision != NULL){
		fclose(mision);
		printf("La misión para la cual estás enlistando enanos ya existe, no es posible crearla de nuevo.\n");
		return;
	}

	censo = fopen("censo.csv","r");

	if (censo == NULL){
		printf("No se pudo abrir el archivo censo.csv.\n");
		return;
	}

	mision = fopen(nombre_mision_final,"w");

	if (mision == NULL){
		printf("No se pudo crear el archivo mision.dat.\n");
		fclose(censo);
		return;
	}

	cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);

	while (cantidad_leidos != EOF){
		if ((contador_guerreros < cant_guerreros) && (auxiliar_enano.id_rango == GUERRERO)){
			fwrite(&auxiliar_enano, sizeof (enano_t), 1, mision);
			contador_guerreros ++;
		}else if ((contador_lideres < cant_lideres) && (auxiliar_enano.id_rango == LIDER)){
			fwrite(&auxiliar_enano, sizeof (enano_t), 1, mision);	
			contador_lideres ++;	
		}else if ((contador_generales < cant_generales) && (auxiliar_enano.id_rango == GENERAL)){
			fwrite(&auxiliar_enano, sizeof (enano_t), 1, mision);				
			contador_generales ++;
		}else if ((contador_aprendices < MAXIMO_APRENDICES) && (auxiliar_enano.id_rango == APRENDIZ)){
			fwrite(&auxiliar_enano, sizeof (enano_t), 1, mision);
			contador_aprendices ++;
		}

		cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);
	}

	fclose(censo);
	fclose(mision);

	if ((contador_guerreros < cant_guerreros) || (contador_lideres < cant_lideres) || (contador_generales < cant_generales)){
		printf("Una o más de una cantidad pedida resultó ser mayor que el stock, no se pudo crear la misión.\n");
		remove(nombre_mision_final);
	}
}

/*Pre: El archivo del censo está correctamente creado.
  Post: Ascendieron de rango los enanos que cumplian las condiciones necesarias.
*/
void promover_enanos (){

	FILE* censo;
	FILE* censo_actualizado;
	int cantidad_leidos;
	enano_t auxiliar_enano;

	censo = fopen("censo.csv","r");

	if (censo == NULL){
		printf("No se pudo abrir el archivo censo.csv.\n");
		return;
	}

	censo_actualizado = fopen("censo_actualizado.csv","w");

	if (censo_actualizado == NULL){
		printf("No se pudo crear el archivo censo_actualizado.csv.\n");
		fclose(censo);
		return;
	}

	cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);

	while (cantidad_leidos != EOF){
		if ((auxiliar_enano.id_rango == APRENDIZ) && (auxiliar_enano.cantidad_misiones > NECESARIAS_PARA_GUERRERO)){
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", auxiliar_enano.nombre, auxiliar_enano.edad, auxiliar_enano.cantidad_misiones, (auxiliar_enano.id_rango + 1));
		}else if ((auxiliar_enano.id_rango == GUERRERO) && (auxiliar_enano.cantidad_misiones > NECESARIAS_PARA_LIDER) && (auxiliar_enano.edad >= MINIMA_EDAD_LIDER && auxiliar_enano.edad < MAXIMA_EDAD_LIDER)){
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", auxiliar_enano.nombre, auxiliar_enano.edad, auxiliar_enano.cantidad_misiones, (auxiliar_enano.id_rango + 1));
		}else if ((auxiliar_enano.id_rango == LIDER) && (auxiliar_enano.cantidad_misiones > NECESARIAS_PARA_GENERAL) && (auxiliar_enano.edad >= MAXIMA_EDAD_LIDER && auxiliar_enano.edad < MAXIMA_EDAD_GENERAL)){
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", auxiliar_enano.nombre, auxiliar_enano.edad, auxiliar_enano.cantidad_misiones, (auxiliar_enano.id_rango + 1));
		}else {
			fprintf(censo_actualizado, "%s;%i;%i;%i\n", auxiliar_enano.nombre, auxiliar_enano.edad, auxiliar_enano.cantidad_misiones, (auxiliar_enano.id_rango));
		}
		cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);
	}

	fclose(censo);
	fclose(censo_actualizado);
	remove("censo.csv");
	rename("censo_actualizado.csv", "censo.csv");
}

/*Pre: Los archivos rangos y censo estan abiertos. 
  Post: Se muestra en pantalla todos los enanos del rango solicitado.
*/
void imprimir_lista (int rango_pedido, FILE* rangos, FILE* censo){

	rango_t auxiliar_rango;
	enano_t auxiliar_enano;
	int cantidad_leidos;

	fseek(rangos, (long)((rango_pedido-1)* (long)(sizeof (rango_t))), SEEK_SET);
	fread(&auxiliar_rango, sizeof (rango_t), 1, rangos);
	printf("\n%s: %s\n", auxiliar_rango.nombre, auxiliar_rango.descripcion);
	printf("\nNOMBRE\t  EDAD\t  CANTIDAD DE MISIONES\n\n");
	cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);
	while (cantidad_leidos != EOF){
		if (cantidad_leidos != EOF && auxiliar_enano.id_rango == rango_pedido){
			printf("%s\t  %i\t  %i\n", auxiliar_enano.nombre, auxiliar_enano.edad, auxiliar_enano.cantidad_misiones);
		} 
		cantidad_leidos = fscanf(censo, "%[^;];%i;%i;%i\n", auxiliar_enano.nombre, &auxiliar_enano.edad, &auxiliar_enano.cantidad_misiones, &auxiliar_enano.id_rango);
	}
}

/*Pre: El archivo del censo está correctamente creado.
  Post: Se mostraron los enanos del rango pedido en pantalla.
*/
void listar_enanos (int id_rango){

	FILE* censo;
	FILE* rangos;

	censo = fopen("censo.csv","r");

	if (censo == NULL){
		printf("No se abrió el archivo censo.csv.\n");
		return;
	}

	rangos = fopen("rangos.dat","r");

	if (rangos == NULL){
		printf("No se abrió el archivo rangos.dat.\n");
		fclose(censo);
		return;
	}

	if (id_rango == OBRERO){
		imprimir_lista (OBRERO, rangos, censo);
	}else if (id_rango == APRENDIZ){
		imprimir_lista (APRENDIZ, rangos, censo);
	}else if (id_rango == GUERRERO){
		imprimir_lista (GUERRERO, rangos, censo);
	}else if (id_rango == LIDER){
		imprimir_lista (LIDER, rangos, censo);
	}else { 
		imprimir_lista (GENERAL, rangos, censo);
	}

	fclose(censo);
	fclose(rangos);
}

/*Post: Se muestra en pantalla información útil para el usuario.
*/
void mostrar_ayuda (){
	printf("\nARGUMENTO\t\t  IMPLEMENTACIÓN\n\n");
	printf("'actualizar_censo'\t  './miniestadisticas actualizar_censo nombre_mision'\n");
	printf("'integrantes_mision'\t  './miniestadisticas integrantes_mision cantidad_guerreros cantidad_líderes cantidad_generales nombre_mision'\n");
	printf("'promover_enanos'\t  './miniestadisticas promover_enanos'\n");
	printf("'listar_enanos'\t          './miniestadisticas listar_enanos id_rango'\n");
	printf("\nINFORMACIÓN\n");
	printf("\nactualizar_censo:\nA partir de la misión recibida actualiza el censo de la totalidad de enanos eliminando a los que no hayan vuelto de la misma e incorporando a los que se perdieron en otras misiones y lograron volver.\n");
	printf("\nintegrantes_mision:\nRecibe una cantidad de enanos guerreros, otra de enanos líderes y una ultima de enanos generales, se buscará en el censo si existe la cantidad solicitada, de ser asi se creará una mision en la que estaran anotados los que fueron solicitados. Si no hay stock, se informará al usuario.\n");
	printf("\npromover_enanos:\nPromueve a los enanos que cumplan las condiciones para pertenecer a diferentes categorias luego de haber hecho una mision.\n");
	printf("\nlistar_enanos:\nMuestra en pantalla los enanos que pertenecen a la categoria consultada.\n");
}
