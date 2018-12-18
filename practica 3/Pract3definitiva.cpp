/********************************************
 *               Práctica 3                 *
 *				Color Crush                 *
 *										    *
 * Realizada por: ISABEL NÚÑEZ DE LA TORRE  *  
 * Clase: 1ºC							    *
 ********************************************/

// Inclusión de bibliotecas.
#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h> // La utilizamos para system("cls").
#include <fstream> // Para los archivos.

// Espacio de nombres estándar std.
using namespace std;

// Declaración de constantes.
// La dimensión del tablero.
const int DIM = 8; 
const int MAX_INTENTOS = 2;
// Colores de las fichas con los que vamos a jugar.
const int MAX_COLOR_FICHAS = 4;
// Creamos constantes para los caracteres que necesitamos para generar el tablero.
const char ESQ_SUP_IZQ = char(218), ESQ_SUP_DER = char(191), ESQ_INF_IZQ = char(192), ESQ_INF_DER = char(217),
		   T_GIRADA_IZQ = char(195), T_GIRADA_DER = char(180), T_VERTICAL = char(194), T_REVES = char(193), CRUZ = char(197),
		   LINEA_HORIZONTAL = char(196), LINEA_VERTICAL = char(179), CUADRADITO_FICHA = char(219);
/* Para el modo de ejecución del juego, usamos una constante DEBUG, si está a true, se para la ejecución hasta que el usuario pulse una tecla, en false, la ejecución se para
   durante unos milisegundos */
const bool DEBUG = true;
const int NAP_TIME = 300; // milisegundos de espera 

// Declaración de tipos.
// Color neutro que representa la celda vacía -> negro.
typedef enum { magenta, amarillo, azul, verde, negro }tFicha;
// Array bidimensional de colores
typedef tFicha tTablero[DIM][DIM];
// Creamos otro array bidimensional con booleanos para señalar a 1 los grupos.
typedef bool tTableroAux[DIM][DIM];
typedef struct
{
	int intentos;
	int puntos;
	tTablero tablero;
}tJuego;

typedef enum { arriba, abajo, derecha, izquierda }tDireccion;
typedef struct
{
	int fila;
	int columna;
	tDireccion direccion;
}tMovimiento;

typedef enum 
{
	black, dark_blue, dark_green, dark_cyan, dark_red,
	dark_magenta, dark_yellow, light_gray, dark_gray,
	light_blue, light_green, light_cyan, light_red,
	light_magenta, light_yellow, white
} tColor;


// Prototipos de funciones.
// Generar, pintar y mostrar el tablero.
void setColor(tColor color);
// Genera un color aleatorio tFicha y lo devuelve.
tFicha generarColorAleatorio();
// Genera un tablero, 
void generarTablero(tTablero tablero);
void mostrarPartida(tJuego juego);
void mostrarTableroPorPantalla(const tTablero tablero);
void pintarLineas(int i);
void pintarBordeDeArriba();
void pintarLineasInteriores();
void pintarBordeDeAbajo();
void pintarLineasFichas(const tTablero tablero, int &fila);
void pintarFicha(tColor c_ficha);
tColor conversorFichaColor(tFicha ficha);

// Funciones para comprobar si hay algún grupo a partir de una posición, en horizontal o en vertical.
bool comprobarSiHayGrupoPartiendoDeUnaPosicion(const tTablero tablero, int fila, int columna);
bool comprobarSiColoresFichasSonIguales(tFicha ficha_actual, tFicha ficha_lado);
bool grupoEnFilaConLaFichaPosicion(const tTablero tablero, int fila, int columna);
int grupoHaciaLaDerecha(const tTablero tablero, int fila, int columna);
int grupoHaciaLaIzquierda(const tTablero tablero, int fila, int columna);
bool grupoEnColumnaConLaFichaPosicion(const tTablero tablero, int fila, int columna);
int grupoHaciaArriba(const tTablero tablero, int fila, int columna);
int grupoHaciaAbajo(const tTablero tablero, int fila, int columna);

// Funciones para procesar tablero.
void procesarTablero(tTablero tablero, tTableroAux auxiliar, int &puntos);
void eliminarGruposFichasExistentes(tTablero tablero, const tTableroAux auxiliar);
int procesarFilasTablero(const tTablero tablero, tTableroAux auxiliar_filas);
int procesarColumnasTablero(const tTablero tablero, tTableroAux auxiliar_columnas);
int calcularPuntosGrupoFichas(int numero_fichas_grupo);
// Los huecos.
void llenarHuecosFichasEliminadas(tTablero tablero);
bool comprobarSiQuedanHuecos(const tTablero tablero);


