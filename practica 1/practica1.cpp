/****************************************************************************
 * Práctica realizada por: Isabel Núñez de la Torre *
 ****************************************************************************/

// Practica 1 CodeBreaker.

// Inclusión de bibliotecas.
#include <iostream>     // Biblioteca de entrada/salida estándar.
#include <string>      // Función bool mostrar(string nombArch) de la versión 3 y para la versión 4.
#include <cstdlib>    // Para generar números aleatorios utilizamos las funciones rand() y srand() de la biblioteca cstdlib.
#include <ctime>     /* Lo que hace que el número se comporte de forma aleatoria es la semilla, una semilla habitual es el
					    valor de la hora del sistema time(NULL), de la biblioteca ctime. */
#include <fstream> // Lectura y escritura de archivos.

//Espacio de nombres estándar std.
using namespace std;

// Declaración de funciones.

// versión 1
/* Conduce el desarrollo del juego, se le pasa como parámetros intentos, longitud e intervalo, 
   se genera una secuencia de una cierta longitud cuyos dígitos están entre 1 e intervalo,
   devuelve el numero de intentos que ha utilizado el jugador para adivinar la clave, sino consigue
   adivinarla después de intentos veces, devuelve intentos+1, y si abandona devuelve 0. */
int codeBreaker(int intentos, int longitud, int intervalo);

// Genera una secuencia de longitud dígitos entre 1 e intervalo y lo devuelve como resultado, los parámetros de entrada son la longitud e intervalo.
int claveAleatoria(int longitud, int intervalo);

// Le introducimos como parámetro el codigo, nos calcula el número de dígitos del código y lo devuelve.
int longitudCodigo(int codigo);

/* Devuelve true si los dígitos del codigo proporcionado por el usuario están entre 1 e intervalo, en caso contrario
   devolvemos false, le pasamos como parámetros de entrada el codigo y el intervalo. */
bool intervaloCodigo(int codigo, int intervalo);

/* Devuelve true si el código proporcionado tiene exactamente longitud dígitos y todos ellos están entre 1 e intervalo,
   en caso contrario devuelve false, como parámetros de entrada tiene, codigo, longitud e intervalo. */
bool codigoValido(int codigo, int longitud, int intervalo);

/* Tenemos como parámetro de entrada un entero n, en la función (se invierte el orden de los dígitos). Por ejemplo invertir(2113)
    y nos devuelve el número n invertido, en el ejemplo anterior devolverá 3112. */
int invertir(int n);

/* Devuelve el número de dígitos iniciales coincidentes entre clave y código. Por ejemplo, numeroBips(2123, 2113), devolverá 2
   y numeroBips(3113, 2113), devolverá 0. Le pasamos como parámetros de entrada clave y codigo*/
int numeroBips(int clave, int codigo);

// Versión 2
// Muestra el menú, pide la opción y la devuelve como resultado. Sólo devuelve una opción válida.
int menu();

// Devuelve el número de intentos máximos que haya introducido el usuario. 
int pedirIntentos();

// Devuelve un numero entero que haya introducido el usuario, ese número es la longitud que va a tener el codigo.
int pedirLongitud();

/* Devuelve un número entero que indica el máximo del dígito, es decir, el codigo estará formado por dígitos que estén
   entre 1 y el número que introduzca el usuario */
int pedirIntervalo();

// Versión 3
/* Le pasamos como parámetros maxIntentos, longitud e intervalo, la función lo que hace es abrir, si no está creado, entonces crear
   un archivo de texto llamado "configCB", dónde escribe en orden los valores de los párametros */
void guardamosValores(int intentos, int longitud, int intervalo);

/* Si el archivo no se encuentra devolverá false, en otro caso true, le pasamos cómo parámetro el nombArch,
   la fución lo que hace es leer cada línea del fichero y la muestra por pantalla. */
bool mostrar(string nombArch);

// Version 4
/* Le pasamos como parámetros de entrada, los intentos, la longitud y el intervalo, los cuales utiliza la función para 
   el desarrollo del juego. El Rompedor consiste en que el ordenador adivine su propio código, y que el
   resultado nos lo muestre en un archivo de texto, la función no devuelve nada (no es necesario). */
void rompedor(int intentos, int longitud, int intervalo);

