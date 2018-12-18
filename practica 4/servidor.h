#ifndef servidor_h
#define servidor_h

// Inclusión de bibliotecas.
#include "listaUsuarios.h"

// Declaración de tipos.
typedef struct
{
	tListaUsuarios listaUsuariosServidor;
}tServidor;

//Prototipos de funciones.
// enviarMensaje: gestiona un mensaje enviado por un usuario, recibe el servidor y el mensaje a enviar.
void enviarMensaje(tServidor &servidor, const tMensaje &mensaje);

// ObtenerNuevosMensajes: obtiene todos los nuevos mensajes de un usuario.
void obternerNuevosMensajes(tServidor &servidor, string id_usuario, tListaMensajes &mensajesPendientesLeer);

#endif