// Nos muestra el tablero auxiliar, para probar que funciona luego borrarrrrrrrr
void mostrarTableroAuxiliar(const tTableroAux auxiliar);
void inicializarTableroAux(tTableroAux tablero_aux);

// Fuciones para comprobar si el movimiento es válido.
void comprobarSiMovimientoUsuarioEsValido(tTablero tablero, tMovimiento movimiento, bool &salir);
void cambiarFichasMovimiento(tTablero tablero, const tMovimiento movimiento);
bool direccionValida(const tDireccion direccion, int &fila, int &columna);
tDireccion conversorCharEnumerado(char letra_direccion);

void jugarPartidaColorCrush(tJuego juego, tMovimiento movimiento, string nombre_usuario);
void jugarPartidaColorCrushMismoTablero(tJuego juego, tMovimiento movimiento, string nombre_usuario);

// Partes Opcionales.
// Puntuaciones.
void actualizarFicheroPuntuaciones(string nombre_usuario, int puntos);
void copiarArchivos(ifstream &archT, ofstream &archU);
//void mostrarPuntuaciones(string nombreArchivo);

// Cargar tablero de archivo.
bool cargarTablero(tJuego &juego);

// Permitir salvar partidas y recuperarlas.
void guardarPartida(const tJuego &juego);
bool cargarPartidaGuardada(tJuego &juego);

// Función principal.
int main()
{
	// Declaración de variables.
	srand(time(NULL));
	
	tJuego juego;
	tMovimiento movimiento;
	movimiento.direccion = arriba;
	// Inicializamos los intentos y los puntos.
	juego.intentos = MAX_INTENTOS;
	juego.puntos = 0;

	string nombre_usuario;
	// Jugamos la partida.
	// Le pedimos el nombre al usuario para las puntuaciones
	cout << "Bienvenid@ a Color Crush! Por favor, introduce tu nombre: ";
	cin >> nombre_usuario;
	cin.sync();

	if(DEBUG)
	{
		jugarPartidaColorCrush(juego, movimiento, nombre_usuario);
	}
	else
	{
		jugarPartidaColorCrushMismoTablero(juego, movimiento, nombre_usuario);
	}
	
	return 0;
}

// Funciones.
void jugarPartidaColorCrushMismoTablero(tJuego juego, tMovimiento movimiento, string nombre_usuario)
{
	// Declaración de variables
	bool cancelar = false;

	// Inicializamos todas las posiciones del tablero_auxiliar a falso.
	tTableroAux tablero_auxiliar = {false};

	// Cuerpo de la función.
	if(cargarTablero(juego))
	{
		do
		{
			cout << endl;
			mostrarPartida(juego);
			procesarTablero(juego.tablero, tablero_auxiliar, juego.puntos);
			Sleep(NAP_TIME);
			system("cls");
		
			do
			{
				cout << endl;
				mostrarPartida(juego);
				Sleep(NAP_TIME);
				system("cls");
			
				while(comprobarSiQuedanHuecos(juego.tablero))
				{
					llenarHuecosFichasEliminadas(juego.tablero);
					cout << endl;
					mostrarPartida(juego);
					Sleep(NAP_TIME);
					system("cls");
				}
				inicializarTableroAux(tablero_auxiliar);
				procesarTablero(juego.tablero, tablero_auxiliar, juego.puntos);
			}while(comprobarSiQuedanHuecos(juego.tablero));

			if(juego.intentos > 0)
			{
				cout << endl;
				mostrarPartida(juego);
				cout << endl;
				comprobarSiMovimientoUsuarioEsValido(juego.tablero, movimiento, cancelar);
			}
			if(!cancelar)
			{
				juego.intentos--;
			}
		
		}while((!cancelar) && (juego.intentos >= 0));


		if(cancelar)
		{
			guardarPartida(juego);
		}
		else
		{
			actualizarFicheroPuntuaciones(nombre_usuario, juego.puntos);
			cout << "Has agotado los intentos, fin de la partida" << endl;
		}
	}
	
	system("pause");
}

