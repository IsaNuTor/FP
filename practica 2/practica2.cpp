/*****************************************************************************
 * Práctica realizada por: Isabel Núñez de la Torre *
 ****************************************************************************/
// Práctica 2 Mastermind.

// Inclusión de bibliotecas.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

// Espacio de nombres estándar std.
using namespace std;

// Declaración de constantes.
const int N_FICHAS = 4, MAX_INTENTOS = 30, MAX_COLORES = 6;
const bool SIN_REPETICION = true; // Si lo queremos poner con repetición, ponemos SIN_REPETICION = false.
const int PUNTO_POSICION = 5, PUNTO_COLOR = 1, PUNTOS_GANAR_JUEGO = 100; // Las puntuaciones.
// X son los intentos que tienen que pasar para obtener pista e Y son el máximo de pistas que puedes conseguir.
const int X = 5, Y = 2;

// Declaración de tipos.
typedef enum {rojo, azul, verde, negro, granate, marron} tColores;
typedef tColores tCodigo[N_FICHAS]; // Array de valores del tipo enumerado.
typedef bool tAciertosFallos[N_FICHAS]; // Lo utilizamos para la versión 2, comprobar las posiciones y colores acertados.
typedef char tSinRepeticion[N_FICHAS]; // Lo creamos para comprobar que los colores elegidos aleatoriamente no se repitan.
typedef int tComprobarPista[Y]; // Lo creamos para que no salgan pistas repetidas, parte opcional de la versión 2.

// Prototipos de funciones.
// Versión 1.
int menu(); // Función menú.
void codigoAleatorio(string &codigo); // Genera un código aleatorio y lo devuelve en un parámetro.
void codigoAleatorioSinRepeticion(string &codigo2); // Genera código aleatorio con ninguno repetido y lo devuelve en un parámetro.
void ComprobarSiColorHaSalido(char &a, tSinRepeticion auxiliar);
// Conversores.
tColores conversorDeLetraEnumerado(char letra); // Conversor de letra a enumerado.
char conversorDeEnumeradoLetra(tColores color); // Conversor de enumerado a letra. 
void jugarMastermind(int &intentos, string nombre_usuario); // Lleva el juego y devuelve el nº de intentos en un parámetro.
/* Pide y lee el código del jugador, sino es correcto sale error y se lo vuelve a pedir, salimos de la función cuando cancela sea 
   true es decir, cuando el usuario introduce 0, o bien cuando pide pista, cuando el usuario introduce !, y sino es ninguno de 
   estos casos, el usuario a introducido bien el código, lo escribimos en el array jugada, por eso no ponemos el array con const */
void leerCodigoJugador(tCodigo jugada, bool &cancela, bool &pista);
void mostrarArchivo(string nombrArch); // Muestra el contenido de un archivo por pantalla.
void escribirCodigoSecuenciaEnArray(tCodigo nombreArray, string secuencia);
void comprobarColoresCorrectos(const tCodigo secreto, const tCodigo jugada, int &posiciones_acertadas, int &colores_acertados);
void mostrarMovimientoJugador(tCodigo jugada, int &intentos_jugadas, int posicion_acertada, int color_acertado, int &puntos_juego);

// Versión 2.
int puntuacionPartida(int posiciones_correctas, int colores_correctos); // Calcula la puntuación de la jugada y la devuelve.
string conversorEnumeradoColor(tColores color); // Conversor de enumerado a nombre de color(cadena).
void darPista(tCodigo secretoArray, int &posicion_pista, string &cadena, tComprobarPista pistas, int &j);

// Versión 3.
void actualizarFicheroPuntuaciones(string nombre_usuario, int pJugada, int pGanada, int puntos);
void copiarArchivos(ifstream &archT, ofstream &archU);
void mostrarPuntuaciones(string nombreArchivo);

// Función principal.
int main()
{
	// Declaración de variables.
	int intentos_jugador, opcion;
	string nombre_jugador;

	// Cuerpo de la función.
	cout << "Bienvenido a Mastermind! Por favor, introduce tu nombre: ";
	cin >> nombre_jugador;
	cin.sync();

	cout << "Hola " << nombre_jugador << "!" << endl;
	do
	{
		intentos_jugador = 0;
		opcion = menu();

		switch(opcion)
		{
		case 1: jugarMastermind(intentos_jugador, nombre_jugador); break;
		case 2: mostrarPuntuaciones("usuarios.txt");		
		}
		
	}while(opcion != 0);

	return 0;
}

