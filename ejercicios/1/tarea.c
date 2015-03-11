#include "tarea.h"
#include "string.h"

struct tarea {
	const char *nombre_tarea;
	const char *desc_tarea;
	uint32_t id;
	const char *usuario;
	uint32_t prioridad;
	uint32_t flags;
};

struct tarea *curso_tarea_alloc(void)
{
	// El malloc se encarga de reservar memoria de tamanyo tarea
	// Ademas hace casting a tipo tarea
	return (struct tarea *)malloc(sizeof(struct tarea));
}

void curso_tarea_free(struct tarea * t)
{
	// PREGUNTA. ¿NO HABRIA QUE LIBERAR MEMORIA DE LOS ENTEROS?
	// Entiendo que al liberar la estructura se libera la memoria del entero.
	// Es asi puesto que solo es una poscion de memoria. Las cadenas son varias
	// Con las condiciones if nos aseguramos que liberamos solo si esta
	// activo el atributo de la estructura para que no de error
	if (t->flags & (1 << CURSO_TAREA_ATTR_NOMBRE_TAREA))
		xfree(t->nombre_tarea);
	if (t->flags & (1 << CURSO_TAREA_ATTR_DESC_TAREA))
		xfree(t->desc_tarea);
/*	if (t->flags & (1 << CURSO_TAREA_ATTR_ID))
		xfree(t->id);*/
	if (t->flags & (1 << CURSO_TAREA_ATTR_USUARIO))
		xfree(t->usuario);
/*	if (t->flags & (1 << CURSO_TAREA_ATTR_PRIORIDAD))
		xfree(t->prioridad);*/
	xfree(t);
}

// ####*** TO DO Comentar esto luego
bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr)
{
	return t->flags & (1 << attr);
}

void curso_tarea_attr_unset(struct tarea *t, uint16_t attr)
{
	if (!(t->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (t->nombre_tarea) {
			xfree(t->nombre_tarea);
			t->nombre_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (t->desc_tarea){
			xfree(t->desc_tarea);
			t->desc_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_ID:
		break;
	case CURSO_TAREA_ATTR_USUARIO:
		if (t->usuario){
			xfree(t->usuario);
			t->usuario = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		break;
	}

	// ####*** TO DO ¿Que hace esta linea?
	t->flags |= (1 << attr);
}

void curso_tarea_set_data(struct tarea *t, uint16_t attr, const void *data,
			 uint32_t data_len)
{
	if (attr > CURSO_TAREA_ATTR_MAX)
		return;

	switch (attr)
	{
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (t->nombre_tarea)
			xfree(t->nombre_tarea);

		// ¿Que hacia exactamente el strdup?
		t->nombre_tarea = strdup(data);
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (t->desc_tarea)
			xfree(t->desc_tarea);

		t->desc_tarea = strdup(data);
		break;
	case CURSO_TAREA_ATTR_ID:
		t->id = *((uint32_t *)data);
		break;
	case CURSO_TAREA_ATTR_USUARIO:
		if (t->usuario)
			xfree(t->usuario);

		t->usuario = strdup(data);
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		t->prioridad = *((uint32_t *)data);
		break;
	}

	// ¿Que hacia esta linea?
	t->flags |= (1 << attr);
}

void curso_tarea_attr_set_u32(struct tarea *t, uint16_t  attr, uint32_t data)
{
	// Aqui me gustaría plantearme si cuando se le pasa un char por parametro evitarlo
	// pero por lo visto lo pasa a numero y no crashea. No se como comprobarlo
	curso_tarea_set_data(t, attr, &data, sizeof(uint32_t));
}

void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr, const char *data)
{
	// Si nuestro puntero es nulo no debe llamar a set_data. Daría violación de segmento
	if(data!=NULL){
		curso_tarea_set_data(t, attr, data, 0);
	}
}

const void *curso_tarea_attr_get_data(struct tarea *t, uint16_t attr)
{
	// Con este if nos aseguramos que si no esta activo
	//no podamos coger nada ¿SEGURO?
	if (!(t->flags & (1 << attr)))
		return NULL;

	// ####*** TO DO- Investigar diferencias entre cadena y entero
	switch(attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		return t->nombre_tarea;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		return t->desc_tarea;
	case CURSO_TAREA_ATTR_ID:
		// ¿Por qué se usan los ampersand?
		return &t->id;
	case CURSO_TAREA_ATTR_USUARIO:
		return t->usuario;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		return &t->prioridad;
	}

	// Devolvemos null en caso de que no haya ningun flag activo
	return NULL;
}

uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr){
	const void *ret = curso_tarea_attr_get_data(t, attr);
	// Si es NULL devolvemos 0, si no devolvemos el valor haciendo
	// el casting a uint32
	return ret == NULL ? 0: *((uint32_t *)ret);
}

const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr){
	// Devolvemos la cadena con el atributo attr
	return curso_tarea_attr_get_data(t, attr);
}

int curso_tarea_snprintf(char *buf, size_t size, struct tarea *t)
{
//La tarea número NUMERO_TAREA está enviada por NOMBRE_USUARIO.
//Se llama NOMBRE_TAREA y la descripción es DESCRIPCION_TAREA
	return snprintf(buf, size, "La tarea número %d esta enviada por %s. Se llama %s y la descripcion es %s",
			t->id, t->usuario, t->nombre_tarea, t->desc_tarea);
}