void jugarPartidaColorCrush(tJuego juego, tMovimiento movimiento, string nombre_usuario)
{
	// Declaración de variables
	bool cancelar = false;
	// Inicializamos todas las posiciones del tablero_auxiliar a falso.
	tTableroAux tablero_auxiliar = {false};

	// Cuerpo de la función.
	if((cargarPartidaGuardada(juego)) || (cargarTablero(juego)))
	{
		do
		{
			cout << endl;
			mostrarPartida(juego);
			cout << endl;
			procesarTablero(juego.tablero, tablero_auxiliar, juego.puntos);
			system("pause");
			cout << endl;
	
			do
			{
				mostrarPartida(juego);
				cout << endl;
				system("pause");
			
				while(comprobarSiQuedanHuecos(juego.tablero))
				{
					cout << endl;
					llenarHuecosFichasEliminadas(juego.tablero);
					mostrarPartida(juego);
					cout << endl;
					system("pause");
					cout << endl;
				}
				inicializarTableroAux(tablero_auxiliar);
				procesarTablero(juego.tablero, tablero_auxiliar, juego.puntos);
			}while(comprobarSiQuedanHuecos(juego.tablero));

			if(juego.intentos > 0)
			{
				comprobarSiMovimientoUsuarioEsValido(juego.tablero, movimiento, cancelar);
			}
			if(!cancelar)
			{
				juego.intentos--;
			}
		
		}while((!cancelar) && (juego.intentos >= 0));

		if(cancelar)
		{
			guardarPartida(juego);
		}
		else
		{
			actualizarFicheroPuntuaciones(nombre_usuario, juego.puntos);
			cout << "Has agotado los intentos, fin de la partida" << endl;
		}
	}
	system("pause");
}

void setColor(tColor color) 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

tFicha generarColorAleatorio()
{
	// Declaración de variables.
	tFicha color_aleatorio;
	
	// Cuerpo de la función.
	color_aleatorio = tFicha(rand() % MAX_COLOR_FICHAS);

	return color_aleatorio;
}
//	Generar aleatoriamente un tablero
void generarTablero(tTablero tablero)
{
	for(int fila = 0; fila < DIM; fila++)
	{
		for(int columna = 0; columna < DIM; columna++)
		{
			tablero[fila][columna] = generarColorAleatorio();
			cout << tablero[fila][columna] << " "; // quitarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
		}
	}
}

void mostrarPartida(tJuego juego)
{
	cout << setw(DIM + 10) << "Intentos: " << juego.intentos << setw(DIM + 4) << "Puntos: " << juego.puntos << endl;
	mostrarTableroPorPantalla(juego.tablero);
}

void mostrarTableroPorPantalla(const tTablero tablero)
{
	// Declaración de variables.
	int fila_array = 0, numero_filas = DIM;
	 
	// Cuerpo de la función.
	

	for(int i = 0; i <= (DIM * 2); i++)
	{
		if(i % 2 == 0)
		{
			// Pintamos las líneas.
			cout << setw(6);
			pintarLineas(i);
		}
		else
		{
			//Pintamos las fichas, para mostrar el número de la fila, utilizamos un contador numero_filas.
			cout << setw(4) << numero_filas << " ";
			pintarLineasFichas(tablero, fila_array);
			fila_array++;
			numero_filas--;
		}
	}
	// Para poner la numeración de las columnas utilizamos un recorrido for, desde 1 hasta DIM.
	cout << setw(8);
	for(int numero_columnas = 1; numero_columnas <= DIM; numero_columnas++)
	{
		cout << numero_columnas << setw(4);
	}
}

void pintarLineas(int i)
{
	if(i == 0)
	{
		pintarBordeDeArriba();
	}
	else if(i == (DIM * 2))
	{
		pintarBordeDeAbajo();
	}
	else
	{
		pintarLineasInteriores();
	}
}

void pintarBordeDeArriba()
{
	cout << ESQ_SUP_IZQ;
	for(int k = 0; k < (DIM - 1); k++)
	{
		cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << T_VERTICAL;
	}
	cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << ESQ_SUP_DER << endl;
}

void pintarLineasInteriores()
{
	cout << T_GIRADA_IZQ;
	for(int k = 0; k < (DIM - 1); k++)
	{
		cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << CRUZ;
	}
	cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << T_GIRADA_DER << endl;
}

void pintarBordeDeAbajo()
{
	cout << ESQ_INF_IZQ;
	for(int k = 0; k < (DIM - 1); k++)
	{
		cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << T_REVES;
	}
	cout << LINEA_HORIZONTAL << LINEA_HORIZONTAL << LINEA_HORIZONTAL << ESQ_INF_DER << endl;
}

void pintarLineasFichas(const tTablero tablero, int &fila)
{
	tColor color_ficha;
	
	cout << LINEA_VERTICAL;

	for(int columna = 0; columna < DIM; columna++)
	{
		color_ficha = conversorFichaColor(tablero[fila][columna]);
		pintarFicha(color_ficha);
	}
	cout << endl;
}

void pintarFicha(tColor c_ficha)
{
		setColor(c_ficha);
		cout << CUADRADITO_FICHA << CUADRADITO_FICHA << CUADRADITO_FICHA;
		setColor(white);
		cout << LINEA_VERTICAL;
}