// Funciones.
void jugarMastermind(int &intentos, string nombre_usuario)
{
	// Declaración de variables.
	string codigo_secreto;
	tCodigo secreto, jugada; 
	tComprobarPista posPistas;
	bool salir = false, pedirPista, codigoAcertado = false;
	int fichas_posicion_correcta, colores_acertados_jugador, puntos_partida = 0, partida_ganada = 0, partida_jugada = 0;
	int acumulador_pistas = 0, pistas_gastadas = 0, veces = 0, posicion_de_la_pista = 0, posArray = 0;
	string cadena_color;
	srand(time(NULL));
		
	// Cuerpo de la función.
	if((N_FICHAS < 1) || (N_FICHAS > MAX_COLORES))
	{
		cout << "Error, el n\xa3mero de fichas no es correcto." << endl;
		salir = true;
	}
	if(!salir)
	{
		if(!SIN_REPETICION) // Si es con repetición, entra dentro del if,en cambio si es sin repetición nos vamos al else.
		{
			codigoAleatorio(codigo_secreto);// Genera un código aleatorio y lo guarda en la variable codigo_secreto.
		}
		else
		{
			codigoAleatorioSinRepeticion(codigo_secreto);
		}

		escribirCodigoSecuenciaEnArray(secreto, codigo_secreto); // Escribimos el código secreto en el array secreto.
		// cout << "Codigo secreto: " << codigo_secreto << endl; // -> Para probarlo.
	
		cout << "Mastermind! Codigos de " << N_FICHAS << " colores (RAVNGM), " << MAX_INTENTOS << " intentos, ";
		if(SIN_REPETICION)
		{
			cout << "sin repetici\xa2n" << "." << endl;
		}
		else
		{
			cout << "con repetici\xa2n" << "." << endl;
		}

		do
		{
			pedirPista = false;

			leerCodigoJugador(jugada, salir, pedirPista);

			if(pedirPista)
			{
				// Cada vez que pasan X intentos, se guarda 1 más en acumulador_pistas siempre y cuando no pase de Y.
				if(acumulador_pistas > 0) 
				{
					darPista(secreto, posicion_de_la_pista, cadena_color, posPistas, posArray);
					cout << "El color en la posici\xa2n " << posicion_de_la_pista << " es: " << cadena_color << endl;
					acumulador_pistas--; // Ya hemos utilizado una pista, la restamos de acumulador pistas.
					pistas_gastadas++; // Sumamos uno más a pistas gastadas.
				}
				else if(pistas_gastadas == Y)
				{
					cout << "Lo siento. Ya has agotado el m\xa0ximo de pistas." << endl;
				}
				else
				{
					cout << "Lo siento. Puedes conseguir una pista cada " << X << " intentos." << endl;
				}
			}
			else
			{
				if(!salir)// Hemos introducido un código, no le hemos dado a salir.
				{
					fichas_posicion_correcta = 0, colores_acertados_jugador = 0;

					comprobarColoresCorrectos(secreto, jugada, fichas_posicion_correcta, colores_acertados_jugador);
					// Mostramos el resultado.
					mostrarMovimientoJugador(jugada, intentos, fichas_posicion_correcta, colores_acertados_jugador, puntos_partida); 
					
					if(fichas_posicion_correcta == N_FICHAS)
					{
						codigoAcertado = true;
						cout << "ENHORABUENA " << char(258) << "! Has ganado en " << intentos << " intento(s)." << endl;
						partida_ganada++;
					}
					if((intentos % X == 0) && (veces < Y))
					{
						acumulador_pistas++;
						veces++;
					}
				}
			}
		}while((salir == false) && (intentos < MAX_INTENTOS) && (codigoAcertado == false));

		partida_jugada++;
		if((codigoAcertado == false) && (salir == false))
		{
			cout << "Lo siento. Has superado el n\xa3mero m\xa0ximo de intentos, has perdido." << endl;
		}
		if(salir == false) // Si el usuario no ha salido actualizamos el fichero de puntuaciones del usuario.
		{
			actualizarFicheroPuntuaciones(nombre_usuario, partida_jugada, partida_ganada, puntos_partida);
		}
	}
}

