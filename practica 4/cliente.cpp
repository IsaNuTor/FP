// Inclusión de bibliotecas.
#include "cliente.h"

// Función principal, para realizar las pruebas de las funciones del módulo cliente.
/*
int main()
{
	ifstream archivo;
	string idUsuario, nombreArchivo;
	tDatosCliente cliente;
	tServidor servidor;

	ifstream archivoUsuarios;

	archivoUsuarios.open("usuarios.txt");

	// Cargamos la lista de usuarios en el servidor.
	cargarListaUsuarios(servidor.listaUsuariosServidor, archivoUsuarios);
	archivoUsuarios.close();

	cout << "Usuario (0 para salir): ";
	cin >> idUsuario;
	
	inicializarApp(cliente, idUsuario);

	// ejecutarApp: maneja el menú de usuario.
	ejecutarApp(cliente, servidor, idUsuario);
	
	////////////////////
	if(idUsuario != "0")
	{
		nombreArchivo = idUsuario + "_chats.txt";
		archivo.open(nombreArchivo);

		if(archivo.is_open())
		{
			cargarListaChats(cliente.listaChatsCliente, archivo, idUsuario);
			archivo.close();
		}
			
		colocarMensajesBuzonEnLosChats(cliente, servidor, idUsuario);

		mostrarInterfaz(cliente);
		crearNuevoChatOpcionMenu(cliente, servidor);
		mostrarInterfaz(cliente);

		mostrarListaUsuarios(servidor.listaUsuariosServidor);
	}
	////////////////////
	system("pause");
	return 0;
}
*/

// Funciones.
// inicializarApp: inicializa la estructura de datos.
void inicializarApp(tDatosCliente &cliente, string usuario)
{
	cliente.id_usuario_conectado = usuario;
	inicializarListaChats(cliente.listaChatsCliente);
}

/* colocarMensajesBuzonEnLosChats: solicita al servidor los mensajes sin leer para el usuario y
   los coloca en los chats correspondientes. */
void colocarMensajesBuzonEnLosChats(tDatosCliente &cliente, tServidor &servidor, string usuario)
{
	tListaMensajes mensajes_sin_leer;
	tMensaje mensaje;
	tChat chat;
	int pos_chat;
	bool lleno;

	// Solcitamos al servidor los mensajes sin leer.
	obternerNuevosMensajes(servidor, usuario, mensajes_sin_leer);
	// Para cada mensaje, buscamos el chat.
	for(int i = 0; i < mensajes_sin_leer.cont_mensajes; i++)
	{
		mensaje = DevolverMensaje(mensajes_sin_leer, i);

		pos_chat = busquedaLineal(cliente.listaChatsCliente, mensaje.emisor);

		if(pos_chat == -1)
		{
			// No existe el chat, creamos un nuevo chat, añadimos el mensaje al chat y se añade el chat a la lista de chats de usuario.
			crearChatConMensaje(chat, mensaje);
			lleno = anadirChatAlFinalDeLaLista(cliente.listaChatsCliente, chat);
		}
		else
		{
			// Si existe, se añade el mensaje al chat y se pasa el chat a la ultima posición de la lista.
			anadirMensajeAlFinalDeLista(cliente.listaChatsCliente.arrayChats[pos_chat].mensajesChat, mensaje);

			moverAlFinalDeLaListaElChat(cliente.listaChatsCliente, pos_chat);
		}
	}
}

// Mostrar interfaz.
void mostrarInterfaz(const tDatosCliente &cliente)
{
	// Cuerpo de la función.
	PintarLinea();
	cout << setw(47) << "CHATSAPP 1.0: Chat de " << cliente.id_usuario_conectado << endl;
	PintarLinea();

	if(cliente.listaChatsCliente.cont_chats == 0)
	{
		cout << "                                No hay chats                " << endl;
	}

	for(int i = 0; i < cliente.listaChatsCliente.cont_chats; i++)
	{
		cout << i << ": ";
		mostrarCabecera(cliente.listaChatsCliente.arrayChats[i]);
	}

	mostrarMenu();
}

// Menú
void mostrarMenu()
{
	PintarLinea();
	cout << setw(33) << "Entrar al chat N: c N <intro>" << right << setw(45) << "Crear nuevo chat: n <intro>" << endl;
	cout << setw(35) << "Eliminar el chat N: e N <intro>" << right << setw(43) << "Ordenar chats por nombre: o n <intro>" << endl;
	cout << setw(40) << "Ordenar chats por fecha: o f <intro>" << right << setw(38) << "Salir: s <intro>" << endl;
	PintarLinea();
}

