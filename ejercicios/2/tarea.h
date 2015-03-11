#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Enum para flags en nuestra estructura.
enum {
	// Especifico su identificador y que el primer flag valga 0
	CURSO_TAREA_ATTR_NOMBRE_TAREA,
	CURSO_TAREA_ATTR_DESC_TAREA,
	CURSO_TAREA_ATTR_ID,
	CURSO_TAREA_ATTR_USUARIO,
	CURSO_TAREA_ATTR_PRIORIDAD,
	__CURSO_TAREA_ATTR_MAX
};

// constante para numero maximo de estructuras
// ¿ Para que sirve esta constante de aqui ?
// Entiendo que es para tener el valor maximo de objetos que hay
// que sería el flag MAX de la estructura tarea
#define CURSO_TAREA_ATTR_MAX (__CURSO_TAREA_ATTR_MAX - 1)

// Macro para liberar usando esto
#define xfree(ptr) free((void *) ptr);

struct tarea;

// Funcion para asignar memoria a tarea. (primera direccion entiendo)
struct tarea *curso_tarea_alloc(void);
// Funcion para liberar la memoria a una tarea (Estructura) determinada
void curso_tarea_free(struct tarea *);

// Sirve para saber que atributs de la estructura esta activos o no
bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr);

// Funcion que nos permite liberar recursos de forma controlada
void curso_tarea_attr_unset(struct tarea *t, uint16_t attr);

// ----> Funciones que permiten intruducir atributos de la estructura
// Permite la liberación de atributos de la estructura para asignar otros
// nuevos
void curso_tarea_attr_set_data(struct tarea *t, uint16_t attr,
			      const void *data, uint32_t data_len);

void curso_tarea_attr_set_u32(struct tarea *t, uint16_t attr, uint32_t data);

void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr,
			      const char *data);
// <--- Fin funciones set

// ------> Funciones que devuelven los atributos de una estructura
// Hay que asegurarse primero que sus flags respectivos estan activo
const void * curso_tarea_attr_get_data(struct tarea *t, uint16_t attr);

uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr);

const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr);
// <------ Fin de funciones get

//  Funcion de impresion. Nos ayuda a depurar fallos de una estructura
int curso_tarea_snprintf(char *buf, size_t size, struct tarea *t);