tColor conversorFichaColor(tFicha ficha)
{
	// Declaración de variables.
	tColor color;

	// Cuerpo de la función.
	switch(ficha)
	{
	case 0: color = light_magenta; break;
	case 1: color = light_yellow;  break;
	case 2: color = dark_cyan;     break;
	case 3: color = dark_green;    break;
	case 4: color = black;
	}
	return color;
}

// Funciones para comprobar si hay algún grupo a partir de una posición, en horizontal o vertical.
// Primero lo hacemos con la posición horizontal.
bool comprobarSiHayGrupoPartiendoDeUnaPosicion(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	bool existe_grupo_fila = false, existe_grupo_columna = false, existe_grupo = false;
	
	// Cuerpo de la función.
	existe_grupo_fila = grupoEnFilaConLaFichaPosicion(tablero, fila, columna);
	existe_grupo_columna = grupoEnColumnaConLaFichaPosicion(tablero, fila, columna);

	
	if((existe_grupo_fila) || (existe_grupo_columna))
	{
		existe_grupo = true;
	}

	return existe_grupo;
}

bool comprobarSiColoresFichasSonIguales(tFicha ficha_actual, tFicha ficha_lado)
{
	// Declaración de variables.
	bool iguales = false;

	// Cuerpo de la función.
	if(ficha_actual == ficha_lado)
	{
		iguales = true;
	}

	return iguales;
}

bool grupoEnFilaConLaFichaPosicion(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	bool existe_grupo = false;
	int fichas_alineadas_fila = 0, fichas_derecha = 0, fichas_izquierda = 0;
	
	// Cuerpo de la función.
	/* Sumamos las fichas alineadas por la derecha, las fichas alineadas por la iquierda, le restamos 1 porque hemos sumado
	   dos veces la misma ficha  y obtenemos*/
	fichas_derecha = grupoHaciaLaDerecha(tablero, fila, columna);
	fichas_izquierda = grupoHaciaLaIzquierda(tablero,fila,columna);
	
	fichas_alineadas_fila = fichas_derecha + fichas_izquierda + 1;

	if(fichas_alineadas_fila >= 3)
	{
		existe_grupo = true;
	}
	
	return existe_grupo;
}

int grupoHaciaLaDerecha(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	int fichas_alineadas_derecha = 0;
	tFicha actual, siguiente;

	// Cuerpo de la función.
	if(columna < (DIM - 1))
	{
		actual = tablero[fila][columna];
		siguiente = tablero[fila][columna + 1];
	}
	while((columna < (DIM - 1)) && (comprobarSiColoresFichasSonIguales(actual, siguiente)))
	{
		
		if(comprobarSiColoresFichasSonIguales(actual, siguiente))
		{
			fichas_alineadas_derecha++;
		}

		columna++;

		if(columna < (DIM - 1))
		{
			siguiente = tablero[fila][columna + 1];
		}
	}
	
	return fichas_alineadas_derecha;
}

int grupoHaciaLaIzquierda(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	tFicha actual, anterior;
	int fichas_alineadas_izquierda = 0;

	// Cuerpo de la función.
	if(columna > 0)
	{
		actual = tablero[fila][columna];
		anterior = tablero[fila][columna - 1];
	}
	while((columna > 0)  && (comprobarSiColoresFichasSonIguales(actual, anterior)))
	{
		
		if(comprobarSiColoresFichasSonIguales(actual, anterior))
		{
			fichas_alineadas_izquierda++;
		}

		columna--;

		if(columna > 0)
		{
			anterior = tablero[fila][columna - 1];
		}
	}
	return fichas_alineadas_izquierda;
}

bool grupoEnColumnaConLaFichaPosicion(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	bool existe_grupo = false;
	int fichas_alineadas_columna = 0, fichas_arriba = 0, fichas_abajo = 0;

	// Cuerpo de la función.
	// Sumamos las fichas alineadas por arriba, las fichas alineadas por abajo, le sumamos uno más por la ficha en la que estamos.
	fichas_arriba = grupoHaciaArriba(tablero,fila,columna);
	fichas_abajo = grupoHaciaAbajo(tablero, fila, columna);

	fichas_alineadas_columna = fichas_arriba + fichas_abajo + 1;
		
	if(fichas_alineadas_columna >= 3)
	{
		existe_grupo = true;
	}
	
	return existe_grupo;
}

