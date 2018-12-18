#ifndef listaChats_h
#define listaChats_h

// Inclusi�n de bibliotecas.
#include "chat.h"

// Declaraci�n de constantes.
const int MAX_CHATS = 20;

// Declaraci�n de tipos.
typedef tChat tArrayChats[MAX_CHATS];

typedef struct
{
	tArrayChats arrayChats;
	int cont_chats;
}tListaChats;

// Prototipos de funciones.
// Inicializar la lista de chats.
void inicializarListaChats(tListaChats &listaChats);

// Cargar lista Chats.
void cargarListaChats(tListaChats &listaChats, ifstream &archivo, string idUsuario);

// Guardar lista Chats.
void guardarListaChatsEnFichero(const tListaChats &listaChats, ofstream &archivo);

// B�squeda lineal por nombre.
int busquedaLineal(const tListaChats &listaChats, string nombreBuscado);

// A�adir chat al final de la lista.
bool anadirChatAlFinalDeLaLista(tListaChats &listaChats, const tChat &chat);

// Eliminar chat de la lista de chats, recibe una lista de chats y la posici�n del elemento que se desea borrar.
void eliminarChat(tListaChats &listaChats, int pos, bool &ok);

void desplazarIzqr(tListaChats &listaChats, int pos);

// moverAlFinal: recibe una lista de chats y la posici�n del elemento que hay que mover al final.
void moverAlFinalDeLaListaElChat(tListaChats &listaChats, int pos);

// OrdenarListaPorNombre: recibe una lista de chats y los ordena por nombre.
// Ordenaci�n por insercci�n con intercambios.
void ordenarListaPorNombres(tListaChats &listaChats);

// ordenarPorFecha: recibe una lista de chats y los ordena por fecha.
void ordenarListaPorFecha(tListaChats &listaChats);

// Mostrar listaChats.
void mostrarListaChats(const tListaChats &lista);

#endif