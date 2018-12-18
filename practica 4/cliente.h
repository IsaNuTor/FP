#ifndef cliente_h
#define cliente_h

// Inclusi�n de bibliotecas.
#include "listaChats.h"

// Declaraci�n de tipos.
typedef struct
{
	string id_usuario_conectado;
	tListaChats listaChatsCliente;
}tDatosCliente;

//Prototipos de funciones.
// Inicializar estructura de tDatosCliente.
void inicializarApp(tDatosCliente &cliente, string usuario);

/* colocarMensajesBuzonEnLosChats: solicita al servidor los mensajes sin leer para el usuario y
   los coloca en los chats correspondientes. */
void colocarMensajesBuzonEnLosChats(tDatosCliente &cliente, tServidor &servidor, string usuario);

// Mostrar interfaz.
void mostrarInterfaz(const tDatosCliente &cliente);

// Men�
void mostrarMenu();

// Opci�n del men� crear nuevo chat.
void crearNuevoChatOpcionMenu(tDatosCliente &cliente, tServidor &servidor);

// ejecutarApp: maneja el men� de usuario.
void ejecutarApp(tDatosCliente &cliente, tServidor &servidor, string idUsuario);

#endif