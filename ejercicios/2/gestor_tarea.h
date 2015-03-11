#include "tarea.h"

enum {
	CURSO_GEST_TAREA_ATTR_TAREA,
	CURSO_GEST_TAREA_ATTR_NUM_TAREAS,
	__CURSO_GEST_TAREA_ATTR_MAX
};

// No se pone ; con los define
#define CURSO_GEST_TAREA_ATTR_MAX 10
struct gestor_tarea;
struct gestor_tarea *curso_gest_tarea_alloc(void);
void curso_gest_tarea_free(struct gestor_tarea *g_tarea);
bool curso_gest_tarea_is_set(const struct gestor_tarea *g_tarea, uint16_t attr);
void curso_gest_tarea_attr_unset_tarea(struct gestor_tarea *g_tarea, uint32_t pos);
void curso_gest_tarea_attr_set_tarea(struct gestor_tarea *g_tarea,
				   uint16_t attr, struct tarea *data);
// set_data es privada (static)
// No implemento set_str ni set_u32 puesto que solo vamos a
// manejar array de struct
const void *curso_gest_tarea_attr_get_data(struct gestor_tarea *g_tarea,
					  uint16_t attr, uint32_t pos);
struct tarea *curso_gest_tarea_attr_get_tarea(struct gestor_tarea *g_tarea,
					 uint16_t attr, uint32_t pos);
int curso_gest_tarea_snprinft(char *buf, size_t size,
			    struct gestor_tarea *g_tarea);
