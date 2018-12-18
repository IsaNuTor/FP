// Inclusión de bibliotecas.
#include "listaMensajes.h"

// Función principal, para realizar las pruebas de las funciones del módulo listaMensajes.
/*
int main()
{
	ifstream archivo;
	ofstream archivoGuardar;
	tListaMensajes lista;
	tMensaje mensaje;

	// Función cargarLista.
	archivo.open("listaMensajes.txt");
	cargarListaMensajes(lista, archivo);
	mostrarListaMensajes(lista);
	archivo.close();
	
	// Función anadirMensajeAlFinalDeLista.
	// Creamos un mensaje.
	crearMensaje(mensaje, "pepe", "casillas", "hola");
	anadirMensajeAlFinalDeLista(lista, mensaje);
	
	// Función guardarLista.
	archivoGuardar.open("listaMensajesGuardados.txt");
	guardarListaMensajes(lista, archivoGuardar);
	archivoGuardar.close();

	// Función consultar el último elemento.
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

	inicializarListaMensajes(lista);
	archivo >> lista.cont_mensajes;

	if(lista.cont_mensajes > MAX_MENSAJES)
	{
		cout << "Lo siento, hay mas mensajes del maximo, no se pueden guardar todos en la lista" << endl;
	}
	
	for(int i = 0; i < lista.cont_mensajes; i++)
	{
		cargarMensaje(mensaje, archivo);
		lista.arrayMensajes[i] = mensaje;
	}
}

// Guardar listaMensajes en fichero.
void guardarListaMensajes(const tListaMensajes &lista, ofstream &archivo)
{
	archivo << lista.cont_mensajes << endl;

	for(int i = 0; i < lista.cont_mensajes; i++)
	{
		guardarMensaje(lista.arrayMensajes[i], archivo);
	}
}

// Pintar linea de separación.
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

// Añadir un mensaje al final de la listaMensajes.
void anadirMensajeAlFinalDeLista(tListaMensajes &listaMensajes, const tMensaje &mensaje)
{
	if(listaMensajes.cont_mensajes < MAX_MENSAJES)
	{
		listaMensajes.arrayMensajes[listaMensajes.cont_mensajes] = mensaje;
	}
	else
	{
		cout << "La lista esta llena, no se puede introducir el mensaje al final de la lista de mensajes" << endl;
	}

	// Actualizamos el contador.
	listaMensajes.cont_mensajes++;
}

// Consultar el último elemento de la lista de Mensajes.
tMensaje consultarUltimoElemento(const tListaMensajes &lista)
{
	 return lista.arrayMensajes[lista.cont_mensajes - 1];
}

// Dada una lista de mensajes y una posición, devolver el mensaje.
tMensaje DevolverMensaje(const tListaMensajes &lista, int pos)
{
	return lista.arrayMensajes[pos];
}
