// Inclusión de bibliotecas.
#include "usuario.h"

// Función principal, para realizar las pruebas de las funciones del módulo usuario.
/*
int main()
{
	ifstream archivo;
	ofstream archivoGuardar;
	tDatosUsuario usuario;

	archivo.open("pruebaUsuario.txt");
	archivoGuardar.open("pruebaUsuarioGuardar.txt");

	cargarUsuario(usuario, archivo);
	mostrarUsuarioPorPantalla(usuario);
	guardarUsuario(usuario, archivoGuardar);

	archivo.close();
	archivoGuardar.close();

	system("Pause");
	return 0;
}
*/

// Funciones.
// Inicializar Usuario, establece el nombre de usuario e inicializa el buzón de mensajes.
bool inicializarUsuario(tDatosUsuario &usuario, ifstream &archivo)
{
	bool vacio = false;

	archivo >> usuario.id_usuario;
	if(usuario.id_usuario == "XXX")
	{
		vacio = true;
	}
	else
	{
		inicializarListaMensajes(usuario.buzonMensajes);
	}

	return vacio;
}

// cargarUsuario: dado un fichero (ya abierto) lee la información de él y devuelve un tDatosUsuario.
void cargarUsuario(tDatosUsuario &usuario, ifstream &archivo)
{
	// Inicializar el usuario.
	if(!inicializarUsuario(usuario, archivo))
	{
		// Cargar el buzón de mensajes, llamando al subprograma cargar del módulo listaMensajes.
		cargarListaMensajes(usuario.buzonMensajes, archivo);
	}
}

// Guardar usuario en fichero, guarda la información del usuario en el fichero.
void guardarUsuario(tDatosUsuario &usuario, ofstream &archivo)
{
	archivo << usuario.id_usuario << endl;
	guardarListaMensajes(usuario.buzonMensajes, archivo);
}

// Mostrar usuario por pantalla.
void mostrarUsuarioPorPantalla(const tDatosUsuario &usuario)
{
	cout << usuario.id_usuario << endl;
	mostrarListaMensajes(usuario.buzonMensajes, usuario.id_usuario);
}