int grupoHaciaArriba(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	int fichas_alineadas_arriba = 0;
	tFicha actual, anterior;

	// Cuerpo de la función.
	if(fila > 0)
	{
		actual = tablero[fila][columna];
		anterior = tablero[fila - 1][columna];
	}
	while((fila > 0) && (comprobarSiColoresFichasSonIguales(actual, anterior)))
	{
		
		if(comprobarSiColoresFichasSonIguales(actual, anterior))
		{
			fichas_alineadas_arriba++;
		}

		fila--;

		if(fila > 0)
		{
			anterior = tablero[fila - 1][columna];
		}
	}
	return fichas_alineadas_arriba;
}

int grupoHaciaAbajo(const tTablero tablero, int fila, int columna)
{
	// Declaración de variables.
	int fichas_alineadas_abajo = 0;
	tFicha actual, anterior;

	// Cuerpo de la función.
	if(fila < (DIM - 1))
	{
		actual = tablero[fila][columna];
		anterior = tablero[fila + 1][columna];
	}
	while((fila < (DIM - 1)) && (comprobarSiColoresFichasSonIguales(actual, anterior)))
	{
		
		if(comprobarSiColoresFichasSonIguales(actual, anterior))
		{
			fichas_alineadas_abajo++;
		}

		fila++;

		if(fila < (DIM - 1))
		{
			anterior = tablero[fila + 1][columna];
		}
	}

	return fichas_alineadas_abajo;
}

// Funciones de procesar tablero.
void procesarTablero(tTablero tablero, tTableroAux auxiliar, int &puntos)
{
	int puntos_filas, puntos_columnas;

	puntos_columnas = procesarColumnasTablero(tablero, auxiliar);
	puntos_filas = procesarFilasTablero(tablero, auxiliar);
	// Ponemos a negro los grupos de fichas.
	eliminarGruposFichasExistentes(tablero, auxiliar);

	puntos = puntos + puntos_filas + puntos_columnas;
}

void eliminarGruposFichasExistentes(tTablero tablero, const tTableroAux auxiliar)
{
	for(int fila = 0; fila < DIM; fila++)
	{
		for(int columna = 0; columna < DIM; columna++)
		{
			if(auxiliar[fila][columna])
			{
				tablero[fila][columna] = negro;
			}
		}
	}
}

int procesarFilasTablero(const tTablero tablero, tTableroAux auxiliar_filas)
{
	int j, fichas, grupo_fichas, puntos_grupos_filas = 0;

	for(int i = 0; i < DIM; i++)
	{
		j = 0;
		while(j < (DIM - 1))
		{
			fichas = grupoHaciaLaDerecha(tablero, i ,j);
			grupo_fichas = 1 + fichas;

			if(grupo_fichas >= 3)
			{
				for(int k = j; k < (j + grupo_fichas); k++)
				{
					auxiliar_filas[i][k] = true;
				}
				// Calculamos los puntos.
				puntos_grupos_filas = puntos_grupos_filas + calcularPuntosGrupoFichas(grupo_fichas);
			}
			j = j + 1 + fichas;
		}
	}
	return puntos_grupos_filas;
}

int procesarColumnasTablero(const tTablero tablero, tTableroAux auxiliar_columnas)
{
	int j, fichas, grupo_fichas, puntos_grupos_columnas = 0;

	for(int i = 0; i < DIM; i++)
	{
		j = 0;
		while(j < (DIM - 1))
		{
			fichas = grupoHaciaAbajo(tablero, j, i);
			grupo_fichas = 1 + fichas;

			if(grupo_fichas >= 3)
			{
				for(int k = j; k < (j + grupo_fichas); k++)
				{
					auxiliar_columnas[k][i] = true;
				}
				// Calculamos los puntos.
				puntos_grupos_columnas = puntos_grupos_columnas + calcularPuntosGrupoFichas(grupo_fichas);
			}
			j = j + 1 + fichas;
		}
	}
	return puntos_grupos_columnas;
}

int calcularPuntosGrupoFichas(int numero_fichas_grupo)
{
	// Declaración de variables.
	int puntos = 0;

	// Cuerpo de la función.
	if(numero_fichas_grupo == 3)
	{
		puntos = 3;
	}
	else if(numero_fichas_grupo == 4)
	{
		puntos = 8;
	}
	else if(numero_fichas_grupo >= 5)
	{
		puntos = 15;
	}

	return puntos;
}

// Funciones para llenar los huecos.

