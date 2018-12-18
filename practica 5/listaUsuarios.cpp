// Inclusión de bibliotecas.
#include "listaUsuarios.h"

// Función principal, para realizar las pruebas de las funciones del módulo listaUsuarios.
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
	// Declaración de variables.
	tDatosUsuario usuario;
	tDatosUsuario usuarioInicial;

	// Cuerpo de la función.
	inicializarListaUsuarios(listaUsuarios);
	cargarUsuario(usuario,archivo);
	
	// Mientras sea distinto del centinela y la lista no esté llena, añadimos usuario a la lista.
	while((usuario.id_usuario != "XXX") && (listaUsuarios.cont_usuarios < MAX_USUARIOS))
	{
		insertarUsuario(listaUsuarios, usuario);

		cargarUsuario(usuario,archivo);
	}
}

// Buscar usuario, búsqueda binaria.
bool buscaUsuarioEnListaUsuarios(const tListaUsuarios &usuarios, const string &identidad_usuario, int &pos)
{
	// Declaración de variables.
	int ini, fin, mitad;
	bool encontrado = false;
	ini = 0;
	fin = usuarios.cont_usuarios;

	// Cuerpo de la función.
	while((ini <= fin) && (!encontrado))
	{
		mitad = (ini + fin) / 2;
		
		if(identidad_usuario < usuarios.arrayUsuarios[mitad]->id_usuario)
		{
			fin = mitad - 1;
		}
		else if(usuarios.arrayUsuarios[mitad]->id_usuario < identidad_usuario)
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

bool insertarUsuario(tListaUsuarios &listaUsuarios, const tDatosUsuario &usuario)
{
	// Declaración de variables.
	bool correcto, insertado = false;
	int pos = 0;

	// Cuerpo de la función.
	if(listaUsuarios.cont_usuarios >= MAX_USUARIOS)
	{
		correcto = false; // La lista está llena, no se pueden añadir nuevos usuarios.
	}
	else if(listaUsuarios.cont_usuarios == 0)
	{
		listaUsuarios.arrayUsuarios[0] = new tDatosUsuario(usuario);
		correcto = true;
	}
	else
	{
		// Buscamos la posición del nuevo usuario.
		while((pos < listaUsuarios.cont_usuarios) && (!insertado))
		{
			if(listaUsuarios.arrayUsuarios[pos]->id_usuario < usuario.id_usuario)
			{
				pos++;
			}
			else
			{
				listaUsuarios.arrayUsuarios[listaUsuarios.cont_usuarios] = new tDatosUsuario(usuario);
			    for(int i = listaUsuarios.cont_usuarios; i > pos; i--)
				{
					listaUsuarios.arrayUsuarios[i]->id_usuario = listaUsuarios.arrayUsuarios[i - 1]->id_usuario;
				}
				insertado = true;
			}
		}
		// Insertamos el elemento.
		listaUsuarios.arrayUsuarios[pos] = new tDatosUsuario(usuario);
		correcto = true;
	}
	if(correcto)
	{
		listaUsuarios.cont_usuarios++;
	}

	return correcto;
}

// Guardar lista usuario.
void guardarListaUsuarios(tListaUsuarios &lista, ofstream &archivo)
{
	for(int i = 0; i < lista.cont_usuarios; i++)
	{
		guardarUsuario(*lista.arrayUsuarios[i], archivo);
	}

	archivo << "XXX" << endl;

	destruir(lista);
}

// Mostrar lista usuarios.
void mostrarListaUsuarios(const tListaUsuarios &lista)
{
	for(int i = 0; i < lista.cont_usuarios; i++)
	{
		mostrarUsuarioPorPantalla(*lista.arrayUsuarios[i]);
	}
}

// Destruir.
void destruir(tListaUsuarios &lista) 
{
	for (int i = 0; i < lista.cont_usuarios; i++) 
   {
	   delete lista.arrayUsuarios[i];
   }
	lista.cont_usuarios = 0;
}