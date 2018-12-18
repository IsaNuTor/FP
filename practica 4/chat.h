#ifndef chat_h
#define chat_h

// Inclusión de bibliotecas.
#include "listaMensajes.h"
#include "servidor.h"

// Declaración de tipos.
typedef struct
{
	string nombre_chat; // Identificador del usuario con el que se habla.
	string id_chat; // identificador del usuario al que pertenece el chat.
	tListaMensajes mensajesChat;
}tChat;

// Prototipos de funciones.
// Inicializar, establece nombre_chat, id_chat e inicializa la lista de mensajes.
bool inicializarChat(tChat &chat, ifstream &archivo);

// Cargar chat de fichero.
void cargarChatDeFichero(tChat &chat, ifstream &archivo, string id_chat);

// Guardar chat en fichero.
void guardarChat(const tChat &chat, ofstream &archivo);

// Mostrar cabecera.
void mostrarCabecera(const tChat &chat);

// Mostrar chat por pantalla.
void mostrarChatPorPantalla(const tChat &chat);

// Mostrar mensajes del chat.
void mostrarMensajesChat(const tChat &chat);


// Devolver nombre de quien nos ha enviado el mensaje.
string obtenerNombreDeQuienNosEscribe(const tChat &chat);

// Devuelve la fecha del último mensaje del buzón.
tFecha obtenerFechaDelUltimoMensajeDelChat(const tChat & chat);

// gestionarChat.
bool gestionarChat(tChat &chat, tServidor &servidor, bool &error, bool &ha_introducido_texto);


// CrearChatConMensaje(módulo cliente).
void crearChatConMensaje(tChat &chat, const tMensaje &mensaje);

void crearNuevoChatOpcionMenu(tChat &chat, string id_chat, string nombre_chat, const tMensaje &mensaje);

#endif