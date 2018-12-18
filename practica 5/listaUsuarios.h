#ifndef listaUsuarios_h
#define listaUsuarios_h

// Inclusión de bibliotecas.
#include "usuario.h"

// Declaración de constantes.
const int MAX_USUARIOS = 50;

// Declaración de tipos.
typedef tDatUsPtr tArrayUsuarios[MAX_USUARIOS];

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

// Buscar usuario, búsqueda binaria.
bool buscaUsuarioEnListaUsuarios(const tListaUsuarios &usuarios, const string &identidad_usuario, int &pos);

// Insertar usuario en la lista, insercción ordenada sin repeticiones.
bool insertarUsuario(tListaUsuarios &usuarios, const tDatosUsuario &usuario);

// Guardar lista usuario.
void guardarListaUsuarios(tListaUsuarios &lista, ofstream &archivo);

// Mostrar lista usuarios.
void mostrarListaUsuarios(const tListaUsuarios &lista);


// Destruir.
void destruir(tListaUsuarios &lista);


#endif