void llenarHuecosFichasEliminadas(tTablero tablero)
{
	int posicion, j;
	tFicha ficha_superior;
	bool hueco_lleno;

	for(int i = 0; i < DIM; i++)
	{
		posicion = 0;
		j = 0;
		hueco_lleno = false;

		while((j < DIM) && (!hueco_lleno))
		{
			if(tablero[j][i] == negro) // Buscamos la posicion del hueco.
			{
				for(int k = posicion; k > 0; k--)
				{
					tablero[k][i] = tablero[k-1][i];
				}
				ficha_superior = generarColorAleatorio();
				tablero[0][i] = ficha_superior;
				hueco_lleno = true;
			}
			else
			{
				posicion++;
			}
			j++;
		}
	}
}

bool comprobarSiQuedanHuecos(const tTablero tablero)
{
	bool quedan_huecos = false;

	for(int i = 0; i < DIM; i++)
	{
		for(int j = 0; j < DIM; j++)
		{
			if(tablero[i][j] == negro)
			{
				quedan_huecos = true;
			}
		}
	}

	return quedan_huecos;
}
// Para hacer las pruebas luego borrarrrrrrrrrrrrr
void mostrarTableroAuxiliar(const tTableroAux auxiliar)
{
	for(int i = 0; i < DIM; i++)
	{
		for(int j = 0; j < DIM; j++)
		{
			cout << auxiliar[i][j] << " ";
		}
	}
}

void inicializarTableroAux(tTableroAux tablero_aux)
{
	for(int i = 0; i < DIM; i++)
	{
		for(int j = 0; j < DIM; j++)
		{
			tablero_aux[i][j] = false;
		}
	}
}

// Comprobar si el movimiento de usuario es válido.
void comprobarSiMovimientoUsuarioEsValido(tTablero tablero, tMovimiento movimiento, bool &salir)
{
	// Declaración de variables.
	char letra_direccion;
	bool movimiento_valido = false;

	// Cuerpo de la función.
	do
	{
		cout << "Introduce fila, columna y letra de direcci\xa2n (A, B, D o I; 0 para cancelar): ";
		cin >> movimiento.fila;

		if(movimiento.fila == 0)
		{
			salir = true;
		}
		else
		{
			cin >> movimiento.columna >> letra_direccion;
			movimiento.direccion = conversorCharEnumerado(letra_direccion);

			// Comprobamos que la fila y la columna esté entre 1 y DIM.
			if(((movimiento.fila < 0) || (movimiento.fila > (DIM + 1))) || ((movimiento.columna < 0) || (movimiento.columna > (DIM + 1))))
			{
				movimiento_valido = false;
				cout << "Error, el movimiento no es v\xa0lido. " << endl;
			}
			else if((movimiento.direccion != arriba) && (movimiento.direccion != abajo) && (movimiento.direccion != derecha) && (movimiento.direccion != izquierda))
			{
				movimiento_valido = false;
				cout << "Error, el movimiento no es v\xa0lido, la direcci\xan es incorrecta. " << endl;
			}
			else if(!direccionValida(movimiento.direccion, movimiento.fila, movimiento.columna))
			{
				movimiento_valido = false;
				cout << "Error, la direcci\xa2n del movimiento no es correcta." << endl;
			}
			else
			{
				// Para comprobar si se forma algún grupo con ese movimiento, primero realizamos el movimiento y comprobamos
				// Dependiendo de la dirección, así cambiaremos las fichas.
				cambiarFichasMovimiento(tablero, movimiento);

				if(comprobarSiHayGrupoPartiendoDeUnaPosicion(tablero, movimiento.fila, movimiento.columna))
				{
					movimiento_valido = true;
				}
				else
				{
					// Para comprobar tenemos que dar la dicha posición y eso dependera de la direccion que hayamos tomado
					switch(movimiento.direccion)
					{
					case 0: movimiento.fila = movimiento.fila - 1;       break;
					case 1: movimiento.fila = movimiento.fila + 1;       break;
					case 2: movimiento.columna = movimiento.columna + 1; break;
					case 3: movimiento.columna = movimiento.columna - 1;
					}
					if(comprobarSiHayGrupoPartiendoDeUnaPosicion(tablero, movimiento.fila, movimiento.columna))
					{
						movimiento_valido = true;
					}
					else // como el movimiento no es correcto, deshacemos el movimiento.
					{
						if(movimiento.direccion == arriba)
						{
							movimiento.direccion = abajo;
						}
						else if(movimiento.direccion == abajo)
						{
							movimiento.direccion = arriba;
						}
						else if(movimiento.direccion == derecha)
						{
							movimiento.direccion = izquierda;
						}
						else
						{
							movimiento.direccion = derecha;
						}
						cambiarFichasMovimiento(tablero, movimiento);
					}
				}
			}
		}
	}while((!movimiento_valido) && (!salir));
}

