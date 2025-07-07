#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

// ================== COLORES ================== //
#define COLOR_DEFAULT 7
#define COLOR_INFO 11
#define COLOR_SUCCESS 10
#define COLOR_ERROR 12
#define COLOR_CYAN 3

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================== VALIDACIONES ================== //
void limpiarBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

int leerEnteroSeguro(string mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < min || valor > max) {
            limpiarBuffer();
            cout << "Entrada inválida. Intenta de nuevo.\n";
        } else {
            limpiarBuffer();
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
            limpiarBuffer();
            cout << "Entrada inválida. Intenta de nuevo.\n";
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

char leerCharSeguro(string mensaje) {
    char c;
    while (true) {
        cout << mensaje;
        cin >> c;
        limpiarBuffer();
        c = tolower(c);
        if (c == 's' || c == 'n') return c;
        cout << "Entrada inválida. Ingresa 's' o 'n'.\n";
    }
}

// ================== JUGADOR ================== //
struct Jugador {
    string nombre;
    float saldo;
};

Jugador registrarJugador() {
    Jugador j;
    cout << "\nREGISTRO DE JUGADOR\n";
    cout << "Nombre: ";
    getline(cin >> ws, j.nombre);
    j.saldo = leerFloatSeguro("Saldo inicial ($): ", 1, 100000);
    return j;
}

// ================== RULETA ================== //
const int redNumbers[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};

bool esRojo(int n) {
    for (int num : redNumbers) {
        if (num == n) return true;
    }
    return false;
}

void apostarColor(float& saldo) {
    char opcion;
    float apuesta;

    do {
        setColor(COLOR_INFO);
        cout << "\nAPUESTA POR COLOR\n";
        cout << "(r) Rojo    (paga 1:1)\n";
        cout << "(n) Negro   (paga 1:1)\n";
        cout << "(v) Verde (0) (paga 35:1)\n";
        cout << "Elige una opción: ";
        setColor(COLOR_DEFAULT);
        cin >> opcion;
        opcion = tolower(opcion);
        limpiarBuffer();
        if (!(opcion == 'r' || opcion == 'n' || opcion == 'v')) {
            setColor(COLOR_ERROR);
            cout << "Opción inválida\n";
            setColor(COLOR_DEFAULT);
        }
    } while (!(opcion == 'r' || opcion == 'n' || opcion == 'v'));

    apuesta = leerFloatSeguro("¿Cuánto deseas apostar?: $", 1, saldo);

    int resultado = rand() % 37;
    setColor(COLOR_SUCCESS);
    cout << "La ruleta gira...\n";
    Sleep(1000);
    cout << "Resultado: " << resultado << (resultado == 0 ? " (Verde)" : esRojo(resultado) ? " (Rojo)" : " (Negro)") << endl;

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
        setColor(COLOR_ERROR);
        cout << "Perdiste\n";
    }

    setColor(COLOR_DEFAULT);
    cout << "Saldo actual: $" << saldo << endl;
}

void apostarRango(float& saldo) {
    int opcion;
    float apuesta;

    do {
        setColor(COLOR_INFO);
        cout << "\nAPUESTA POR RANGO\n";
        cout << "1. Bajo (1-12) (paga 2:1)\n";
        cout << "2. Medio (13-24) (paga 2:1)\n";
        cout << "3. Alto (25-36) (paga 2:1)\n";
        cout << "Elige una opción: ";
        setColor(COLOR_DEFAULT);
        cin >> opcion;
        limpiarBuffer();
        if (opcion < 1 || opcion > 3) {
            setColor(COLOR_ERROR);
            cout << "Opción inválida\n";
            setColor(COLOR_DEFAULT);
        }
    } while (opcion < 1 || opcion > 3);

    apuesta = leerFloatSeguro("¿Cuánto deseas apostar?: $", 1, saldo);

    int resultado = rand() % 37;
    setColor(COLOR_SUCCESS);
    cout << "La ruleta gira...\n";
    Sleep(1000);
    cout << "Resultado: " << resultado << endl;

    saldo -= apuesta;
    bool gano = false;
    switch (opcion) {
        case 1: gano = (resultado >= 1 && resultado <= 12); break;
        case 2: gano = (resultado >= 13 && resultado <= 24); break;
        case 3: gano = (resultado >= 25 && resultado <= 36); break;
    }

    if (resultado == 0) {
        setColor(COLOR_ERROR);
        cout << "Es 0. Pierdes.\n";
    } else if (gano) {
        cout << "¡Ganaste $" << apuesta * 3 << "!\n";
        saldo += apuesta * 3;
    } else {
        setColor(COLOR_ERROR);
        cout << "Pierdes.\n";
    }

    setColor(COLOR_DEFAULT);
    cout << "Saldo actual: $" << saldo << endl;
}

void jugarRuleta(Jugador& jugador) {
    if (jugador.saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo insuficiente para jugar.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    int opcion;
    char continuar;

    do {
        setColor(COLOR_CYAN);
        cout << "\n" << jugador.nombre << ", tu saldo es: $" << jugador.saldo << endl;
        cout << "MENÚ RULETA\n";
        cout << "1. Apostar por color\n";
        cout << "2. Apostar por rango\n";
        cout << "3. Salir\n";
        setColor(COLOR_DEFAULT);

        opcion = leerEnteroSeguro("Selecciona una opción: ", 1, 3);

        switch (opcion) {
            case 1: apostarColor(jugador.saldo); break;
            case 2: apostarRango(jugador.saldo); break;
            case 3: return;
        }

        if (jugador.saldo < 100) {
            setColor(COLOR_ERROR);
            cout << "Saldo insuficiente para seguir apostando.\n";
            setColor(COLOR_DEFAULT);
            return;
        }

        continuar = leerCharSeguro("¿Deseas seguir apostando? (s/n): ");
    } while (continuar == 's');
}

// ================== MAIN ================== //
int main() {
    srand(time(0));
    Jugador jugador = registrarJugador();
    jugarRuleta(jugador);
    return 0;
}