// Función principal
int main()
{
	// Declaración de variables.
	int opcion, maxIntentos = 3, longitud = 4, intervalo = 3;
	ifstream archivo;

	archivo.open("configCB.txt");
	if(archivo.is_open()) // Si el archivo existe, se ha podido abrir, leemos las variables.
	{
		archivo >> maxIntentos >> longitud >> intervalo;
	}

	// Cuerpo de la función.
	do
	{
		opcion = menu();
		
		switch(opcion) 
		{
			case 1: codeBreaker(maxIntentos, longitud, intervalo); break; 
			case 2: maxIntentos = pedirIntentos(); break;
			case 3: longitud = pedirLongitud(); break;
			case 4: intervalo = pedirIntervalo(); break;
			case 5: mostrar("versionCB.txt"); break;
			case 6: rompedor(maxIntentos, longitud, intervalo);
		}
	}while (opcion != 0); 

	archivo.close(); // Cerramos el archivo de lectura.

	// Guardamos los valores de maxIntentos, longitud e intervalo en archivo "configCB.txt"
	guardamosValores(maxIntentos, longitud, intervalo);

	return 0; 
}

// Implementación de funciones.
int codeBreaker(int intentos, int longitud, int intervalo)
{
	// Declaración de variables.
	int clave_ordenador, codigo_usuario, intentos_usuario = 0;
	bool noTerminar;
	
	// Cuerpo de la función.
	clave_ordenador = claveAleatoria(longitud, intervalo); // Asignamos a clave_ordenador una clave aleatoria.

	cout << "Codebreaker... " << intentos << " intentos, longitud " << longitud << " - 1..." << intervalo << endl; 

	do
	{
		cout << "Introduce un codigo (0 para abandonar): "; 
		cin >> codigo_usuario; 

		// Mientras ese número sea distinto de 0 y no sea válido (!=1), volvemos a pedirle el código.
		while ((codigo_usuario != 0) && (codigoValido(codigo_usuario,longitud, intervalo) != 1)) 
		{
			cout << "Codigo incorrecto! Int\x82ntalo de nuevo.\n";
			cout << "Introduce un codigo (0 para abandonar): ";
			cin >> codigo_usuario;
		}

		if (codigo_usuario != 0)
		{
			cout << "  "; 

			/* Mostramos el resultado mediante un for, i es un contador, la función numeroBips nos devuelve el numero de bips correcto
			   por tanto mostramos tantos bips como nos indique la función numeroBips(clave_ordenador, codigo_usuario) */
			for(int i=0; i < numeroBips(clave_ordenador, codigo_usuario); i++)
			{
				cout << "bip ";
			}
			// Si lo que nos da de resultado la función numeroBips(clave_ordenador, codigo_usuario) es igual a longitud, entonces hemos acertado el código.
			if(numeroBips(clave_ordenador, codigo_usuario) == longitud)
			{
				cout << "-- OK!" << endl;
				intentos_usuario++; 

				cout << "Has utilizado " << intentos_usuario << " intento(s)" << endl;
				noTerminar = false; // Ponemos noterminar = false para salir del do while.
			}
			else // El resultado de la función numeroBips(clave_ordenador, codigo_usuario) no es igual a longitud, no hemos acertado el codigo.
			{
				cout << "booop -- Acceso denegado!" << endl; 
				intentos_usuario++; 

				noTerminar = true; 
			}
		} 
		else // El usuario a escogido 0, por tanto hay que salirse del do while, por ello noTerminar = false.
		{
			noTerminar = false; 
		}
	}while((noTerminar == true) && (intentos_usuario < intentos)); 

	// Una vez ya tenemos el resultado.
	if (codigo_usuario == 0) // Si el usuario introdujo un 0, la función devuelve 0.
	{
		return 0;
	} // Luego si los intentos del usuario son iguales a los intentos y además el resultado de la función numeroBips es distinto de la longitud.
	else if ((intentos_usuario == intentos) && (numeroBips(clave_ordenador, codigo_usuario) != longitud))
	{
		cout << "Has agotado el n\xa3mero m\xa0ximo de intentos. Lo siento has perdido!" << endl;

		return intentos+1; // Devolvemos intentos+1.
	}
	// Si no es ninguna de las anteriores devolvemos el número de intentos que ha utilizado el usuario para acertar el código.
	return intentos_usuario; 		
}

int claveAleatoria(int longitud, int intervalo)
{
	// Declaración de variables.
	int  digito, numero = 0;
	
	// Cuerpo de la función.
	srand(time(NULL)); // Lo usamos para poder establecer la semilla.
	
	for(int i = 0; i < longitud; i++) 
	{
		// Creamos un dígito aleatorio entre 1 y el intervalo.
		digito = 1 + (rand() % intervalo); 
		// Añadimos el dígito que hemos creado a número, el dígito nuevo se añade por la derecha(ej: 121 * 10 + 3 = 1213). 
		numero = numero * 10 + digito; 
	}
	
	return numero; // Devolvemos la secuecia generada de longitud dígitos entre 1 e intervalo.
}

