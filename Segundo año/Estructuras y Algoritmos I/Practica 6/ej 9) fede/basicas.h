#ifndef __FBASICAS_H__
#define __FBASICAS_H__

#include <stddef.h>
#include <stdio.h>

/** Enumeraciones utilizables. */
typedef enum{
	MASCULINO,
	FEMENINO
} GENERO;

typedef enum{
	Nombre,
	Apellido,
	Telefono,
	Mail,
	Genero,
	Nacimiento
 } ATRIBUTO;

/** Estructura fecha. */
typedef struct _Fecha{
	int dia, mes, anio;
} Fecha;

/** Estructura de un contacto. */
typedef struct _Contacto{
	char *nombre, *apellido, *telefono, *mail;
	int edad;
	GENERO genero;
	Fecha fechaNacimiento;
} *Contacto;

/** Tipo de la funcion HASH e IGUALDAD */
typedef unsigned (*FuncionHash)(void* clave);

typedef int (*FuncionIgualdad)(void * dato1, void * dato2); 


/** Casilla de la tabla hash. */ 
typedef struct CasillaHash_ {
	Contacto contacto;
	void *clave;
	struct CasillaHash *sig;
} *CasillaHash;

/** Estructura de datos utilizada para la agenda. */
typedef struct {
  CasillaHash *tabla;
  unsigned numElems, capacidad;
  FuncionHash hash;
  FuncionIgualdad igualdad;
  float factorCarga;
} TablaHash;

/** Estructura de datos utilizada para almacenar comandos*/ 
typedef struct SNodo_ {
	char *str;
	struct SNodo_ *sig;
} SNodo;

typedef SNodo* SList;

typedef void (*comand_handler)(TablaHash th, SList comando);

/** Estructura de datos de un comando. */
typedef struct  comando_ {
	char *cmd;
	unsigned nargs;
	comand_handler handler;
} comando;

void imprimirMenu(); /** Imprime el menu. */ 

void imprimirBusqueda(Contacto *contacto);

void buscar_contacto(TablaHash th, SList comando);

void insertar_contacto(Contacto contacto, TablaHash th);

void eliminar_contacto(TablaHash th, SList comando);

void editar_contacto();

void cargar_archivo();

void grabar_archivo();

#endif /* FBASICAS_H */
