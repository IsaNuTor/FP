// Inclusión de bibliotecas.
#include "listaChats.h"

// Función principal, para realizar las pruebas de las funciones del módulo listaChats.
/*
int main()
{
	ifstream archivo;
	ofstream archivoGuardar;
	tListaChats lista;
	int pos;

	archivo.open("pepe_chats.txt");

	cargarListaChats(lista, archivo, "pepe");
	archivo.close();
	mostrarListaChats(lista);
	cout << lista.cont_chats << endl;

	pos = busquedaLineal(lista, "dcosta");
	cout << pos << endl;
	pos = busquedaLineal(lista, "casillas");
	cout << pos << endl;

	// ordenarListaPorFecha(lista);
	ordenarListaPorNombres(lista);
	archivoGuardar.open("pepeGuardar.txt");
	guardarListaChatsEnFichero(lista, archivoGuardar);
	archivoGuardar.close();

	// Probamos moverChatAlFinal.
	moverAlFinalDeLaListaElChat(lista, 0);
	archivoGuardar.open("pepeGuardar.txt");
	guardarListaChatsEnFichero(lista, archivoGuardar);
	archivoGuardar.close();

	system("Pause");
	return 0;
}
*/

// Funciones.
// Inicializar la lista de chats.
void inicializarListaChats(tListaChats &listaChats)
{
	listaChats.cont_chats = 0;
}

// Cargar lista Chats.
void cargarListaChats(tListaChats &listaChats, ifstream &archivo, string idUsuario)
{
	// Cuerpo de la función.
	inicializarListaChats(listaChats);
	cargarChatDeFichero(listaChats.arrayChats[listaChats.cont_chats], archivo, idUsuario);

	// Mientras sea distinto del centinela y la lista no esté llena, añadimos chat a la lista.
	while((listaChats.arrayChats[listaChats.cont_chats].nombre_chat != "XXX") && (listaChats.cont_chats < MAX_CHATS))
	{
		listaChats.cont_chats++;
		cargarChatDeFichero(listaChats.arrayChats[listaChats.cont_chats], archivo, idUsuario);
	}
}

// Guardar lista Chats.
void guardarListaChatsEnFichero(const tListaChats &listaChats, ofstream &archivo)
{
	for(int i = 0; i < listaChats.cont_chats; i++)
	{
		guardarChat(listaChats.arrayChats[i], archivo);
	}

	archivo << "XXX" << endl;
}

// Búsqueda lineal por nombre.
int busquedaLineal(const tListaChats &listaChats, string nombreBuscado)
{
	// Declaración de variables.
	bool encontrado = false;
	int posicion = 0;

	// Cuerpo de la función.
	while((!encontrado) && (posicion < listaChats.cont_chats))
	{
		if(nombreBuscado == obtenerNombreDeQuienNosEscribe(listaChats.arrayChats[posicion]))
		{
			encontrado = true;
		}
		else
		{
			posicion++;
		}
	}

	if(!encontrado)
	{
		posicion = -1; // Devolveremos -1 en el caso de que no lo hayamos encontrado.
	}

	return posicion;
}

// Añadir chat al final de la lista.
bool anadirChatAlFinalDeLaLista(tListaChats &listaChats, const tChat &chat)
{
	bool lleno = false;

	if(listaChats.cont_chats < MAX_CHATS)
	{
		listaChats.arrayChats[listaChats.cont_chats] = chat;
		listaChats.cont_chats++;
	}
	else
	{
		lleno = true;
		cout << "Lista de chats llena, no se puede insertar el chat." << endl;
	}

	return lleno;
}

// Eliminar chat de la lista de chats, recibe una lista de chats y la posición del elemento que se desea borrar.
void eliminarChat(tListaChats &listaChats, int pos, bool &ok)
{
	if ((pos < 0) || (pos > listaChats.cont_chats - 1))
	{
      ok = false; // Elemento inexistente
	}
	else 
	{
      ok = true;
      desplazarIzqr(listaChats, pos);
	  listaChats.cont_chats--;
   }
}

void desplazarIzqr(tListaChats &listaChats, int pos) 
{
	for (int i = pos; i < listaChats.cont_chats - 1; i++) 
	{
		listaChats.arrayChats[i] = listaChats.arrayChats[i + 1];
    }
}

// moverAlFinal: recibe una lista de chats y la posición del elemento que hay que mover al final.
void moverAlFinalDeLaListaElChat(tListaChats &listaChats, int pos)
{
	// Declaración de variables.
	tChat chat;
	bool ok;

	// Cuerpo de la función.
	// Copiamos ese chat en la variable chat.
	chat = listaChats.arrayChats[pos];

	// Eliminamos ese chat.
	eliminarChat(listaChats, pos, ok);

	// Añadimos el chat al final de la lista.
	anadirChatAlFinalDeLaLista(listaChats, chat);
}

// OrdenarListaPorNombre: recibe una lista de chats y los ordena por nombre.
// Ordenación por insercción con intercambios.
void ordenarListaPorNombres(tListaChats &listaChats)
{
	// Declaración de variables.
	int pos;
	tChat tmp;

	// Cuerpo de la función.
	// Desde el segundo elemento hasta el último...
	for(int i = 1; i < listaChats.cont_chats; i++)
	{
		pos = i;
		// Mientras no al principio y anterior mayor...
		while((pos > 0) && (obtenerNombreDeQuienNosEscribe(listaChats.arrayChats[pos - 1]) > obtenerNombreDeQuienNosEscribe(listaChats.arrayChats[pos])))
		{
			// Intercambiar...
			tmp = listaChats.arrayChats[pos];
			listaChats.arrayChats[pos] = listaChats.arrayChats[pos - 1];
			listaChats.arrayChats[pos - 1] = tmp;
			pos--;
		}
	}
}

// ordenarPorFecha: recibe una lista de chats y los ordena por fecha.
void ordenarListaPorFecha(tListaChats &listaChats)
{
	// Declaración de variables.
	int pos;
	tChat tmp;

	// Cuerpo de la función.
	// Desde el segundo elemento hasta el último...
	for(int i = 1; i < listaChats.cont_chats; i++)
	{
		pos = i;
		// Mientras no al principio y anterior mayor...
		while((pos > 0) && (obtenerFechaDelUltimoMensajeDelChat(listaChats.arrayChats[pos - 1]) > obtenerFechaDelUltimoMensajeDelChat(listaChats.arrayChats[pos])))
		{
			// Intercambiar...
			tmp = listaChats.arrayChats[pos];
			listaChats.arrayChats[pos] = listaChats.arrayChats[pos - 1];
			listaChats.arrayChats[pos - 1] = tmp;
			pos--;
		}
	}
}

// Mostrar listaChats.
void mostrarListaChats(const tListaChats &lista)
{
	for(int i = 0; i < lista.cont_chats; i++)
	{
		mostrarChatPorPantalla(lista.arrayChats[i]);
	}
}

