#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Números rojos de la ruleta
const int numerosRojos[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};

// Función que determina si un número es rojo
bool esRojo(int numero) {
    for (int i = 0; i < 18; ++i) {
        if (numerosRojos[i] == numero) {
            return true;
        }
    }
    return false;
}

// Función principal del juego de ruleta básica
int main() {
    srand(time(0)); // Semilla para aleatoriedad

    float saldo = 500; // Saldo inicial
    char colorElegido;
    float apuesta;

    cout << "Bienvenido a la ruleta (Rojo / Negro)\n";
    cout << "Saldo inicial: $" << saldo << "\n";

    do {
        cout << "\n¿Cuánto deseas apostar? $";
        cin >> apuesta;

        if (apuesta <= 0 || apuesta > saldo) {
            cout << "Apuesta inválida. Debe ser mayor que 0 y menor o igual al saldo.\n";
            continue;
        }

        cout << "Elige un color (r = rojo, n = negro): ";
        cin >> colorElegido;

        if (colorElegido != 'r' && colorElegido != 'n') {
            cout << "Opción inválida. Debes elegir 'r' o 'n'.\n";
            continue;
        }

        int resultado = rand() % 37;
        cout << "La ruleta gira... salió el número: " << resultado << "\n";

        bool esNumeroRojo = esRojo(resultado);
        bool gano = (colorElegido == 'r' && esNumeroRojo) ||
                    (colorElegido == 'n' && resultado != 0 && !esNumeroRojo);

        saldo -= apuesta;

        if (gano) {
            cout << "¡Ganaste! Has duplicado tu apuesta.\n";
            saldo += apuesta * 2;
        } else {
            cout << "Perdiste esta ronda.\n";
        }

        cout << "Saldo actual: $" << saldo << "\n";

        if (saldo <= 0) {
            cout << "Te has quedado sin saldo. Fin del juego.\n";
            break;
        }

        cout << "¿Deseas seguir jugando? (s/n): ";
        char continuar;
        cin >> continuar;
        if (continuar != 's') break;

    } while (true);

    cout << "Gracias por jugar.\n";
    return 0;
}