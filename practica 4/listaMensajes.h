#ifndef listaMensajes_h
#define listaMensajes_h

// Inclusión de bibliotecas.
#include "mensaje.h"
#include <iomanip>

// Declaración de constantes.
const int MAX_MENSAJES = 20;
const char LINEA = char(196);

// Declaración de tipos.
typedef tMensaje tArrayMensajes[MAX_MENSAJES];

typedef struct
{
	tArrayMensajes arrayMensajes;
	int cont_mensajes;
}tListaMensajes;

// Prototipos de funciones.
// Inicializar la lista.
void inicializarListaMensajes(tListaMensajes &listaMensajes);

// Cargar ListaMensajes de fichero.
void cargarListaMensajes(tListaMensajes &lista, ifstream &archivo);

// Guardar listaMensajes en fichero.
void guardarListaMensajes(const tListaMensajes &lista, ofstream &archivo);

// Mostrar la lista de mensajes.
void mostrarListaMensajes(const tListaMensajes &lista, string usuario);

// Añadir un mensaje al final de la listaMensajes.
void anadirMensajeAlFinalDeLista(tListaMensajes &listaMensajes, const tMensaje &mensaje);

// Consultar el último elemento de la lista de Mensajes.
tMensaje consultarUltimoElemento(const tListaMensajes &lista);


// Pintar linea de separación.
void PintarLinea();


// Dada una lista de mensajes y una posición, devolver el mensaje.
tMensaje DevolverMensaje(const tListaMensajes &lista, int pos);

#endif