#ifndef __ENANOS_H__
#define __ENANOS_H__
#define MAX_NOMBRE 50
#define MAX_RANGO 50
#define MAX_DESCRIPCION 200
#define	IGUALES 0

typedef struct enano{
	char nombre[MAX_NOMBRE];
	int edad;
	int cantidad_misiones;
	int id_rango;
} enano_t;

typedef struct rango{
	int id;
	char nombre[MAX_RANGO];
	char descripcion[MAX_DESCRIPCION];
} rango_t;

void actualizar_censo (const char* nombre_mision);

void integrantes_mision (int cant_guerreros, int cant_lideres, int cant_generales, const char nombre_mision[MAX_NOMBRE]);

void promover_enanos ();

void listar_enanos (int id_rango);

void mostrar_ayuda ();

#endif