bool direccionValida(const tDireccion direccion, int &fila, int &columna)
{
	bool direccion_correcta = false;
	// Nuestra fila va a ser igual a la Dimensión - el numero de fila que introduzcan.
	fila = DIM - fila;
	columna = columna - 1;

	switch(direccion)
	{
	case 0: 
		{
			if(fila == 0)
			{
				direccion_correcta = false;
			}
			else
			{
				direccion_correcta = true;
			}
		}; break;
	case 1:
		{
			if(fila == (DIM - 1))
			{
				direccion_correcta = false;
			}
			else
			{
				direccion_correcta = true;
			}
		}; break;
	case 2:
		{
			if(columna == (DIM - 1))
			{
				direccion_correcta = false;
			}
			else
			{
				direccion_correcta = true;
			}
		}; break;
	case 3:
		{
			if(columna == 0)
			{
				direccion_correcta = false;
			}
			else
			{
				direccion_correcta = true;
			}
		}
	}

	return direccion_correcta;
}

void cambiarFichasMovimiento(tTablero tablero, const tMovimiento movimiento)
{
	tFicha ficha_color_en_el_que_estamos;

	switch(movimiento.direccion)
	{
	case 0: 
		{
			ficha_color_en_el_que_estamos = tablero[movimiento.fila - 1][movimiento.columna];
			tablero[movimiento.fila - 1][movimiento.columna] = tablero[movimiento.fila][movimiento.columna];
			tablero[movimiento.fila][movimiento.columna] = ficha_color_en_el_que_estamos;
		}break; 
	case 1: 
		{
			ficha_color_en_el_que_estamos = tablero[movimiento.fila + 1][movimiento.columna];
			tablero[movimiento.fila + 1][movimiento.columna] = tablero[movimiento.fila][movimiento.columna]; 
			tablero[movimiento.fila][movimiento.columna] = ficha_color_en_el_que_estamos;
		}break;
	case 2:
		{
			ficha_color_en_el_que_estamos = tablero[movimiento.fila][movimiento.columna + 1];
			tablero[movimiento.fila][movimiento.columna + 1] = tablero[movimiento.fila][movimiento.columna];
			tablero[movimiento.fila][movimiento.columna] = ficha_color_en_el_que_estamos;
		}break;
	case 3:
		{
			ficha_color_en_el_que_estamos = tablero[movimiento.fila][movimiento.columna - 1];
			tablero[movimiento.fila][movimiento.columna - 1] = tablero[movimiento.fila][movimiento.columna];
			tablero[movimiento.fila][movimiento.columna] = ficha_color_en_el_que_estamos;
		}
	}
}

tDireccion conversorCharEnumerado(char letra_direccion)
{
	tDireccion direccion = arriba;

	switch(letra_direccion)
	{
	case 'a': 
	case 'A': direccion = arriba; break;
	case 'b':
	case 'B': direccion = abajo; break;
	case 'd':
	case 'D': direccion = derecha; break;
	case 'i':
	case 'I': direccion = izquierda;
	}

	return direccion;
}

// Partes Opcionales.
/* Mantener un archivo con las puntuaciones de los distintos jugadores. Solicitar el nombre del jugador
   al principio y actualizar los datos de cada usuario que juegue. */
void actualizarFicheroPuntuaciones(string nombre_usuario, int puntos)
{
	// Declaración de variables.
	ifstream archivoUsuarios, archivoT;
	ofstream archivoTmp, archivoU;
	string dato_nombre;
	int total_puntos;
	bool encontrado = false;

	// Cuerpo de la función.
	archivoTmp.open("tmp.txt");
	archivoUsuarios.open("usuarios.txt");

	if(archivoUsuarios.is_open())
	{
		archivoUsuarios >> dato_nombre; // Leemos el primer nombre.

		while(dato_nombre != "XXX") // Mientras el nombre sea distinto del centinela.
		{
			if(dato_nombre != nombre_usuario)
			{
				archivoUsuarios >> total_puntos;
				archivoTmp << dato_nombre << " " << total_puntos << endl;
			}
			else // Hemos encontrado el nombre
			{
				archivoUsuarios >> total_puntos;
				archivoTmp << dato_nombre << " " << total_puntos + puntos << endl;
				encontrado = true;
			}
			archivoUsuarios >> dato_nombre;
		}
		if(encontrado == false) // El nombre no existe, hay que añadirlo al final del archivo.
		{
			archivoTmp << nombre_usuario << " " << puntos << endl;
		}

		archivoTmp << "XXX" << endl;
	}
	else
	{
		archivoTmp << nombre_usuario << " " << puntos << endl;
		archivoTmp << "XXX" << endl;
	}

	archivoTmp.close();
	archivoUsuarios.close();

	archivoT.open("tmp.txt");
	archivoU.open("usuarios.txt");

	copiarArchivos(archivoT, archivoU);
}

