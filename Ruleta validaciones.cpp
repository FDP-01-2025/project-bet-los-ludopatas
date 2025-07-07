#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

// ====== COLORES (CONSOLAS WINDOWS) ====== //
#define COLOR_DEFAULT 7
#define COLOR_ERROR 12
#define COLOR_SUCCESS 10
#define COLOR_INFO 11
#define COLOR_CYAN 3

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ====== VALIDACIONES SEGURAS ====== //
int leerEnteroSeguro(string mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < min || valor > max) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Intenta de nuevo.\n";
        } else {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

float leerFloatSeguro(string mensaje, float min, float max) {
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < min || valor > max) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Intenta de nuevo.\n";
        } else {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

char leerCharSeguro(string mensaje) {
    char c;
    while (true) {
        cout << mensaje;
        cin >> c;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Intenta de nuevo.\n";
        } else {
            cin.ignore(1000, '\n');
            return tolower(c);
        }
    }
}

// ================== RULETA ================== //
const int redNumbers[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};

bool esRojo(int n) {
    for (int i = 0; i < 18; ++i) {
        if (redNumbers[i] == n) return true;
    }
    return false;
}

void apostarColor(float& saldo) {
    char opcion;
    float apuesta;

    do {
        cout << "\nApuesta por color: (r) Rojo, (n) Negro, (v) Verde: ";
        cin >> opcion;
        opcion = tolower(opcion);
        cin.ignore(1000, '\n');

        if (!(opcion == 'r' || opcion == 'n' || opcion == 'v')) {
            cout << "Opción inválida.\n";
        }
    } while (!(opcion == 'r' || opcion == 'n' || opcion == 'v'));

    apuesta = leerFloatSeguro("¿Cuánto deseas apostar?: $", 1, saldo);

    int resultado = rand() % 37;
    cout << "Resultado: " << resultado
         << (resultado == 0 ? " (Verde)" : esRojo(resultado) ? " (Rojo)" : " (Negro)") << endl;

    saldo -= apuesta;
    if (opcion == 'v' && resultado == 0) {
        cout << "¡Ganaste $" << apuesta * 35 << "!\n";
        saldo += apuesta * 36;
    } else if (opcion == 'r' && esRojo(resultado) && resultado != 0) {
        cout << "¡Ganaste $" << apuesta << "!\n";
        saldo += apuesta * 2;
    } else if (opcion == 'n' && !esRojo(resultado) && resultado != 0) {
        cout << "¡Ganaste $" << apuesta << "!\n";
        saldo += apuesta * 2;
    } else {
        cout << "Perdiste.\n";
    }

    cout << "Saldo actual: $" << saldo << endl;
}

void jugarRuleta(float& saldo) {
    if (saldo < 100) {
        cout << "Saldo mínimo requerido: $100.\n";
        return;
    }

    char continuar;
    do {
        apostarColor(saldo);
        if (saldo < 100) {
            cout << "Saldo insuficiente para seguir jugando.\n";
            return;
        }
        continuar = leerCharSeguro("¿Deseas hacer otra apuesta? (s/n): ");
    } while (continuar == 's');
}

// ========== MENÚ PRINCIPAL ========== //
int validarEdad() {
    int edad;
    do {
        cout << "Ingresa tu edad: ";
        cin >> edad;
        if (cin.fail() || edad < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Edad inválida. Intenta de nuevo.\n";
        } else if (edad < 18) {
            cout << "Debes ser mayor de edad para ingresar.\n";
        }
    } while (edad < 18);
    return edad;
}

float solicitarSaldo() {
    float saldo;
    do {
        cout << "Ingresa tu saldo inicial (mínimo $100): $";
        cin >> saldo;
        if (cin.fail() || saldo < 100) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Saldo inválido o insuficiente. Intenta de nuevo.\n";
        }
    } while (saldo < 100);
    return saldo;
}

void menuCasino() {
    int opcion;
    float saldo;

    cout << "¡Bienvenido al casino Bet++!\n";
    validarEdad();
    saldo = solicitarSaldo();

    do {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Jugar Ruleta\n";
        cout << "2. Salir\n";
        opcion = leerEnteroSeguro("Selecciona una opción: ", 1, 2);

        switch (opcion) {
            case 1:
                jugarRuleta(saldo);
                break;
            case 2:
                cout << "Gracias por jugar. ¡Hasta pronto!\n";
                break;
        }
    } while (opcion != 2);
}

int main() {
    srand(time(0));
    menuCasino();
    return 0;
}