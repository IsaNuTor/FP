// Inclusi�n de bibliotecas.
#include "listaUsuarios.h"

// Funci�n principal, para realizar las pruebas de las funciones del m�dulo listaUsuarios.
/*
int main()
{
	tListaUsuarios lista;
	ifstream archivo;
	ofstream archivoGuardar;
	int pos;

	// Probamos cargar lista usuarios.
	archivo.open("usuarios.txt");
	cargarListaUsuarios(lista, archivo);
	mostrarListaUsuarios(lista);
	buscaUsuarioEnListaUsuarios(lista, "casillas", pos);
	cout << pos << endl;
	buscaUsuarioEnListaUsuarios(lista, "pepe", pos);
	cout << pos << endl;
	archivo.close();
	// Probamos guardar lista.
	archivoGuardar.open("usuarios.txt");
	guardarListaUsuarios(lista, archivoGuardar);
	archivoGuardar.close();
	
	system("Pause");
	return 0;
}
*/

// Funciones.
// Inicializar lista usuarios.
void inicializarListaUsuarios(tListaUsuarios &listaUsuarios)
{
	listaUsuarios.cont_usuarios = 0;
}

// Cargar lista usuarios.
void cargarListaUsuarios(tListaUsuarios &listaUsuarios, ifstream &archivo)
{
	// Declaraci�n de variables.
	tDatosUsuario usuario;

	// Cuerpo de la funci�n.
	inicializarListaUsuarios(listaUsuarios);
	cargarUsuario(usuario,archivo);
	
	// Mientras sea distinto del centinela y la lista no est� llena, a�adimos usuario a la lista.
	while((usuario.id_usuario != "XXX") && (listaUsuarios.cont_usuarios < MAX_USUARIOS))
	{
		insertarUsuario(listaUsuarios, usuario);
		cargarUsuario(usuario,archivo);
	}
}

// Buscar usuario, b�squeda binaria.
bool buscaUsuarioEnListaUsuarios(const tListaUsuarios &usuarios, const string &identidad_usuario, int &pos)
{
	// Declaraci�n de variables.
	int ini, fin, mitad;
	bool encontrado = false;
	ini = 0;
	fin = usuarios.cont_usuarios;

	// Cuerpo de la funci�n.
	while((ini <= fin) && (!encontrado))
	{
		mitad = (ini + fin) / 2;
		
		if(identidad_usuario < usuarios.arrayUsuarios[mitad].id_usuario)
		{
			fin = mitad - 1;
		}
		else if(usuarios.arrayUsuarios[mitad].id_usuario < identidad_usuario)
		{
			ini = mitad + 1;
		}
		else
		{
			encontrado = true;
		}
	}
	if(encontrado)
	{
		pos = mitad;
	}
	else
	{
		pos = ini;
	}

	return encontrado;
}

// Insertar usuario en la lista, insercci�n ordenada sin repeticiones.
bool insertarUsuario(tListaUsuarios &usuarios, const tDatosUsuario &usuario)
{
	// Declaraci�n de variables.
	int pos;

	// Cuerpo de la funci�n.
	if((!buscaUsuarioEnListaUsuarios(usuarios, usuario.id_usuario, pos)) && (usuarios.cont_usuarios < MAX_USUARIOS))
	{
		int i = usuarios.cont_usuarios;

		while(i > pos)
		{
			usuarios.arrayUsuarios[i] = usuarios.arrayUsuarios[i - 1];
			i--;
		}

		usuarios.cont_usuarios++;
		usuarios.arrayUsuarios[i] = usuario; // insertamos el usuario.
		return true;
	}
	else
	{
		return false; // Ese usuario ya est� en la lista.
	}
}

// Guardar lista usuario.
void guardarListaUsuarios(const tListaUsuarios &lista, ofstream &archivo)
{
	for(int i = 0; i < lista.cont_usuarios; i++)
	{
		guardarUsuario(lista.arrayUsuarios[i], archivo);
	}

	archivo << "XXX" << endl;
}

// Mostrar lista usuarios.
void mostrarListaUsuarios(const tListaUsuarios &lista)
{
	for(int i = 0; i < lista.cont_usuarios; i++)
	{
		mostrarUsuarioPorPantalla(lista.arrayUsuarios[i]);
	}
}