int longitudCodigo(int codigo)
{
	// Declaración de variables.
	int numero_de_digitos=0;
	
	// Cuerpo de la función.
	// Dividimos sucesivamente entre 10 el código y vamos aumentado en 1 el contador.
	while(codigo > 0) 
	{
		codigo /= 10; 
		numero_de_digitos++; 
	}
	
	return numero_de_digitos; 
}

bool intervaloCodigo(int codigo, int intervalo)
{	
	// Declaración de variables.
	int digito;
	bool digito_correcto = true;

	// Cuerpo de la función.
	do 
	{
		digito = codigo % 10; 
		codigo /=  10; 

		// Comprobamos que el dígito se encuentra entre 1 e intervalo.
		if ((digito >= 1) && (digito <= intervalo)) 
		{
			digito_correcto = true; 
		}
		else
		{ 
			digito_correcto = false;
		} 

	}while((digito_correcto == true) && (codigo > 0)); 
	
	return digito_correcto;
}

bool codigoValido(int codigo, int longitud, int intervalo)
{
	// Declaración de variables.
	bool codigo_correcto;

	// Cuerpo de la función.
	if((longitudCodigo(codigo) == longitud) && (intervaloCodigo(codigo, intervalo) == 1))
	{
		return codigo_correcto = true; 
	}
	else
	{
		return codigo_correcto = false; 
	}
}

int invertir(int n)
{
	// Declaración de variables.
	int digito, numero_invertido = 0;

	// Cuerpo de la función.
	while (n != 0) 
	{
		digito = n % 10; 
		n /= 10; 
		// Añadimos a numero_invertido, el dígito que hemos "quitado de n".
		numero_invertido = numero_invertido * 10 + digito; 
	}

	return numero_invertido; 
}

int numeroBips(int clave, int codigo)
{
	/* idea: queremos ver los dígitos que tienen iguales hasta el primero que no lo sea, un ejemplo, los números 2113 y 2123, tenemos que comparar el primer dígito
	   con el primero, el segundo con el segundo..., por tanto invertimos los dos números y nos queda el 3112 y 3212, aquí serían 2 (2,1), así pues vamos cogiendo 
	   los últimos dígitos usando el módulo % y "quitándolos" dividiendolos por diez, ¿cúando paramos?, cuando encontremos dos que ya no sean iguales */

	// Declaración de variables.
	int clave_invertida, codigo_invertido, digito_clave, digito_codigo, i = 0;

	// Cuerpo de la función.
	// Invertimos la clave y el codigo con la función invertir.
	clave_invertida = invertir(clave); 
	codigo_invertido = invertir(codigo); 

	do
	{
		// Cogemos los digitos que queremos comparar.
		digito_clave = clave_invertida % 10; 
		digito_codigo = codigo_invertido % 10; 

		// Si los dos son iguales, le sumamos uno al contador, el contador significa los "bips".
		if(digito_clave == digito_codigo) 
		{
			i++;
		}

		clave_invertida = clave_invertida / 10; 
		codigo_invertido = codigo_invertido / 10;

	}while ((digito_clave == digito_codigo) && (codigo_invertido > 0));
	
	return i; 
}

// Versión 2
int menu()
{
	// Declaración de variables.
	int opcion;

	// Cuerpo de la función
	do
	{
		cout << "1 - Jugar"								 << endl;
		cout << "2 - Cambiar el m\xa0ximo de intentos"   << endl;
		cout << "3 - Cambiar la longitud de los codigos" << endl;
		cout << "4 - Cambiar el intervalo de d\xa1gitos" << endl;
		cout << "5 - Acerca de CodeBreaker"              << endl;
		cout << "6 - Rompedor autom\xa0tico"             << endl;
		cout << "0 - Salir"                              << endl;
		cout << "Opci\xa2n: ";
		cin >> opcion;

		if ((opcion < 0) || (opcion > 6)) 
		{
			cout << "Opci\xa2n no v\xa0lida. Int\x82ntalo de nuevo" << endl;
		}
	}while((opcion < 0) || (opcion > 6)); 

	return opcion;
}

