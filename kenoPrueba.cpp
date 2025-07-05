#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

const int MAX_NUMEROS = 10;
const int RANGO = 80;

// Códigos de colores para la consola
enum Colores {
    RESET = 7,      // Blanco por defecto
    ROJO = 12,      // Rojo brillante
    VERDE = 10,     // Verde brillante
    AZUL = 9,       // Azul brillante
    AMARILLO = 14,  // Amarillo brillante
    MAGENTA = 13,   // Magenta brillante
    CYAN = 11       // Cyan brillante
};

// Función para cambiar color del texto
void cambiarColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Funcion para limpiar buffer en caso de error de entrada
void limpiarBuffer()
{
    char c;
    while (cin.get(c) && c != '\n')
    {
    }
}

// Funcion para pedir numero con validacion robusta
int pedirNumero(int min, int max)
{
    int num;
    while (true)
    {
        cin >> num;

        if (cin.fail())
        {
            cambiarColor(ROJO);
            cout << "Entrada invalida. Por favor ingresa solo numeros.\n";
            cambiarColor(RESET);
            cin.clear();
            limpiarBuffer();
            cout << "Intenta de nuevo: ";
            continue;
        }

        if (num < min || num > max)
        {
            cambiarColor(ROJO);
            cout << "Numero fuera de rango. Ingresa un numero entre " << min << " y " << max << ".\n";
            cambiarColor(RESET);
            limpiarBuffer();
            cout << "Intenta de nuevo: ";
            continue;
        }

        limpiarBuffer();
        return num;
    }
}

void generarNumeros(int numeros[])
{
    int count = 0;
    while (count < MAX_NUMEROS)
    {
        int num = rand() % RANGO + 1;
        bool repetido = false;
        for (int i = 0; i < count; i++)
        {
            if (numeros[i] == num)
            {
                repetido = true;
                break;
            }
        }
        if (!repetido)
        {
            numeros[count++] = num;
        }
    }
}

void mostrarNumeros(int arr[])
{
    cambiarColor(AMARILLO);
    for (int i = 0; i < MAX_NUMEROS; i++)
    {
        cout << arr[i] << " ";
    }
    cambiarColor(RESET);
    cout << "\n";
}

void ingresoNumerosJugador(int jugador[], int numJugador)
{
    if (numJugador == 1) {
        cambiarColor(CYAN);
        cout << "Jugador " << numJugador << ", elige tus numeros con la misma precision con la que gastas tu sueldo.\n";
        cout << "Recuerda: aqui no hay sistemas infalibles, solo esperanzas rotas y creditos perdidos.\n";
        cambiarColor(RESET);
    }
    
    cambiarColor(VERDE);
    cout << "Jugador " << numJugador << ", elige 10 numeros entre 1 y 80:\n";
    cambiarColor(RESET);

    for (int i = 0; i < MAX_NUMEROS;)
    {
        cambiarColor(AZUL);
        cout << " #" << i + 1 << ": ";
        cambiarColor(RESET);
        int num = pedirNumero(1, 80);

        bool repetido = false;
        for (int j = 0; j < i; j++)
        {
            if (jugador[j] == num)
            {
                repetido = true;
                break;
            }
        }

        if (repetido)
        {
            cambiarColor(MAGENTA);
            cout << "¡Numero repetido! Como tus excusas para seguir jugando... intenta con otro.\n";
            cambiarColor(RESET);
            continue;
        }

        jugador[i++] = num;
    }

    cambiarColor(VERDE);
    cout << "Numeros ingresados por el jugador " << numJugador << ":\n";
    cambiarColor(RESET);
    mostrarNumeros(jugador);
    cambiarColor(CYAN);
    cout << "Fin del turno (ahora reza, porque las matematicas no te ayudaran)\n";
    cambiarColor(RESET);
}

int contarAciertos(int jugador[], int sorteados[])
{
    int aciertos = 0;
    for (int i = 0; i < MAX_NUMEROS; i++)
    {
        for (int j = 0; j < MAX_NUMEROS; j++)
        {
            if (jugador[i] == sorteados[j])
            {
                aciertos++;
                break;
            }
        }
    }
    return aciertos;
}

void jugarKenoSolo()
{
    int numerosJugador[MAX_NUMEROS];
    int numerosSorteados[MAX_NUMEROS];

    // Pido apuesta al jugador
    int apuesta;
    cambiarColor(AMARILLO);
    cout << "Cuanto deseas apostar (1 - 1000)? ";
    cambiarColor(RESET);
    apuesta = pedirNumero(1, 1000);

    ingresoNumerosJugador(numerosJugador, 1);
    generarNumeros(numerosSorteados);

    cambiarColor(AMARILLO);
    cout << "\nY los numeros ganadores son... *el sonido de tu billetera llorando*\n";
    cambiarColor(RESET);
    cout << "Numeros sorteados: ";
    mostrarNumeros(numerosSorteados);

    int aciertos = contarAciertos(numerosJugador, numerosSorteados);
    
    cambiarColor(VERDE);
    cout << "\nACERTASTE " << aciertos << " NUMEROS.\n";
    cambiarColor(RESET);

    // Calculamos porcentaje de ganancia basado en aciertos (4 niveles)
    int porcentaje = 0;

    if (aciertos <= 3)
        porcentaje = 0;
    else if (aciertos <= 5)
        porcentaje = 25;
    else if (aciertos <= 7)
        porcentaje = 50;
        
    else // 8 a 10 aciertos
        porcentaje = 100;

    int ganancia = apuesta * porcentaje / 100;

    // Mostrar resultados de apuesta y ganancia
    cambiarColor(AMARILLO);
    cout << "\nAPUESTA: " << apuesta << " | GANANCIA: " << ganancia << "\n";

    if (ganancia == 0) {
        cambiarColor(ROJO);
        cout << "Nada ganado... tu billetera pide clemencia.\n";
    } else if (ganancia < apuesta) {
        cambiarColor(CYAN);
        cout << "Algo recuperaste... como cuando encuentras una moneda bajo el sofá.\n";
    } else if (ganancia == apuesta) {
        cambiarColor(VERDE);
        cout << "Recuperaste lo tuyo. No perdiste, pero tampoco saliste con gloria.\n";
    } else {
        cambiarColor(VERDE);
        cout << "¡Triunfo total! Aciertos y dinero, esto ya parece brujería.\n";
    }
    cambiarColor(RESET);
}

