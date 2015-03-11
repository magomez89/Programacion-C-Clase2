#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea{
	struct tarea *array_tarea[10];
	uint32_t num_tareas;
	uint32_t flags;
};

struct gestor_tarea *curso_gest_tarea_alloc(void)
{
	return (struct gestor_tarea *)malloc(sizeof(struct gestor_tarea));
}

void curso_gest_tarea_free(struct gestor_tarea *g_tarea)
{
	int i;
	// Liberamos cada elemento de nuestro array_tarea
	// llamando a curso_tarea_free
	for (i = 0; i < g_tarea->num_tareas; i++)
	{
		curso_tarea_free(g_tarea->array_tarea[i]);
	}
	xfree(g_tarea);
}

bool curso_gest_tarea_is_set(const struct gestor_tarea *g_tarea, uint16_t attr)
{
	return g_tarea->flags & (1 << attr);
}

void curso_gest_tarea_attr_unset_tarea(struct gestor_tarea *g_tarea, uint32_t pos)
{
	int i;
	// Controlamos que la posición  a hacer unset sea mayor que
	// 0 y menor a num_coches. Si no es así return y salimos
	if (pos > 0 && pos < g_tarea->num_tareas)
		return;

	// curso_tarea_free(g_tarea->array_tarea[pos]);
	// Recolocamos el array_tareas. En la última posición tiene que salir un elemento repetido
	for ( i = pos; i < (g_tarea->num_tareas -1); i++)
	{
		g_tarea->array_tarea[pos] = g_tarea->array_tarea[pos+1];
	}
	g_tarea->num_tareas--;
	// Liberamos de memoria la última posición del array
	curso_tarea_free(g_tarea->array_tarea[g_tarea->num_tareas -1]);

}

// set_data es privada (static)
static void curso_gest_tarea_set_data(struct gestor_tarea *g_tarea,
				      uint16_t attr, const void *data)
{
	int pos_a_cambiar;
	struct tarea *aux_tarea;
	if (attr > CURSO_GEST_TAREA_ATTR_MAX)
		return;

	switch (attr)
	{
	case CURSO_GEST_TAREA_ATTR_TAREA:
		if (g_tarea->num_tareas > 10)
		{
			printf("El garaje esta lleno\n");
			break;
		}
		pos_a_cambiar = curso_gest_tarea_devuelve_pos_mayor_prioridad(g_tarea, data);
		// Introducimos nuevo coche en ultima posición del array
		if (pos_a_cambiar == -1 )
			g_tarea->array_tarea[g_tarea->num_tareas] = (struct tarea *)data;
		else
		{
			printf("Tarea nueva en posicion %d\n", pos_a_cambiar);
			aux_tarea = curso_tarea_alloc();
			aux_tarea =  curso_gest_tarea_attr_get_tarea(g_tarea,
                                         CURSO_GEST_TAREA_ATTR_TAREA, pos_a_cambiar);
			g_tarea->array_tarea[pos_a_cambiar] = (struct tarea *)data;
			g_tarea->array_tarea[g_tarea->num_tareas] = aux_tarea;
		}
		g_tarea->num_tareas++;
		break;
	}
	g_tarea->flags |= (1 << attr);

}

int  curso_gest_tarea_devuelve_pos_mayor_prioridad(const struct gestor_tarea *g_tarea, const void *data)
{
	int i;
	struct tarea *tarea_nueva = (struct tarea *)data;
	for (i = 0; i < g_tarea->num_tareas; i++)
	{
		if (curso_tarea_attr_get_u32(g_tarea->array_tarea[i],
					 CURSO_TAREA_ATTR_PRIORIDAD) >
		    curso_tarea_attr_get_u32(tarea_nueva, CURSO_TAREA_ATTR_PRIORIDAD))
			return i;
	}
	return -1;
}

void curso_gest_tarea_attr_set_tarea(struct gestor_tarea *g_tarea,
				   uint16_t attr, struct tarea *data)
{
	curso_gest_tarea_set_data(g_tarea, attr, data);
}

// No implemento set_str ni set_u32 puesto que solo vamos a
// manejar array de struct

const void *curso_gest_tarea_attr_get_data(struct gestor_tarea *g_tarea,
					  uint16_t attr, uint32_t pos)
{
	if (!(g_tarea->flags & (1 << attr)))
		return NULL;

	switch (attr)
	{
	case CURSO_GEST_TAREA_ATTR_NUM_TAREAS:
		return &g_tarea->num_tareas;
	case CURSO_GEST_TAREA_ATTR_TAREA:
		return g_tarea->array_tarea[pos];
	}
	return NULL;
}

struct tarea *curso_gest_tarea_attr_get_tarea(struct gestor_tarea *g_tarea,
					 uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gest_tarea_attr_get_data(g_tarea, attr, pos);
}

int curso_gest_tarea_snprinft(char *buf, size_t size,
			    struct gestor_tarea *g_tarea)
{
	int i, ret = 0;
	for (i = 0; i< g_tarea->num_tareas; i++)
	{
		ret += curso_tarea_snprintf(buf + ret, size - ret,
					    g_tarea->array_tarea[i]);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
