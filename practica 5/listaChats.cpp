// Inclusi�n de bibliotecas.
#include "listaChats.h"

// Funci�n principal, para realizar las pruebas de las funciones del m�dulo listaChats.
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
	int capacidadRedondeadaSiguienteDecena;

	// Cuerpo de la funci�n.
	inicializarListaChats(listaChats);
	archivo >> listaChats.cont_chats;

	if(listaChats.cont_chats != 0)
	{
		capacidadRedondeadaSiguienteDecena = ((listaChats.cont_chats / 10) + 1) * 10;

		listaChats.arrayChats= new tChat[capacidadRedondeadaSiguienteDecena];
	}
	for(int i = 0; i < listaChats.cont_chats; i++)
	{
		cargarChatDeFichero(listaChats.arrayChats[i], archivo, idUsuario);
	}
}

// Guardar lista Chats.
void guardarListaChatsEnFichero(tListaChats &listaChats, ofstream &archivo)
{
	archivo << listaChats.cont_chats << endl;

	for(int i = 0; i < listaChats.cont_chats; i++)
	{
		guardarChat(listaChats.arrayChats[i], archivo);
	}

	if(listaChats.cont_chats != 0)
	{
		destruir(listaChats);
	}
}

// B�squeda lineal por nombre.
int busquedaLineal(const tListaChats &listaChats, string nombreBuscado)
{
	// Declaraci�n de variables.
	bool encontrado = false;
	int posicion = 0;

	// Cuerpo de la funci�n.
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

// A�adir chat al final de la lista.
void anadirChatAlFinalDeLaLista(tListaChats &listaChats, const tChat &chat)
{
	if(listaChats.cont_chats < MAX_CHATS)
	{
		listaChats.arrayChats[listaChats.cont_chats] = chat;
		listaChats.cont_chats++;
	}
	else
	{
		redimensionar(listaChats);
		listaChats.arrayChats[listaChats.cont_chats] = chat;
		listaChats.cont_chats++;
	}
}

// Eliminar chat de la lista de chats, recibe una lista de chats y la posici�n del elemento que se desea borrar.
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

// moverAlFinal: recibe una lista de chats y la posici�n del elemento que hay que mover al final.
void moverAlFinalDeLaListaElChat(tListaChats &listaChats, int pos)
{
	// Declaraci�n de variables.
	tChat chat;
	bool ok;

	// Cuerpo de la funci�n.
	// Copiamos ese chat en la variable chat.
	chat = listaChats.arrayChats[pos];

	// Eliminamos ese chat.
	eliminarChat(listaChats, pos, ok);

	// A�adimos el chat al final de la lista.
	anadirChatAlFinalDeLaLista(listaChats, chat);
}

// OrdenarListaPorNombre: recibe una lista de chats y los ordena por nombre.
// Ordenaci�n por insercci�n con intercambios.
void ordenarListaPorNombres(tListaChats &listaChats)
{
	// Declaraci�n de variables.
	int pos;
	tChat tmp;

	// Cuerpo de la funci�n.
	// Desde el segundo elemento hasta el �ltimo...
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
	// Declaraci�n de variables.
	int pos;
	tChat tmp;

	// Cuerpo de la funci�n.
	// Desde el segundo elemento hasta el �ltimo...
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

// Destruir.
void destruir(tListaChats &lista) 
{
	delete [] lista.arrayChats;
	lista.cont_chats = 0;
}

// Redimensionar.
void redimensionar(tListaChats &listaChats)
{
	// Declaraci�n de variables.
	tPtrChat arrayChatsAux;
	int nuevaCapacidad;

	// Cuerpo de la funci�n.
	// Calculamos la nueva capacidad.
	nuevaCapacidad = (listaChats.cont_chats * 3) / 2 + 1;

	// Creamos el array auxiliar con la nuevaCapacidad.
	arrayChatsAux = new tChat[nuevaCapacidad];

	// Copiamos los elementos del array al array auxiliar.
	for(int i = 0; i < listaChats.cont_chats; i++)
	{
		arrayChatsAux[i] = listaChats.arrayChats[i];
	}
	
	// Eliminamos el array.
	delete[]listaChats.arrayChats;

	// Ponemos el puntero en el nuevo array.
	listaChats.arrayChats = arrayChatsAux;

	// Actualizamos el contador.
	listaChats.capacidad = nuevaCapacidad;
}