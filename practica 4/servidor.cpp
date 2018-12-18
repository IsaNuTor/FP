/************************************************
 *           ISABEL NÚÑEZ DE LA TORRE           *
 *                  CLASE 1ºC                   *
 ***********************************************/

// Inclusión de bibliotecas.
#include "servidor.h"
#include "cliente.h"

int main()
{
	// Declaración de variables.
	ifstream archivoUsuarios;
	tDatosCliente cliente;
	tServidor servidor;
	string idUsuario;
	ofstream archivoGuardar;
	bool usuario_existe;
	int pos_usuario;

	// Cuerpo de la función.
	archivoUsuarios.open("usuarios.txt");
	
	if(archivoUsuarios.is_open())
	{
		// Cargamos la lista de usuarios en el servidor.
		cargarListaUsuarios(servidor.listaUsuariosServidor, archivoUsuarios);
		archivoUsuarios.close();

		cout << "Usuario (0 para salir): ";
		cin >> idUsuario;

		usuario_existe = buscaUsuarioEnListaUsuarios(servidor.listaUsuariosServidor, idUsuario, pos_usuario);

		while(idUsuario != "0")
		{
			if(usuario_existe == true)
			{
				inicializarApp(cliente, idUsuario);
				ejecutarApp(cliente, servidor, idUsuario);
			}
			else
			{
				cout << "Error, el usuario no existe en el servidor, por favor vuelva a introducirlo." << endl;
			}
			cout << "Usuario (0 para salir): ";
			cin >> idUsuario;
			usuario_existe = buscaUsuarioEnListaUsuarios(servidor.listaUsuariosServidor, idUsuario, pos_usuario);
			system("cls");
		}

		archivoGuardar.open("usuarios.txt");
		guardarListaUsuarios(servidor.listaUsuariosServidor, archivoGuardar);
		archivoGuardar.close();
	}
	else
	{
		cout << "No existe el archivo de usuarios." << endl;
	}
	
	system("Pause");
	return 0;
}
// int main de prueba del módulo servidor.
/*
int main()
{
	ifstream archivo;
	tServidor servidor;
	tMensaje mensaje;
	tListaMensajes listaMensajes;

	archivo.open("usuarios.txt");

	// Cargamos la lista de usuarios en el servidor.
	cargarListaUsuarios(servidor.listaUsuariosServidor, archivo);
	archivo.close();

	mostrarListaUsuarios(servidor.listaUsuariosServidor);

	// Creamos un mensaje, mensaje de pepe a simeone hola.
	crearMensaje(mensaje, "pepe", "simeone", "hola");
	// Enviamos el mensaje al buzon del servidor.
	enviarMensaje(servidor, mensaje);

	obternerNuevosMensajes(servidor, "simeone", listaMensajes);
	mostrarListaMensajes(listaMensajes, "simeone");

	system("pause");
	return 0;
}
*/

// Funciones.
// enviarMensaje: gestiona un mensaje enviado por un usuario, recibe el servidor y el mensaje a enviar.
void enviarMensaje(tServidor &servidor, const tMensaje &mensaje)
{
	int pos_usuario;

	// Busca el usuario destinatario del mensaje en la lista de usuarios del servidor.
	// Buscar usuario, búsqueda binaria.
	if(buscaUsuarioEnListaUsuarios(servidor.listaUsuariosServidor, mensaje.receptor, pos_usuario))
	{
		// Lo hemos encontrado, añadimos el mensaje a la lista mensajes del usuario en el servidor.
		anadirMensajeAlFinalDeLista(servidor.listaUsuariosServidor.arrayUsuarios[pos_usuario].buzonMensajes, mensaje);
	}
	else
	{
		// No lo hemos encontrado, informamos al usuario del error.
		cout << "No se ha encontrado el usuario" << endl;
	}
}

// ObtenerNuevosMensajes: obtiene todos los nuevos mensajes de un usuario.
void obternerNuevosMensajes(tServidor &servidor, string id_usuario, tListaMensajes &mensajesPendientesLeer)
{
	int pos_usuario;

	// Devuelve los mensajes pendientes de leer por el usuario que se encuentran en el servidor.
	// Buscamos en que posición se encuentra el usuario.
	if(buscaUsuarioEnListaUsuarios(servidor.listaUsuariosServidor, id_usuario, pos_usuario))
	{
		// Lo hemos encontrado, cogemos los mensajes, y ponemos el contador a 0.
		mensajesPendientesLeer = servidor.listaUsuariosServidor.arrayUsuarios[pos_usuario].buzonMensajes;
		inicializarListaMensajes(servidor.listaUsuariosServidor.arrayUsuarios[pos_usuario].buzonMensajes);
	}
	else
	{
		// No lo hemos encontrado, informamos al usuario del error.
		cout << "No se ha encontrado el usuario" << endl;
	}
}