int menu()
{
	// Declaración de variables.
	int opcion;

	// Cuerpo de la función.
	do
	{
		cout << "1 - Jugar a Mastermind" << endl;
		cout << "2 - Puntuaciones"  << endl;
		cout << "0 - Salir" << endl;
		cout << "Elige una opci\xa2n: ";
		cin >> opcion;

		if((opcion < 0) || (opcion > 2))
		{
			cout << "Error. Vuelve a introducir la opci\xa2n" << endl;
		}
	}while((opcion < 0) || (opcion > 2));

	return opcion;
}

void codigoAleatorio(string &codigo)
{
	// Declaración de variables.
	tColores numero_aleatorio;
	char c;

	// Cuerpo de la función.
	for(int i = 0; i < N_FICHAS; i++)
	{
		numero_aleatorio = tColores(rand() % MAX_COLORES); // Aleatorio entre 0 y MAX_COLORES.
		c = conversorDeEnumeradoLetra(numero_aleatorio);
		codigo = codigo + c;
	}
}

void codigoAleatorioSinRepeticion(string &codigo2)
{
	// Declaración de variables.
	tSinRepeticion auxiliar;
	tColores numero_aleatorio;
	char c;
	
	// Cuerpo de la función.
	for(int i = 0; i < N_FICHAS; i++)
	{
		numero_aleatorio = tColores(rand() % MAX_COLORES); // Aleatorio entre 0 y MAX_COLORES.
		c = conversorDeEnumeradoLetra(numero_aleatorio);

		ComprobarSiColorHaSalido(c, auxiliar);
		
		auxiliar[i] = c; // Guardamos el color que hemos cogido, para así comprobar que no se repitan.

		codigo2 = codigo2 + c;
	}
}

void ComprobarSiColorHaSalido(char &a, tSinRepeticion auxiliar)
{
	// Declaración de variables
	tColores numero_aleatorio;
	int j = 0;
	
	// Cuerpo de la función.
	while(j < N_FICHAS)
	{
		if(a == auxiliar[j])
		{
			numero_aleatorio = tColores(rand() % MAX_COLORES); // Aleatorio entre 0 y N.
			a = conversorDeEnumeradoLetra(numero_aleatorio);
			j = 0;
		}
		else
		{
			j++;
		}
	}
}

tColores conversorDeLetraEnumerado(char letra)
{
	tColores resultado;

	// Cuerpo de la función.
	switch(letra)
	{
	case 'r':
	case 'R': resultado = rojo; break;
	case 'a':
	case 'A': resultado = azul; break;
	case 'v':
	case 'V': resultado = verde; break;
	case 'n':
	case 'N': resultado = negro; break;
	case 'g':
	case 'G': resultado = granate; break;
	case 'm':
	case 'M': resultado = marron; break;
	}

	return resultado;
}

char conversorDeEnumeradoLetra(tColores color)
{
	// Declaración de variables.
	char letra;

	// Cuerpo de la función.
	switch(color)
	{
	case 0: letra = 'R'; break;
	case 1: letra = 'A'; break;
	case 2: letra = 'V'; break;
	case 3: letra = 'N'; break;
	case 4: letra = 'G'; break;
	case 5: letra = 'M'; break;
	}

	return letra;
}

string conversorEnumeradoColor(tColores color)
{
	// Declaración de variables.
	string cadena;

	// Cuerpo de la función.
	switch(color)
	{
	case 0: cadena = "rojo"; break;
	case 1: cadena = "azul"; break;
	case 2: cadena = "verde"; break;
	case 3: cadena = "negro"; break;
	case 4: cadena = "granate"; break;
	case 5: cadena = "marr\xa2n"; break;
	}

	return cadena;
}