int pedirIntentos()
{
	// Declaración de variables.
	int maximo_intentos; 

	// Cuerpo de la función.
	cout << "Introduce el nuevo n\xa3mero m\xa0ximo de intentos: ";
	cin >> maximo_intentos; 
	cout << "M\xa0ximo de intentos modificado!" << endl;

	return maximo_intentos; 
}

int pedirLongitud()
{
	// Declaración de variables.
	int longitud_modificada;

	// Cuerpo de la función.
	cout << "Introduce la nueva longitud de clave: ";
	cin >> longitud_modificada;

	while ((longitud_modificada < 1) || (longitud_modificada > 9)) 
	{
		cout << "Debe estar entre 1 y 9! Int\x82ntalo de nuevo." << endl;
		cout << "Introduce la nueva longitud de clave: "; 
		cin >> longitud_modificada;
	}

	cout << "Longitud de codigo modificada!" << endl;

	return longitud_modificada; 
}

int pedirIntervalo()
{
	// Declaración de variables.
	int intervalo_modificado;

	// Cuerpo de la función.
	cout << "Introduce el nuevo d\xa1gito m\xa0ximo: ";
	cin >> intervalo_modificado;

	while ((intervalo_modificado < 1) || (intervalo_modificado > 9)) 
	{
		cout << "Debe estar entre 1 y 9! Int\x82ntalo de nuevo." << endl;
		cout << "Introduce el nuevo d\xa1gito m\xa0ximo: ";
		cin >> intervalo_modificado;
	}

	cout << "Intervalo de d\xa1gitos modificado!" << endl;

	return intervalo_modificado; 

}

// Versión 3
void guardamosValores(int intentos, int longitud, int intervalo)
{
	// Declaración de variables
	ofstream archivo;

	// Cuerpo de la función.
	archivo.open("configCB.txt"); // Abrimos el archivo

	archivo << intentos << " " << longitud << " " << intervalo << endl; // Escribimos

	archivo.close(); // Cerramos el archivo
}

bool mostrar(string nombArch)
{
	// Declaración de variables.
	ifstream archivo;
	string dato;
	bool archivo_encontrado;

	// Cuerpo de la función.
	archivo.open(nombArch); // Abrimos el archivo

	if(archivo.is_open()) // Si existe el archivo.
	{
		getline(archivo, dato,'\n');

		while( dato != "XXX") // Mientras el dato leído sea distinto del centinela "XXX", seguimos leyendo.
		{
			cout << dato << endl;
			getline(archivo,dato,'\n');
		}

		archivo.close();

		return archivo_encontrado = true;
	}

	cout << "Error. Archivo no encontrado" << endl;

	archivo.close();

	return archivo_encontrado = false;	
}

