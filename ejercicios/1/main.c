#include <string.h>
#include <assert.h>
#include "tarea.h"
// stdio no se incluye aqui. Ya esta en tarea.h

static int test(char *nombre_tarea, char *descripcion, int id, char *usuario, int prioridad){
	struct tarea *punt_tarea;
	char info[250];

	punt_tarea = curso_tarea_alloc();

	// Con esto queda terminado los assert que hacen que funcione bien.
	// AHORA A PENSAR EN LOS ASSERT QUE SE ENCARGUEN DE QUE NO ME BURREEN EL PROGRAMA
	curso_tarea_attr_set_str(punt_tarea, CURSO_TAREA_ATTR_NOMBRE_TAREA, nombre_tarea);
	// Comprobamos que la función get_str no nos devuelva null
	assert(curso_tarea_attr_get_str
		(punt_tarea, CURSO_TAREA_ATTR_NOMBRE_TAREA) != NULL);
	assert(strcmp(curso_tarea_attr_get_str
                     (punt_tarea,CURSO_TAREA_ATTR_NOMBRE_TAREA),
                        nombre_tarea) == 0);

	curso_tarea_attr_set_str(punt_tarea, CURSO_TAREA_ATTR_DESC_TAREA,
				descripcion);
	// Comprobamos que la funcion get_str no nos devuelva null
	assert(curso_tarea_attr_get_str
		      (punt_tarea, CURSO_TAREA_ATTR_DESC_TAREA) != NULL);
	assert(strcmp(curso_tarea_attr_get_str
                     (punt_tarea,CURSO_TAREA_ATTR_DESC_TAREA),
                        descripcion) == 0);

	curso_tarea_attr_set_u32(punt_tarea, CURSO_TAREA_ATTR_ID, id);
	assert(curso_tarea_attr_get_u32(punt_tarea, CURSO_TAREA_ATTR_ID) == id);

	curso_tarea_attr_set_str(punt_tarea, CURSO_TAREA_ATTR_USUARIO, usuario);
	// Comprobamos que la funcion get_str no nos devuelva null
	assert(curso_tarea_attr_get_str
                     (punt_tarea, CURSO_TAREA_ATTR_USUARIO)!= NULL);
	assert(strcmp(curso_tarea_attr_get_str
                     (punt_tarea, CURSO_TAREA_ATTR_USUARIO),
                        usuario) == 0);

	curso_tarea_attr_set_u32(punt_tarea, CURSO_TAREA_ATTR_PRIORIDAD, prioridad);
	assert(curso_tarea_attr_get_u32(punt_tarea, CURSO_TAREA_ATTR_PRIORIDAD) == prioridad);

	curso_tarea_snprintf(info, sizeof(info), punt_tarea);
	printf("%s\n", info);

	curso_tarea_free(punt_tarea);
	return 1;
}

int main(void)
{

	char nombre_tarea[20], descripcion[20], usuario[20];
	int id, prioridad;

	printf("Introduzca los siguientes datos\n");
	printf("Nombre Tarea:\n");
	fgets(nombre_tarea, sizeof(nombre_tarea), stdin);
	printf("Descripcion:\n");
	fgets(descripcion, sizeof(descripcion), stdin);

	printf("Id:\n");
	while(!scanf("%d", &id))
	{
		printf("Introduce un entero\n");
		fflush(stdin);
		getchar();
	}

	printf("Prioridad:\n");
	while(!scanf("%d", &prioridad))
	{
		printf("Introduce un entero\n");
		fflush(stdin);
		getchar();
	}
	printf("Usuario:\n");
	getchar();
	fgets(usuario, sizeof(usuario), stdin);

	return test(nombre_tarea, descripcion, id, usuario, prioridad);
}

