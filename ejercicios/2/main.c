#include "gestor_tarea.h"
#include <string.h>
#include <assert.h>

int main(void)
{
	struct tarea *t1, *t2;
	struct gestor_tarea *g_tarea;
	char info[4000];

	t1 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE_TAREA, "Mi tarea 1");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DESC_TAREA, "Tarea mia 1");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 0);
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, "Usuario1");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_PRIORIDAD, 2);

	t2 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_NOMBRE_TAREA, "Mi tarea 2");
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_DESC_TAREA, "Tarea mia 2");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_ID, 1);
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_USUARIO, "Usuario2");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_PRIORIDAD, 0);

	g_tarea = curso_gest_tarea_alloc();

	curso_gest_tarea_attr_set_tarea(g_tarea, CURSO_GEST_TAREA_ATTR_TAREA,
					   t1);

	curso_gest_tarea_attr_set_tarea(g_tarea, CURSO_GEST_TAREA_ATTR_TAREA,
					   t2);

	curso_gest_tarea_snprinft(info, sizeof(info), g_tarea);
	printf("%s", info);

	curso_gest_tarea_attr_unset_tarea(g_tarea, 0);

	// Con esta función se ve que se libera bien la tarea borrada.
	// ERROR. De alguna forma sigue mostrandose en pantalla la linea de la tarea
	// borrada. Aunque con valores basura
	curso_gest_tarea_snprinft(info, sizeof(info), g_tarea);
        printf("%s", info);
	// Esto se fastidia al liberar. Doble liberación o algo así
	//curso_gest_tarea_free(g_tarea);
	return 0;
}
