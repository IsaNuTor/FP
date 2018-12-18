#ifndef mensaje_h
#define mensaje_h

// Inclusi�n de bibliotecas.
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

// Declaraci�n de tipos.
typedef time_t tFecha;

typedef struct
{
	string emisor;
	string receptor;
	tFecha fecha;
	string texto;
}tMensaje;

// Prototipos de funciones.
// Mostrar la fecha por pantalla en el formato (A�o/Mes/Dia, Hora/Mins/Segs)
void mostrarFecha(tFecha fecha);

// crearMensaje: a partir de un emisor, un receptor y un texto, crea un tMensaje.
void crearMensaje(tMensaje &mensaje, string emisor, string receptor, string texto);

// Mostrar mensaje por pantalla: recibe un tMensaje y lo muestra por pantalla.
void mostrarMensaje(const tMensaje &mensaje);

// cargarMensaje: recibe el archivo de entrada y devuelve el mensaje le�do.
void cargarMensaje(tMensaje &mensaje, ifstream &archivo);

// guardarMensaje: recibe el archivo de salida y el mensaje a guardar.
void guardarMensaje(const tMensaje &mensaje, ofstream &archivo);


// Funci�n que nos devuelva el tama�o del mensaje.
int tamanioDelMensaje(const tMensaje &mensaje);

// Devuelve el emisor del mensaje.
string DevolverEmisor(const tMensaje &mensaje);


// Funci�n que nos devuelve la fecha de un mensaje.
tFecha DevuelveFechaDelMensaje(const tMensaje &mensaje);

#endif