// Opción del menú crear nuevo chat.
void crearNuevoChatOpcionMenu(tDatosCliente &cliente, tServidor &servidor)
{
	string usuario_crear_chat;
	int pos, pos_usuario;
	string texto;
	tMensaje mensaje;
	tChat chat;
	bool lleno;

	// Se solicita el usuario con quién se quiere crear el nuevo chat.
	cout << "Id de usuario con el que crear un nuevo chat: ";
	cin >> usuario_crear_chat;

	// Se comprueba si ya hay un chat creado con ese usuario.
	pos = busquedaLineal(cliente.listaChatsCliente, usuario_crear_chat);

	if(pos == -1) // No existe, lo creamos.
	{
		if(buscaUsuarioEnListaUsuarios(servidor.listaUsuariosServidor, usuario_crear_chat, pos_usuario))
		{
			texto = "Nuevo chat iniciado por " + cliente.id_usuario_conectado;
			crearMensaje(mensaje, cliente.id_usuario_conectado, usuario_crear_chat, texto);

			crearNuevoChatOpcionMenu(chat, cliente.id_usuario_conectado, usuario_crear_chat, mensaje);
			// Se añade el chat a la lista de chats del usuario conectado.
			lleno = anadirChatAlFinalDeLaLista(cliente.listaChatsCliente, chat);

			// Se envía el mensaje al servidor para que lo gestione.
			enviarMensaje(servidor, mensaje);
		}
		else
		{
			cout << "Ese usuario no existe." << endl;
			system("pause");
		}
	}
	else
	{
		// Informamos del error.
		cout << "Ya existe un chat con ese usuario." << endl;
		system("pause");
	}

	system("cls");
}

// ejecutarApp: maneja el menú de usuario.
void ejecutarApp(tDatosCliente &cliente, tServidor &servidor, string idUsuario)
{
	string nombreArchivo;
	ifstream archivo;
	ofstream archivoGuardar;
	char opcion, opcion2, aux;
	int numero;
	bool salir = false, ok = false, error, salirChat, textoIntroducido;

	inicializarApp(cliente, idUsuario);

	nombreArchivo = idUsuario + "_chats.txt";
	archivo.open(nombreArchivo);

	if(archivo.is_open())
	{
		cargarListaChats(cliente.listaChatsCliente, archivo, idUsuario);
		archivo.close();
	}

	colocarMensajesBuzonEnLosChats(cliente, servidor, idUsuario);

	while(!salir)
	{
		salirChat = false;
		error = false;
		textoIntroducido = false;
		// Mostramos la interfaz del menú principal.
		mostrarInterfaz(cliente);

		// Recogemos la opción introducida por el usuario.
		cin >> opcion;

		switch (opcion)
		{
		case 'c':
			{
				cin >> opcion2;
				system("cls");
				numero = (opcion2 - '0');
				if(numero < cliente.listaChatsCliente.cont_chats) // Ese chat no existe, notificamos el error.
				{
					cin.get(aux);

					while((!salirChat) && (!error))
					{
						salirChat = gestionarChat(cliente.listaChatsCliente.arrayChats[numero], servidor, error, textoIntroducido);
						system("cls");
					}
					if(textoIntroducido)
					{
						moverAlFinalDeLaListaElChat(cliente.listaChatsCliente, numero);
					}
				}
				else
				{
					cout << "Ese chat no existe" << endl;
					system("Pause");
					system("cls");
				}
			}break;
		case 'e':
			{
				cin >> opcion2;
				numero = (opcion2 - '0');
				while(!ok)
				{
					eliminarChat(cliente.listaChatsCliente, numero, ok);
					if(!ok)
					{
						cout << "No existe la posicion introducida, vuelva a intentarlo: ";
						cin >> opcion2;
						numero = (opcion2 - '0');
					}
				}
				system("cls");
			}break;
		case 'n':
			{
				crearNuevoChatOpcionMenu(cliente, servidor);
			}break;
		case 'o':
			{
				cin.get(aux);
				cin >> opcion2;
				if(opcion2 == 'n')
				{
					ordenarListaPorNombres(cliente.listaChatsCliente);
				}
				else if(opcion2 == 'f')
				{
					ordenarListaPorFecha(cliente.listaChatsCliente);
				}
				system("cls");
			}break;
		case 's':
			{
				cout << "Ejecucion finalizada" << endl;
				system("pause");
				salir = true;
				system("cls");

				// Guardamos la lista de chats en el archivo.
				archivoGuardar.open(nombreArchivo);
				guardarListaChatsEnFichero(cliente.listaChatsCliente, archivoGuardar);
				archivoGuardar.close();
			}break;
		default: cout << "Opcion incorrecta, vuelve a intentarlo" << endl; break;
		}
	}
}