void leerCodigoJugador(tCodigo jugada, bool &cancela, bool &pista)
{

	// Declaración de variables.
	string codigoLeido;
	int longitud, i = 0; // La variable i es la posición del string.
	bool codigo_correcto = false;
	
	do
	{
		if(i == 0)
		{
			cout <<"Codigo (? para ayuda, ! para pista, 0 para cancelar): ";
			cin >> codigoLeido;

			longitud = codigoLeido.size(); // Calculamos la longitud del string.
		}
		if((longitud != 1) && (longitud != N_FICHAS)) // Mostramos error si no está entre los valores que queremos.
		{
				cout << "Error, el codigo no es correcto, por favor vuelve a introducirlo." << endl;
				codigo_correcto = false;
		}
		else // La longitud es la correcta.
		{
			if((longitud == 1) && (codigoLeido[0] == '0'))
			{
				cancela = true;
			}
			else if((longitud == 1) && (codigoLeido[0] == '?'))
			{
				mostrarArchivo("ayuda.txt");
			}
			else if((longitud == 1) && (codigoLeido[0] == '!'))
			{
				pista = true;
			}
			// Comprobamos que la letra sea uno de los colores disponibles y pasamos a la siguiente letra.
			else if((codigoLeido[i] == 'r') || (codigoLeido[i] == 'R') || (codigoLeido[i] == 'a') || (codigoLeido[i] == 'A') || (codigoLeido[i] == 'v') || (codigoLeido[i] == 'V'))
			{
				i++;
			}
			else if((codigoLeido[i] == 'n') || (codigoLeido[i] == 'N') || (codigoLeido[i] == 'g') || (codigoLeido[i] == 'G') || (codigoLeido[i] == 'm') || (codigoLeido[i] == 'M'))
			{
				i++;
			}
			else // La letra no es la correcta, volvemos a pedir el código.
			{
				cout << "Error, el codigo no es correcto, por favor vuelve a introducirlo." << endl;
				i = 0;
			}
			if((longitud == 1) && (i == 1) && (N_FICHAS != 1)) // La longitud es 1 y la letra está entre las disponible, por tanto error.
			{
				cout << "Error, el codigo no es correcto,  por favor vuelve a introducirlo." << endl;
				i = 0;
			}
			if(i == N_FICHAS)
			{
				codigo_correcto = true;
			}
		}
	}while((cancela == false) && (codigo_correcto == false) && (pista == false));

	// Si ya tenemos el código bien escrito, sin errores, lo escribimos en el array de jugada.
	if(codigo_correcto == true)
	{
		escribirCodigoSecuenciaEnArray(jugada, codigoLeido);
	}
}

void mostrarArchivo(string nombrArch)
{
	// Declaración de variables.
	ifstream archivo;
	string dato;

	// Cuerpo de la función.
	archivo.open(nombrArch); // Abrimos el archivo.
	
	if(archivo.is_open())
	{
		getline(archivo, dato, '\n');
		while(dato != "XXX")
		{
			cout << dato << endl;
			getline(archivo, dato);
		}
	}
	else
	{
		cout << "Error, no se ha podido abrir el archivo." << endl;
	}
}

void escribirCodigoSecuenciaEnArray(tCodigo nombreArray, string secuencia)
{
	tColores valor_guardar;

	for(int i = 0; i < N_FICHAS; i++)
	{
		valor_guardar = conversorDeLetraEnumerado(secuencia[i]);
		nombreArray[i] = valor_guardar;
	}
}

void comprobarColoresCorrectos(const tCodigo secreto, const tCodigo jugada, int &posiciones_acertadas, int &colores_acertados)
{
	tAciertosFallos colores, colores_copia;
	int j;
	bool contado = false;

	for(int i = 0; i < N_FICHAS; i++)
	{
		if(secreto[i] == jugada[i])
		{
			posiciones_acertadas++;
			colores[i] = true;
		}
		else
		{
			colores[i] = false;
		}
	}

	for(int i = 0; i < N_FICHAS; i++)
	{
		colores_copia[i] = colores[i];
	}

	// Ahora comprobamos los colores acertados
	/* Imaginemos que tenemos
	   TFTF -> colores
	   TFTF -> colores_copia 
	   La idea que hemos utilizado es: leemos la primera posición de colores, es true, no nos interesa, seguimos leyendo la 
	   siguiente es false, nos interesa, cogemos ese dato y vamos comparando con los de colores_copia, el primero es true, pasamos
	   al otro, el segundo es false, los datos de secreto[1] == jugada[1], si son iguales, ponemos contado = true y cambiamos el false
	   de colores_copia a true, porque ya lo hemos contado y no lo tenemos que volver a contar, y así sucesivamente, ahora nos vamos
	   a colores[2], es true, pasamos al siguiente, colores[3], este es false, lo comparamos con todos los falses de colores_copia,
	   con los que están a true no los comparamos, porque o bien, ya han sido contados como colores o como posiciones correctas. */
	for(int i = 0; i < N_FICHAS; i++)
	{
		if(!colores[i])
		{
			j = 0;
			contado = false;
			while((j < N_FICHAS) && (!contado))
			{
				if(!colores_copia[j])
				{
					if(secreto[i] == jugada[j])
					{
						colores_acertados++;
						colores_copia[j] = true;
						contado = true;
					}
				}
				j++;
			}
		}
	}
}

