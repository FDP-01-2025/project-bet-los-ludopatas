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
            int numerosPrueba[MAX_NUMEROS];
            generarNumeros(numerosPrueba);
            mostrarNumeros(numerosPrueba);
            break;

        
            break;
        case 2:
            cout << "JUGAR KENO MULTIJUGADOR (PENDIENTE)\n";
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
