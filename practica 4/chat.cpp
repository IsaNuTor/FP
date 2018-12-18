// Inclusión de bibliotecas.
#include "chat.h"

// Función principal, para realizar las pruebas de las funciones del módulo chat.
/*
int main()
{
	ifstream archivo;
	ofstream archivoGuardar;
	tChat chat;

	archivo.open("chatPrueba.txt");
	cargarChatDeFichero(chat, archivo, "pepe");
	archivo.close();
	
	mostrarCabecera(chat);
	mostrarMensajesChat(chat);

	archivoGuardar.open("chatPrueba.txt");
	guardarChat(chat, archivoGuardar);
	archivoGuardar.close();

	system("Pause");
	return 0;
}
*/
// Funciones.
// Inicializar, establece nombre_chat, id_chat e inicializa la lista de mensajes.
bool inicializarChat(tChat &chat, ifstream &archivo, string id_chat)
{
	bool vacio = false;

	archivo >> chat.nombre_chat;

	if(chat.nombre_chat == "XXX")
	{
		vacio = true;
	}
	else
	{
		chat.id_chat = id_chat;
		inicializarListaMensajes(chat.mensajesChat);
	}

	return vacio;
}

// Cargar chat de fichero.
void cargarChatDeFichero(tChat &chat, ifstream &archivo, string id_chat)
{
	// Inicializar chat.
	if(!inicializarChat(chat, archivo, id_chat))
	{
		// Cargar el buzón de mensajes, llamando al subprograma cargar del módulo listaMensajes.
		cargarListaMensajes(chat.mensajesChat, archivo);
	}
}

// Guardar chat en fichero.
void guardarChat(const tChat &chat, ofstream &archivo)
{
	archivo << chat.nombre_chat << endl;
	guardarListaMensajes(chat.mensajesChat, archivo);
}

// Mostrar cabecera.
void mostrarCabecera(const tChat &chat)
{
	// Declaración de variables.
	tMensaje mensaje_chat;

	cout << chat.nombre_chat << endl << "        ";
	mensaje_chat = consultarUltimoElemento(chat.mensajesChat);
	mostrarMensaje(mensaje_chat);

	PintarLinea();
}

// Mostrar chat por pantalla.
void mostrarChatPorPantalla(const tChat &chat)
{
	cout << chat.nombre_chat << endl;
	mostrarListaMensajes(chat.mensajesChat, chat.id_chat);
}

// Mostrar mensajes del chat.
void mostrarMensajesChat(const tChat &chat)
{
	// Cuerpo de la función.
	PintarLinea();
	cout << setw(38) << "CHAT CON " << chat.nombre_chat << endl;
	PintarLinea();
	cout << endl;

	mostrarListaMensajes(chat.mensajesChat, chat.id_chat);

	PintarLinea();
}


// Devolver nombre de quien nos ha enviado el mensaje.
string obtenerNombreDeQuienNosEscribe(const tChat &chat)
{
	return chat.nombre_chat;
}

// Devuelve la fecha del último mensaje del buzón.
tFecha obtenerFechaDelUltimoMensajeDelChat(const tChat & chat)
{
	tFecha fecha;
	tMensaje mensaje;
	
	mensaje = consultarUltimoElemento(chat.mensajesChat);

	fecha = DevuelveFechaDelMensaje(mensaje);

	return fecha;
}

// gestionarChat.
bool gestionarChat(tChat &chat, tServidor &servidor, bool &error, bool &ha_introducido_texto)
{
	string texto_introducido = " ";
	bool salir = false;
	tMensaje mensaje;
	error = false;

	// Muestra la interfaz del chat.
	mostrarMensajesChat(chat);

	// Recoge el texto introducido por el usuario.
	cout << "Escribe aqui ($salir$ para salir): ";
	getline(cin, texto_introducido);

	if(texto_introducido == "$salir$") 
	{
		salir = true;
		system("cls");
	}
	else
	{
		if(chat.mensajesChat.cont_mensajes < MAX_MENSAJES)
		{
			ha_introducido_texto = true;
			// Creamos un nuevo mensaje con el texto introducido.
			crearMensaje(mensaje, chat.id_chat, chat.nombre_chat, texto_introducido);
			// Añadimos el mensaje a la lista de mensajes del chat.
			anadirMensajeAlFinalDeLista(chat.mensajesChat, mensaje);
			// Enviamos el mensaje al servidor(enviarMensaje del módulo servidor).
			enviarMensaje(servidor, mensaje);
		}
		else
		{
			error = true;
			cout << "No se pueden anadir mas mensajes al chat." << endl;
			cout << "Se ha superado la capacidad de la lista de mensajes" << endl;
			system("pause");
		}
	}

	return salir;
}


// CrearChatConMensaje(módulo cliente).
void crearChatConMensaje(tChat &chat, const tMensaje &mensaje)
{
	chat.id_chat = mensaje.receptor;
	chat.nombre_chat = mensaje.emisor;

	inicializarListaMensajes(chat.mensajesChat);
	anadirMensajeAlFinalDeLista(chat.mensajesChat, mensaje);
}

void crearNuevoChatOpcionMenu(tChat &chat, string id_chat, string nombre_chat, const tMensaje &mensaje)
{
	chat.id_chat = id_chat;
	chat.nombre_chat = nombre_chat;

	inicializarListaMensajes(chat.mensajesChat);
	anadirMensajeAlFinalDeLista(chat.mensajesChat, mensaje);
}