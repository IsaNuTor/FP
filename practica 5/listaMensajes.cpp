// Inclusi�n de bibliotecas.
#include "listaMensajes.h"

// Funci�n principal, para realizar las pruebas de las funciones del m�dulo listaMensajes.
/*
int main()
{
	ifstream archivo;
	ofstream archivoGuardar;
	tListaMensajes lista;
	tMensaje mensaje;

	// Funci�n cargarLista.
	archivo.open("listaMensajes.txt");
	cargarListaMensajes(lista, archivo);
	mostrarListaMensajes(lista);
	archivo.close();
	
	// Funci�n anadirMensajeAlFinalDeLista.
	// Creamos un mensaje.
	crearMensaje(mensaje, "pepe", "casillas", "hola");
	anadirMensajeAlFinalDeLista(lista, mensaje);
	
	// Funci�n guardarLista.
	archivoGuardar.open("listaMensajesGuardados.txt");
	guardarListaMensajes(lista, archivoGuardar);
	archivoGuardar.close();

	// Funci�n consultar el �ltimo elemento.
	mensaje = consultarUltimoElemento(lista);
	mostrarMensaje(mensaje, "pepe");

	system("Pause");
	return 0;
}
*/

// Funciones.
// Inicializar la lista.
void inicializarListaMensajes(tListaMensajes &listaMensajes)
{
	listaMensajes.cont_mensajes = 0;
}

// Cargar ListaMensajes de fichero.
void cargarListaMensajes(tListaMensajes &lista, ifstream &archivo)
{
	tMensaje mensaje;
	int capacidadRedondeadaSiguienteDecena;

	inicializarListaMensajes(lista);
	archivo >> lista.cont_mensajes;

	if(lista.cont_mensajes != 0)
	{
		capacidadRedondeadaSiguienteDecena = ((lista.cont_mensajes / 10) + 1) * 10;

		lista.arrayMensajes = new tMensaje[capacidadRedondeadaSiguienteDecena];
	}

	for(int i = 0; i < lista.cont_mensajes; i++)
	{
		cargarMensaje(mensaje, archivo);
		lista.arrayMensajes[i] = mensaje;
	}
}

// Guardar listaMensajes en fichero.
void guardarListaMensajes(tListaMensajes &lista, ofstream &archivo)
{
	archivo << lista.cont_mensajes << endl;

	for(int i = 0; i < lista.cont_mensajes; i++)
	{
		guardarMensaje(lista.arrayMensajes[i], archivo);
	}

	if(lista.cont_mensajes != 0)
	{
		destruir(lista);
	}
}

// Pintar linea de separaci�n.
void PintarLinea()
{
	for (int i = 0; i < 79; i++)
	{
		cout << LINEA;
	}

	cout << endl;
}

// Mostrar la lista de mensajes.
void mostrarListaMensajes(const tListaMensajes &lista, string usuario)
{
	string emisorMensaje;
	int tamanio;

	for(int i = 0; i < lista.cont_mensajes; i++)
	{
		emisorMensaje = DevolverEmisor(lista.arrayMensajes[i]);

		// Si el emisor del mensaje es el mismo que el usuario que se registra, ajustamos el texto a la derecha.
		if(emisorMensaje == usuario)
		{
			tamanio = tamanioDelMensaje(lista.arrayMensajes[i]);
			cout << right << setw(56 - tamanio);
			mostrarMensaje(lista.arrayMensajes[i]);
			PintarLinea();
		}
		else // Por el contrario, lo ajustamos a la izquierda.
		{
			mostrarMensaje(lista.arrayMensajes[i]);
			PintarLinea();
		}
	}
}

// A�adir un mensaje al final de la listaMensajes.
void anadirMensajeAlFinalDeLista(tListaMensajes &listaMensajes, const tMensaje &mensaje)
{
	if(listaMensajes.cont_mensajes < MAX_MENSAJES)
	{
		listaMensajes.arrayMensajes[listaMensajes.cont_mensajes] = mensaje;

		// Actualizamos el contador.
		listaMensajes.cont_mensajes++;
	}
	else
	{
		redimensionar(listaMensajes);
		listaMensajes.arrayMensajes[listaMensajes.cont_mensajes] = mensaje;

		// Actualizamos el contador.
		listaMensajes.cont_mensajes++;
	}
}

// Consultar el �ltimo elemento de la lista de Mensajes.
tMensaje consultarUltimoElemento(const tListaMensajes &lista)
{
	 return lista.arrayMensajes[lista.cont_mensajes - 1];
}

// Dada una lista de mensajes y una posici�n, devolver el mensaje.
tMensaje DevolverMensaje(const tListaMensajes &lista, int pos)
{
	return lista.arrayMensajes[pos];
}


// Destruir.
void destruir(tListaMensajes &lista) 
{
	delete [] lista.arrayMensajes;
	lista.cont_mensajes = 0;
}

// Redimensionar.
void redimensionar(tListaMensajes &listaMensajes)
{
	// Declaraci�n de variables.
	tPtrMensaje arrayMensajesAux;
	int nuevaCapacidad;

	// Cuerpo de la funci�n.
	// Calculamos la nueva capacidad.
	nuevaCapacidad = (listaMensajes.cont_mensajes * 3) / 2 + 1;

	// Creamos el array auxiliar con la nuevaCapacidad.
	arrayMensajesAux = new tMensaje[nuevaCapacidad];

	// Copiamos los elementos del array al array auxiliar.
	for(int i = 0; i < listaMensajes.cont_mensajes; i++)
	{
		arrayMensajesAux[i] = listaMensajes.arrayMensajes[i];
	}
	
	// Eliminamos el array.
	delete[]listaMensajes.arrayMensajes;

	// Ponemos el puntero en el nuevo array.
	listaMensajes.arrayMensajes = arrayMensajesAux;

	// Actualizamos el contador.
	listaMensajes.capacidad = nuevaCapacidad;
}

