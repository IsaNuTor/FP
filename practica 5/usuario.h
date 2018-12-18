#ifndef usuario_h
#define usuario_h

// Inclusi�n de bibliotecas.
#include "listaMensajes.h"

// Declaraci�n de tipos.
typedef struct
{
	string id_usuario;
	tListaMensajes buzonMensajes; // Mensajes sin entregar.
}tDatosUsuario;

typedef tDatosUsuario *tDatUsPtr;

// Prototipos de funciones.
// Inicializar Usuario, establece el nombre de usuario e inicializa el buz�n de mensajes.
bool inicializarUsuario(tDatosUsuario &usuario, ifstream &archivo);

// cargarUsuario: dado un fichero (ya abierto) lee la informaci�n de �l y devuelve un tDatosUsuario.
void cargarUsuario(tDatosUsuario &usuario, ifstream &archivo);

// Guardar usuario en fichero, guarda la informaci�n del usuario en el fichero.
void guardarUsuario(tDatosUsuario &usuario, ofstream &archivo);

// Mostrar usuario por pantalla.
void mostrarUsuarioPorPantalla(const tDatosUsuario &usuario);

#endif