void mostrarMovimientoJugador(tCodigo jugada, int &intentos_jugadas, int posicion_acertada, int color_acertado, int &puntos_juego)
{
	// Cuerpo de la función.
	cout << "  " << intentos_jugadas+1 << ": ";
	for(int i = 0; i < N_FICHAS; i++)
	{
		cout << conversorDeEnumeradoLetra(jugada[i]) << " ";
	}

	puntos_juego = puntos_juego + puntuacionPartida(posicion_acertada, color_acertado);

	if(posicion_acertada == N_FICHAS)
	{
		puntos_juego = puntos_juego + PUNTOS_GANAR_JUEGO;
	}
	// alt 0155 para ›(posiciones) y alt 216 para Ï(colores).
	cout << "     " << posicion_acertada << " ›     " << color_acertado << " Ï     " << puntos_juego << " puntos" << endl;

	intentos_jugadas++;
}

int puntuacionPartida(int posiciones_correctas, int colores_correctos)
{
	// Declaracion de variables.
	int puntos = 0;

	// Cuerpo de la función.
	puntos = posiciones_correctas * PUNTO_POSICION + colores_correctos *  PUNTO_COLOR;

	return puntos;
}

void darPista(tCodigo secretoArray, int &posicion_pista, string &cadena, tComprobarPista pistas, int &j)
{
	// Declaración de variables.
	tColores color;
	bool encontrado = false;
	int i = 0;

	// Cuerpo de la función.
	posicion_pista = rand() % N_FICHAS; // Elegimos un nº aleatorio para elegir la posición del color.
	while(i < Y)
	{
		if(posicion_pista == pistas[i]) // Si la pista ya la hemos dado, cogemos otra nueva y volvemos a comparar con las que han salido.
		{
			posicion_pista = rand() % N_FICHAS;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	pistas[j] = posicion_pista; // Una vez tenemos la pista, la metemos en el array pistas.
	j++; // Nos dice en que posición del array podemos poner la pista.
	
	color = secretoArray[posicion_pista];
	cadena = conversorEnumeradoColor(color);
	posicion_pista = posicion_pista + 1;
}

void actualizarFicheroPuntuaciones(string nombre_usuario, int pJugada, int pGanada, int puntos)
{
	// Declaración de variables.
	ifstream archivoUsuarios, archivoT;
	ofstream archivoTmp, archivoU;
	string dato_nombre;
	int total_jugadas, total_ganadas, total_puntos;
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
				archivoUsuarios >> total_jugadas >> total_ganadas >> total_puntos;
				archivoTmp << dato_nombre << " " << total_jugadas << " " << total_ganadas << " " << total_puntos << endl;
			}
			else // Hemos encontrado el nombre
			{
				archivoUsuarios >> total_jugadas >> total_ganadas >> total_puntos;
				archivoTmp << dato_nombre << " " << total_jugadas + pJugada << " " << total_ganadas + pGanada << " "
						   << total_puntos + puntos << endl;
				encontrado = true;
			}
			archivoUsuarios >> dato_nombre;
		}
		if(encontrado == false) // El nombre no existe, hay que añadirlo al final del archivo.
		{
			archivoTmp << nombre_usuario << " " << pJugada << " " << pGanada << " " << puntos << endl;
		}

		archivoTmp << "XXX" << endl;
	}
	else
	{
		archivoTmp << nombre_usuario << " " << pJugada << " " << pGanada << " " << puntos << endl;
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
	int a, b, c;

	archT >> dato;
	while(dato != "XXX")
	{
		archT >> a >> b >> c;
		archU << dato << " " << a << " " << b << " " << c << endl;
		archT >> dato;
	}
	archU << "XXX" << endl;

	archT.close();
	archU.close();
}

void mostrarPuntuaciones(string nombreArchivo)
{
	// Declaración de variables.
	ifstream archivo;
	string dato;
	int a, b, c, longitud, espacio = 19;

	// Cuerpo de la función.
	archivo.open(nombreArchivo); // Abrimos el archivo.
	
	if(archivo.is_open())
	{
		cout << "Usuario" << setw(15) << "Juegos" << setw(9) << "Ganados" << setw(11) << "Puntos" << endl;
		archivo >> dato;
		while(dato != "XXX")
		{
			longitud = dato.size();
			archivo >> a >> b >> c;
			cout << dato << setw(espacio - longitud) << a << setw(9) << b << setw(12) << c << endl;
			archivo >> dato;
		}
	}
	else
	{
		cout << "Error, no se ha podido abrir el archivo." << endl;
	}
}