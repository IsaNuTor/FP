#ifndef listaUsuarios_h
#define listaUsuarios_h

// Inclusi�n de bibliotecas.
#include "usuario.h"

// Declaraci�n de constantes.
const int MAX_USUARIOS = 20;

// Declaraci�n de tipos.
typedef tDatosUsuario tArrayUsuarios[MAX_USUARIOS];

typedef struct
{
	tArrayUsuarios arrayUsuarios;
	int cont_usuarios;
}tListaUsuarios;

// Prototipos de funciones.
// Inicializar lista usuarios.
void inicializarListaUsuarios(tListaUsuarios &listaUsuarios);

// Cargar lista usuarios.
void cargarListaUsuarios(tListaUsuarios &listaUsuarios, ifstream &archivo);

// Buscar usuario, b�squeda binaria.
bool buscaUsuarioEnListaUsuarios(const tListaUsuarios &usuarios, const string &identidad_usuario, int &pos);

// Insertar usuario en la lista, insercci�n ordenada sin repeticiones.
bool insertarUsuario(tListaUsuarios &usuarios, const tDatosUsuario &usuario);

// Guardar lista usuario.
void guardarListaUsuarios(const tListaUsuarios &lista, ofstream &archivo);

// Mostrar lista usuarios.
void mostrarListaUsuarios(const tListaUsuarios &lista);

#endif