void jugarKenoMultijugador()
{
    int jugador1[MAX_NUMEROS];
    int jugador2[MAX_NUMEROS];
    int numerosSorteadosMulti[MAX_NUMEROS];

    ingresoNumerosJugador(jugador1, 1);

    cambiarColor(MAGENTA);
    cout << "Cambio de jugador... Porque la miseria compartida es menos miseria.\n";
    cout << "PRESIONA ENTER PARA CAMBIAR AL JUGADOR 2 (y duplicar las perdidas)...\n";
    cambiarColor(RESET);
    cin.ignore();
    cin.get();

    for (int i = 0; i < 50; i++)
        cout << "\n";

    ingresoNumerosJugador(jugador2, 2);

    generarNumeros(numerosSorteadosMulti);

    cambiarColor(AMARILLO);
    cout << "\nY los numeros ganadores son... *el sonido de dos carteras vaciandose*\n";
    cambiarColor(RESET);
    cout << "NUMEROS SORTEADOS: ";
    mostrarNumeros(numerosSorteadosMulti);

    int aciertos1 = contarAciertos(jugador1, numerosSorteadosMulti);
    int aciertos2 = contarAciertos(jugador2, numerosSorteadosMulti);

    cambiarColor(VERDE);
    cout << "\nJUGADOR 1 ACERTO: " << aciertos1 << " NUMEROS\n";
    cout << "JUGADOR 2 ACERTO: " << aciertos2 << " NUMEROS\n";
    cambiarColor(RESET);

    // Comentarios individuales para cada jugador
    cambiarColor(AZUL);
    cout << "\nJugador 1: ";
    cambiarColor(RESET);
    if (aciertos1 == 0) {
        cambiarColor(ROJO);
        cout << "0 aciertos... Fallaste mas que un politico prometiendo.\n";
        cambiarColor(RESET);
    }
    else if (aciertos1 >= 1 && aciertos1 <= 3) {
        cambiarColor(CYAN);
        cout << "Algunos aciertos... Como tus relaciones: algo funciona, pero no lo suficiente.\n";
        cambiarColor(RESET);
    }
    else {
        cambiarColor(VERDE);
        cout << "¡Excelente! Tienes mas suerte que dealer corrupto en Vegas.\n";
        cambiarColor(RESET);
    }

    cambiarColor(AZUL);
    cout << "Jugador 2: ";
    cambiarColor(RESET);
    if (aciertos2 == 0) {
        cambiarColor(ROJO);
        cout << "0 aciertos... Al menos no eres el unico, en grupo  la derrota es hermosa.\n";
        cambiarColor(RESET);
    }
    else if (aciertos2 >= 1 && aciertos2 <= 3) {
        cambiarColor(CYAN);
        cout << "Algunos aciertos... Como recordar donde pusiste las llaves: es un milagr!!!!!.\n";
        cambiarColor(RESET);
    }
    else {
        cambiarColor(VERDE);
        cout << "¡Fantastico! Estas que ardes... matematicamente hablando.\n";
        cambiarColor(RESET);
    }

    // Resultado final
    cambiarColor(AMARILLO);
    cout << "\n*** RESULTADO FINAL ***\n";
    cambiarColor(RESET);
    
    if (aciertos1 > aciertos2) {
        cambiarColor(VERDE);
        cout << "¡Jugador 1 gana! Como David vs Goliat, pero con numeros.\n";
        cambiarColor(RESET);
    }
    else if (aciertos2 > aciertos1) {
        cambiarColor(VERDE);
        cout << "¡Jugador 2 gana! El poder del segundo turno es real.\n";
        cambiarColor(RESET);
    }
    else {
        cambiarColor(MAGENTA);
        cout << "¡Empate! Como una serie de Netflix: nadie gana, pero todos perdemos tiempo.\n";
        cambiarColor(RESET);
    }
}

int main()
{
    srand(time(0));
    int opcion;

    do
    {   
        cambiarColor(CYAN);
        cout << " ______________________________________\n";
        cout << "|         BIENVENIDO AL JUEGO KENO     |\n";
        cout << "|______________________________________|\n";
        cambiarColor(VERDE);
        cout << "|  1. Jugar keno solo                  |\n";
        cout << "|  2. Jugar keno multijugador          |\n";
        cambiarColor(ROJO);
        cout << "|  3. Salir                            |\n";
        cambiarColor(CYAN);
        cout << "|______________________________________|\n";
        cambiarColor(RESET);
        cout << "Seleccione una opcion: ";

        opcion = pedirNumero(1, 3);

        switch (opcion)
        {
        case 1:
            jugarKenoSolo();
            break;
        case 2:
            jugarKenoMultijugador();
            break;
        case 3:
            cambiarColor(AMARILLO);
            cout << "Gracias por jugar... y por darle sentido a estos numeros aleatorios.\n";
            cambiarColor(RESET);
            break;
        }

        cambiarColor(MAGENTA);
        cout << "\n----------------------------\n\n";
        cambiarColor(RESET);

    } while (opcion != 3);

    return 0;
}
