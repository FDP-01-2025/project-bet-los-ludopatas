#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int redNumbers[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};

bool esRojo(int n) {
    for (int i = 0; i < 18; i++) {
        if (redNumbers[i] == n) return true;
    }
    return false;
}

void apostarColor(float& saldo) {
    char opcion;
    float apuesta;
    cout << "\nApuesta por color (r = rojo, n = negro): ";
    cin >> opcion;
    opcion = tolower(opcion);

    if (!(opcion == 'r' || opcion == 'n')) {
        cout << "Opción inválida.\n";
        return;
    }

    cout << "¿Cuánto deseas apostar?: $";
    cin >> apuesta;

    if (apuesta > saldo || apuesta <= 0) {
        cout << "Apuesta inválida.\n";
        return;
    }

    int resultado = rand() % 37;
    cout << "La ruleta gira... Resultado: " << resultado << endl;

    saldo -= apuesta;

    if (opcion == 'r' && esRojo(resultado) && resultado != 0) {
        cout << "¡Ganaste!\n";
        saldo += apuesta * 2;
    } else if (opcion == 'n' && !esRojo(resultado) && resultado != 0) {
        cout << "¡Ganaste!\n";
        saldo += apuesta * 2;
    } else {
        cout << "Perdiste.\n";
    }

    cout << "Saldo actual: $" << saldo << endl;
}

void apostarRango(float& saldo) {
    int opcion;
    float apuesta;
    cout << "\nApuesta por rango:" << endl;
    cout << "1. Bajo (1-12)\n2. Medio (13-24)\n3. Alto (25-36)\n";
    cout << "Opción: ";
    cin >> opcion;

    if (opcion < 1 || opcion > 3) {
        cout << "Opción inválida.\n";
        return;
    }

    cout << "¿Cuánto deseas apostar?: $";
    cin >> apuesta;

    if (apuesta > saldo || apuesta <= 0) {
        cout << "Apuesta inválida.\n";
        return;
    }

    int resultado = rand() % 37;
    cout << "La ruleta gira... Resultado: " << resultado << endl;

    saldo -= apuesta;

    bool gana = false;
    switch (opcion) {
        case 1: gana = resultado >= 1 && resultado <= 12; break;
        case 2: gana = resultado >= 13 && resultado <= 24; break;
        case 3: gana = resultado >= 25 && resultado <= 36; break;
    }

    if (resultado == 0) {
        cout << "Cayó 0. Pierdes.\n";
    } else if (gana) {
        cout << "¡Ganaste!\n";
        saldo += apuesta * 3;
    } else {
        cout << "Perdiste.\n";
    }

    cout << "Saldo actual: $" << saldo << endl;
}

void jugarRuleta(float& saldo) {
    int opcion;
    do {
        cout << "\nMenú Ruleta:" << endl;
        cout << "1. Apostar por color\n2. Apostar por rango\n3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: apostarColor(saldo); break;
            case 2: apostarRango(saldo); break;
            case 3: cout << "Saliendo del juego...\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 3 && saldo > 0);
}

int main() {
    srand(time(0));
    float saldo = 500.0;
    cout << "Bienvenido a la ruleta. Saldo inicial: $" << saldo << endl;
    jugarRuleta(saldo);
    cout << "Gracias por jugar.\n";
    return 0;
}