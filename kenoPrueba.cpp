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

void ingresoNumerosJugador(int jugador[])
{
    cout << " INGRESO DE NUMEROS DEL JUGADOR \n";
    int num;
    for (int i = 0; i < MAX_NUMEROS;)
    {
        cout << "Numero #" << i + 1 << ": ";
        cin >> num;

        // Validación del rango
        if (num < 1 || num > RANGO)
        {
            cout << "Numero fuera de rango. Ingresa un numero entre 1 y 80.\n";
            continue;
        }

        // Validación de repetidos
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
    cout << " Fin del turno \n";
}

int main()
{
    srand(time(0));
    int opcion;

    do
    {
        cout << "\n=== MENU KENO ===\n";
        cout << "1. JUGAR KENO SOLO\n";
        cout << "2. JUGAR KENO MULTIJUGADOR\n";
        cout << "3. SALIR\n";
        cout << "INGRESA UNA OPCION: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "NUMEROS GENERADOS ALEATORIAMENTE\n";
            int numerosJugador[MAX_NUMEROS];
            ingresoNumerosJugador(numerosJugador);
            int numerosSorteados[MAX_NUMEROS];
            generarNumeros(numerosSorteados);

            cout << "NUMEROS SORTEADOS\n";
            mostrarNumeros(numerosSorteados);

            int aciertos = contarAciertos(numerosJugador, numerosSorteados);
            cout << "ACERTASTE " << aciertos << " NUMEROS\n";

            break;

            break;
        case 2:
           

            break;
        case 3:
            cout << "GRACIAS POR JUGAR KENO\n";
            break;
        default:
            cout << "OPCION INVALIDA\n";
        }

    } while (opcion != 3);

    return 0;
}