// Versión 4
void rompedor(int intentos, int longitud, int intervalo)
{
	// Declaración de variables
	int clave_ordenador, codigo_ordenador = 0, intentos_ordenador = 0, numero_aleatorio;
	int digito_incorrecto, digitos_correctos, numero_digitos = 0;
	int dato, dato_aux, dato_comparar, vuelta = 0, bips_anteriores = 0;
	bool noTerminar, digito_cambiado = false;
	string nombre_archivo;
	ofstream archivo_juego;

	// Cuerpo de la función.
	cout << "Nombre del archivo: ";
	cin >> nombre_archivo;

	while((nombre_archivo == "datos.txt") || (nombre_archivo == "datos_copia.txt") || (nombre_archivo == "leeme.txt") || (nombre_archivo == "versionCB.txt") || (nombre_archivo == "configCB.txt"))
	{
		cout << "Error con el nombre del archivo, utiliza otro nombre: ";
		cin >> nombre_archivo;
	}

	archivo_juego.open(nombre_archivo); // Creamos el archivo.
	
	
	clave_ordenador = claveAleatoria(longitud, intervalo);
	cout << clave_ordenador << endl;
	
	do
	{
		while(numero_digitos < longitud)
		{
			numero_aleatorio = 1 + (rand() % intervalo);
			codigo_ordenador = codigo_ordenador * 10 + numero_aleatorio;
			numero_digitos++;
		}

		archivo_juego << "Introduce un código (0 para abandonar): ";
		archivo_juego << codigo_ordenador << endl;

		// Escribimos los bips y booop.
		archivo_juego << "  ";

		for(int i = 0; i < numeroBips(clave_ordenador, codigo_ordenador); i++)
		{
			archivo_juego << "bip ";
		}
		if(numeroBips(clave_ordenador, codigo_ordenador) == longitud)
		{
			archivo_juego << "-- OK!" << endl;
			intentos_ordenador++;

			archivo_juego << "Has utilizado " << intentos_ordenador << " intento(s)" << endl;

			cout << "Clave encontrada!" << endl;

			noTerminar = false;
		}
		else
		{
			archivo_juego << "booop -- Acceso denegado!" << endl;
			intentos_ordenador++;

			noTerminar = true;
		}
		// Si el codigo no fuera correcto.
		if (noTerminar == 1)
		{
			/* En la variable numero_digitos guardamos el numero de digitos que hemos acertado y además el que hemos fallado
			 por ejemplo clave = 1231 y el codigo es 1211, numero_digitos guardaríamos 3.*/
			numero_digitos = numeroBips(clave_ordenador, codigo_ordenador) + 1;
			
			// Queremos coger el digito_incorrecto y los digitos_correctos, así que dividimos el codigo por 10 (longitud - numero_digitos) veces.
			for (int i = 0; i < (longitud - numero_digitos); i++)
			{
				codigo_ordenador = codigo_ordenador / 10;
			}
			// Guardamos en digito_incorrecto, el digito que hay que cambiar.
			digito_incorrecto = codigo_ordenador % 10; 
			
			digitos_correctos = codigo_ordenador / 10;
			
			// Para guardar los valores de digito_incorrecto utilizamos un fichero auxiliar.
			/* Hay que ver cuando ponemos otra vez los archivos sin nada (vacios),los pondremos cuando haya un numero de 
			bips mayor que la vez anterior por eso ponemos vuelta = 0,
			*/
			if((numeroBips(clave_ordenador, codigo_ordenador)) == (bips_anteriores + 1))
			{
				vuelta = 0;
			}

			ofstream archivo1("datos.txt"); // Declaramos archivo de escritura.

			if(vuelta == 1)
			{
			ifstream archivo4;

			archivo4.open("datos_copia.txt");
			archivo4 >> dato_aux;
			while( dato_aux != -1)
				{
					archivo1 << dato_aux << " ";
					archivo4 >> dato_aux;
				}
			}

			archivo1 << digito_incorrecto << " " << -1;
			archivo1.close();

			ifstream archivo2("datos.txt"); // Archivo de lectura.
			ofstream archivo3("datos_copia.txt"); // Archivo de escritura.

			archivo2 >> dato; // Leemos el dato
	
			while (dato != -1)// Si el dato es distinto del centinela -1.
			{
				archivo3 << dato << " "; // Escribimos el dato en el archivo de copia.
				archivo2 >> dato; // Leemos el siguiente dato.
			}

			archivo3 << -1; // terminamos el archivo con un centinela

			vuelta = 1; // Ponemos vuelta = 1, ya hemos entrado 1 vez en el código.
			// cerramos los archivos
			archivo2.close(); 
			archivo3.close(); 
			
			bips_anteriores = numeroBips(clave_ordenador, codigo_ordenador); 
			/* En el do while comparamos el digito_incorrecto con los numeros del archivo y lo cambiamos sucesivamente
			   hasta que encontremos uno que no hemos utilizado aún. */
			do
			{
				ifstream archivo5;

				archivo5.open("datos.txt");

				archivo5 >> dato_comparar;

				// Tomamos un nuevo valor para digito_incorrecto.
				digito_incorrecto = 1 + (rand() % intervalo);

				while((dato_comparar != -1) && (digito_incorrecto != dato_comparar))
				{
					archivo5 >> dato_comparar; // Leemos el siguiente dato y volvemos a comparar
				}
				// Si son iguales volvemos a cambiar el dato y volvemos otra vez al principio del archivo, a leer.
				if(digito_incorrecto == dato_comparar) 
				{
					digito_cambiado = false;
				}
				// Si hemos llegado al final, por tanto ese dato no se ha probado, lo probamos pues.
				if(dato_comparar == -1) 
				{
					digito_cambiado = true;
				}

				archivo5.close();

			}while(digito_cambiado == false);
		
			codigo_ordenador = digitos_correctos * 10 + digito_incorrecto;
		}
	}while((noTerminar == true) && (intentos_ordenador < intentos));

	if((intentos_ordenador == intentos) && (numeroBips(clave_ordenador, codigo_ordenador) != longitud))
	{
		archivo_juego << "Has agotado el número máximo de intentos. Lo siento has perdido!" << endl;
		cout << "No se ha encontrado la clave!" << endl;
	}

	cout << "Puedes ver el resultado en el archivo (" << nombre_archivo << ")!" << endl; 

	archivo_juego.close();
}