void copiarArchivos(ifstream &archT, ofstream &archU)
{
	string dato;
	int a;

	archT >> dato;
	while(dato != "XXX")
	{
		archT >> a;
		archU << dato << " " << a << endl;
		archT >> dato;
	}
	archU << "XXX" << endl;

	archT.close();
	archU.close();
}
/*
void mostrarPuntuaciones(string nombreArchivo)
{
	// Declaración de variables.
	ifstream archivo;
	string dato;
	int a;

	// Cuerpo de la función.
	archivo.open(nombreArchivo); // Abrimos el archivo.
	
	if(archivo.is_open())
	{
		cout << "Usuario" << setw(11) << "Puntos" << endl;
		archivo >> dato;
		while(dato != "XXX")
		{
			archivo >> a;
			cout << dato  << setw(11) << a;
			archivo >> dato;
		}
	}
	else
	{
		cout << "Error, no se ha podido abrir el archivo." << endl;
	}
}
*/
bool cargarTablero(tJuego &juego)
{
	// Declaración de variables.
	bool cargadoCorrectamente = false;
	string nomb_tablero;
	int color_leido;
	ifstream archivo;

	cout << "Nombre del tablero(Ej: tablero1.txt)(generar -> para generar aleatoriamente): " << endl;
	cin >> nomb_tablero;

	if(nomb_tablero == "generar") // El usuario no ha pulsado intro
	{
		generarTablero(juego.tablero);
		cargadoCorrectamente = true;
	}
	else
	{
		archivo.open(nomb_tablero);

		if(archivo.is_open())
		{
			for(int fila = 0; fila < DIM; fila++)
			{
				for(int columna = 0; columna < DIM; columna++)
				{
					archivo >> color_leido;
					juego.tablero[fila][columna] = tFicha(color_leido);
				}
			}
			cargadoCorrectamente = true;
		}
		else
		{
			cargadoCorrectamente = false;
			cout << "Error, el archivo no se ha podido abrir" << endl;
		}

		archivo.close();
	}

	return cargadoCorrectamente;
}

void guardarPartida(const tJuego &juego)
{
	char guardar_partida;
	bool contestada = false;
	ofstream archivo;

	cout << "Juego cancelado!!!, ¨deseas guardar la partida?(S/N): ";
	cin >> guardar_partida;
	do
	{
		switch(guardar_partida)
		{
		case 's':
		case 'S':
			{
				contestada = true;
				archivo.open("partidaGuardada.txt");
				archivo << juego.intentos << " " << juego.puntos << endl;
				for(int i = 0; i < DIM; i++)
				{
					for(int j = 0; j < DIM; j++)
					{
						archivo << juego.tablero[i][j] << " ";
					}
					archivo << endl;
				}
				archivo.close();
				cout << "Partida guardada, bye! " << char(2) << endl;
			}break;
		case 'n':
		case 'N': 
			{
				cout << "Partida no guardada, bye! " << char(2) << endl; 
				contestada = true;
			}break;
		default: 
			{
				cout << "No me has contestado, ¨deseas guardar la partida?(S/N): ";
				cin >> guardar_partida;
			}break;
		}
	}while(!contestada);
}

bool cargarPartidaGuardada(tJuego &juego)
{
	char cargar_partida;
	int color_leido;
	bool contestada = false, partida_cargada = false;
	ifstream archivo;

	cout << "¨Deseas cargar la partida guardada?(S/N): ";
	cin >> cargar_partida;
	do
	{
		switch(cargar_partida)
		{
		case 's':
		case 'S':
			{
				contestada = true;
				archivo.open("partidaGuardada.txt");
				if(archivo.is_open())
				{
					archivo >> juego.intentos >> juego.puntos;
					
					for(int fila = 0; fila < DIM; fila++)
					{
						for(int columna = 0; columna < DIM; columna++)
						{
							archivo >> color_leido;
							juego.tablero[fila][columna] = tFicha(color_leido);
						}
					}
					partida_cargada = true;
					archivo.close();
					cout << "Partida cargada" << endl;
				}
				else
				{
					cout << "Error, el archivo no se ha podido abrir" << endl;
				}
				partida_cargada = true;
			}break;
		case 'n':
		case 'N': 
			{
				cout << "Partida no cargada" << endl; 
				contestada = true;
			}break;
		default: 
			{
				cout << "No me has contestado, ¨deseas guardar la partida?(S/N): ";
				cin >> cargar_partida;
			}break;
		}
	}while(!contestada);

	return partida_cargada;
}