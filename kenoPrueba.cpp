#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_NUMEROS = 10;
const int RANGO = 80;

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
    for (int i = 0; i < MAX_NUMEROS; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void ingresoNumerosJugador(int jugador[])
{
    cout << " Jugador, elige 10 numeros entre 1 y 80:\n";
    int num;
    for (int i = 0; i < MAX_NUMEROS;)
    {
        cout << " #" << i + 1 << ": ";
        cin >> num;

        // Validacion del rango
        if (num < 1 || num > RANGO)
        {
            cout << "Numero fuera de rango. Ingresa un numero entre 1 y 80.\n";
            continue;
        }

        // Validacion de repetidos
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
            cout << "Numero repetido. Intenta de nuevo.\n";
            continue;
        }

        jugador[i++] = num;
    }

    cout << "Numeros ingresados por el jugador:\n";
    for (int i = 0; i < MAX_NUMEROS; i++)
    {
        cout << jugador[i] << " ";
    }
    cout << " \nFin del turno\n";
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

  
    ingresoNumerosJugador(numerosJugador);

    generarNumeros(numerosSorteados);

    cout << "\nNumero sortiado: ";
    mostrarNumeros(numerosSorteados);

    int aciertos = contarAciertos(numerosJugador, numerosSorteados);
    cout << "\nACERTASTE " << aciertos << " NUMEROS.\n";
}
void jugarKenoMultijugador()
{
    int jugador1[MAX_NUMEROS];
    int jugador2[MAX_NUMEROS];
    int numerosSorteadosMulti[MAX_NUMEROS];

    cout << "Jugador 1 se prepara para jugar.....\n";
    ingresoNumerosJugador(jugador1);

    cout << "PRESIONA ENTER PARA CAMBIAR AL JUGADOR 2...\n";
    cin.ignore();
    cin.get();

    //  limpieza de consola
    for (int i = 0; i < 50; i++)
    {
        cout << "\n";
    }

    cout << "Jugador 2 se prepara para jugar...\n";
    ingresoNumerosJugador(jugador2);

    generarNumeros(numerosSorteadosMulti);

    cout << "\nNUMEROS SORTEADOS";
    mostrarNumeros(numerosSorteadosMulti);

    int aciertos1 = contarAciertos(jugador1, numerosSorteadosMulti);
    int aciertos2 = contarAciertos(jugador2, numerosSorteadosMulti);

    cout << "\nJUGADOR 1 ACERTO :" << aciertos1 << " NUMEROS\n";
    cout << "JUGADOR 2 ACERTO :" << aciertos2 << " NUMEROS\n";

    if (aciertos1 > aciertos2)
        cout << "\nGANA EL JUGADOR 1\n";
    else if (aciertos2 > aciertos1)
        cout << "\nGANA EL JUGADOR 2\n";
    else
        cout << "\nEMPATE\n";
}
int main()
{
    srand(time(0));
    int opcion;

    do
    {
        cout << "=== MENU KENO ===\n";
        cout << "1. Jugar keno solo\n";
        cout << "2. Jugar keno multijugador\n";
        cout << "3. Salir\n";
        cout << "seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            jugarKenoSolo();
            break;
        }

        case 2:
        {

            jugarKenoMultijugador();
            break;
        }

        case 3:
            cout << "gracias por jugar\n";
            break;

        default:
            cout << "opcion invalida\n";
        }
         cout << "\n----------------------------\n\n";

    } while (opcion != 3);

    return 0;
}
