// Inclusi�n de bibliotecas.
#include "mensaje.h"

// Funci�n principal, para realizar las pruebas de las funciones del m�dulo mensaje.
/*
int main()
{
	tMensaje mensaje;
	ifstream archivo;
	ofstream archivoGuardar;

	// Funci�n mostrar fecha.
	cout << time(0) << endl;  // Nos lo muestra en n�mero.
	mostrarFecha(1409682684); // Nos lo muestra en formato fecha y hora.
	cout << endl;

	// Funci�n crearMensaje y mostrar por pantalla.
	crearMensaje(mensaje, "pepe", "casillas", "hola");
	mostrarMensaje(mensaje);

	// Funci�n cargarMensaje y GuardarMensaje.
	archivo.open("mensajes.txt");
	archivoGuardar.open("mensajesGuardados.txt");
	if(archivo.is_open())
	{
		cargarMensaje(mensaje, archivo);

		while(mensaje.emisor != "XXX")
		{
			guardarMensaje(mensaje, archivoGuardar);
			cargarMensaje(mensaje, archivo);
		}

		archivo.close();
		archivoGuardar.close();
	}
	else
	{
		cout << "El archivo no se ha podido abrir" << endl;
	}

	system("Pause");
	return 0;
}
*/

// Funciones.
// Mostrar la fecha por pantalla en el formato (A�o/Mes/Dia, Hora/Mins/Segs)
void mostrarFecha(tFecha fecha)
{
	tm ltm;
	localtime_s(&ltm, &fecha);
	cout << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	cout << ", " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec;
}

// crearMensaje: a partir de un emisor, un receptor y un texto, crea un tMensaje.
void crearMensaje(tMensaje &mensaje, string emisor, string receptor, string texto)
{
	mensaje.emisor = emisor;
	mensaje.receptor = receptor;
	mensaje.fecha = time(0);
	mensaje.texto = texto;
}

// Mostrar mensaje por pantalla.
void mostrarMensaje(const tMensaje &mensaje)
{
	cout << mensaje.emisor << " <";
	mostrarFecha(mensaje.fecha);
	cout << ">: " << mensaje.texto << endl;
}

// cargarMensaje: recibe el archivo de entrada y devuelve el mensaje le�do.
void cargarMensaje(tMensaje &mensaje, ifstream &archivo)
{
	char aux;

	archivo >> mensaje.emisor;
	archivo >> mensaje.fecha;
	archivo.get(aux); // Leemos el espacio en blanco, para que no lo coga abajo en el string del texto.
	getline(archivo, mensaje.texto);
	// El cursor al finalizar pasa a la siguiente l�nea.
}

// guardarMensaje: recibe el archivo de salida y el mensaje a guardar.
void guardarMensaje(const tMensaje &mensaje, ofstream &archivo)
{
	archivo << mensaje.emisor << " " << mensaje.fecha << " " << mensaje.texto << endl;
}


// Funci�n que nos devuelva el tama�o del mensaje.
int tamanioDelMensaje(const tMensaje &mensaje)
{
	return mensaje.texto.size();
}

// Devuelve el emisor del mensaje.
string DevolverEmisor(const tMensaje &mensaje)
{
	return mensaje.emisor;
}


// Funci�n que nos devuelve la fecha de un mensaje.
tFecha DevuelveFechaDelMensaje(const tMensaje &mensaje)
{
	return mensaje.fecha;
}