#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
#include <limits>
using namespace std;

// Definición de colores para consola (solo Windows)
const int COLOR_DEFAULT = 7;
const int COLOR_SUCCESS = 10;
const int COLOR_INFO = 9;
const int COLOR_ERROR = 12;
const int COLOR_EMPATE = 14;

// Estructuras para usuario, jugador y cartas
struct Usuario {
    string nombre;
    int edad;
};

struct Carta {
    string nombre;
    int valor;
};

struct Jugador {
    string nombre;
    float saldo;
    float apuesta;
    Carta cartas[10];
    int total;
    int ases;
    bool eliminado;
};

// Función para cambiar color de texto
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Validar entrada de entero seguro
int leerEnteroSeguro(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(COLOR_ERROR);
            cout << "Entrada inválida. Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else {
            return valor;
        }
    }
}

// Validar entrada float segura
float leerFloatSeguro(string mensaje) {
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(COLOR_ERROR);
            cout << "Entrada inválida. Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else {
            return valor;
        }
    }
}

// Validar entrada char segura (s/n)
char leerCharSeguro(string mensaje) {
    char opcion;
    while (true) {
        cout << mensaje;
        cin >> opcion;
        opcion = tolower(opcion);
        if (opcion == 's' || opcion == 'n') {
            return opcion;
        } else {
            setColor(COLOR_ERROR);
            cout << "Opción inválida. Solo 's' o 'n'.\n";
            setColor(COLOR_DEFAULT);
        }
    }
}

// Generar carta aleatoria
Carta generarCarta() {
    int numero = rand() % 13 + 1;
    Carta c;
    if (numero == 1) {
        c.nombre = "As";
        c.valor = 11;
    } else if (numero >= 2 && numero <= 10) {
        c.nombre = to_string(numero);
        c.valor = numero;
    } else if (numero == 11) {
        c.nombre = "J";
        c.valor = 10;
    } else if (numero == 12) {
        c.nombre = "Q";
        c.valor = 10;
    } else {
        c.nombre = "K";
        c.valor = 10;
    }
    return c;
}

// Animación de barajeo
void animacionBarajeo() {
    cout << "Barajeando cartas";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << "\n";
}

// Función para Blackjack Multijugador
void jugarBlackJackMultijugador() {
    int numJugadores = leerEnteroSeguro("Ingrese el número de jugadores (2-5): ");
    while (numJugadores < 2 || numJugadores > 5) {
        setColor(COLOR_ERROR);
        cout << "Número inválido. Debe ser entre 2 y 5.\n";
        setColor(COLOR_DEFAULT);
        numJugadores = leerEnteroSeguro("Ingrese el número de jugadores (2-5): ");
    }

    vector<Jugador> jugadores(numJugadores);
    for (int i = 0; i < numJugadores; i++) {
        cout << "\nDatos del Jugador " << i + 1 << ":\n";
        cout << "Nombre: ";
        cin >> jugadores[i].nombre;
        jugadores[i].saldo = leerFloatSeguro("Saldo inicial: ");
        while (jugadores[i].saldo < 100) {
            setColor(COLOR_ERROR);
            cout << "Saldo mínimo debe ser $100\n";
            setColor(COLOR_DEFAULT);
            jugadores[i].saldo = leerFloatSeguro("Saldo inicial: ");
        }
        jugadores[i].total = 0;
        jugadores[i].ases = 0;
        jugadores[i].eliminado = false;
    }

    // Ronda de apuestas
    for (int i = 0; i < numJugadores; i++) {
        cout << "\nTurno de apuestas de " << jugadores[i].nombre << " (Saldo: $" << jugadores[i].saldo << ")\n";
        jugadores[i].apuesta = leerFloatSeguro("Ingrese su apuesta: ");
        while (jugadores[i].apuesta < 100 || jugadores[i].apuesta > jugadores[i].saldo) {
            setColor(COLOR_ERROR);
            cout << "Apuesta no válida. Mínimo $100 y no mayor que tu saldo.\n";
            setColor(COLOR_DEFAULT);
            jugadores[i].apuesta = leerFloatSeguro("Ingrese su apuesta: ");
        }
    }

    animacionBarajeo();

    // Repartir cartas iniciales
    for (int i = 0; i < numJugadores; i++) {
        jugadores[i].cartas[0] = generarCarta();
        jugadores[i].cartas[1] = generarCarta();
        jugadores[i].total = jugadores[i].cartas[0].valor + jugadores[i].cartas[1].valor;
        jugadores[i].ases = (jugadores[i].cartas[0].nombre == "As") + (jugadores[i].cartas[1].nombre == "As");
    }

    // Mostrar cartas iniciales
    for (int i = 0; i < numJugadores; i++) {
        setColor(COLOR_SUCCESS);
        cout << "\n" << jugadores[i].nombre << " tiene: " << jugadores[i].cartas[0].nombre << " y " 
             << jugadores[i].cartas[1].nombre << " (Total: " << jugadores[i].total << ")\n";
        setColor(COLOR_DEFAULT);
    }

    // Ronda de pedir cartas
    for (int i = 0; i < numJugadores; i++) {
        int cartaActual = 2;
        while (!jugadores[i].eliminado && jugadores[i].total < 21) {
            cout << "\nTurno de " << jugadores[i].nombre << " (Total: " << jugadores[i].total << ")\n";
            char opcion = leerCharSeguro("¿Quieres otra carta? (s/n): ");
            
            if (opcion == 's') {
                jugadores[i].cartas[cartaActual] = generarCarta();
                jugadores[i].total += jugadores[i].cartas[cartaActual].valor;
                if (jugadores[i].cartas[cartaActual].nombre == "As") jugadores[i].ases++;

                // Ajustar Ases si se pasa de 21
                while (jugadores[i].total > 21 && jugadores[i].ases > 0) {
                    jugadores[i].total -= 10;
                    jugadores[i].ases--;
                }

                setColor(COLOR_SUCCESS);
                cout << "Carta recibida: " << jugadores[i].cartas[cartaActual].nombre 
                     << " (Total: " << jugadores[i].total << ")\n";
                setColor(COLOR_DEFAULT);
                
                if (jugadores[i].total > 21) {
                    setColor(COLOR_ERROR);
                    cout << jugadores[i].nombre << " se ha pasado de 21. Eliminado.\n";
                    setColor(COLOR_DEFAULT);
                    jugadores[i].eliminado = true;
                    jugadores[i].saldo -= jugadores[i].apuesta;
                }
                cartaActual++;
            } else {
                break;
            }
        }
    }

    // Determinar ganador
    int maxPuntos = -1;
    vector<int> ganadores;
    
    for (int i = 0; i < numJugadores; i++) {
        if (!jugadores[i].eliminado && jugadores[i].total <= 21) {
            if (jugadores[i].total > maxPuntos) {
                maxPuntos = jugadores[i].total;
                ganadores.clear();
                ganadores.push_back(i);
            } else if (jugadores[i].total == maxPuntos) {
                ganadores.push_back(i);
            }
        }
    }

    // Mostrar resultados
    cout << "\n\n=== RESULTADOS FINALES ===\n";
    if (ganadores.empty()) {
        setColor(COLOR_ERROR);
        cout << "Todos los jugadores se pasaron de 21. No hay ganador.\n";
        setColor(COLOR_DEFAULT);
    } else if (ganadores.size() == 1) {
        setColor(COLOR_SUCCESS);
        cout << "¡GANADOR: " << jugadores[ganadores[0]].nombre << " con " << maxPuntos << " puntos!\n";
        setColor(COLOR_DEFAULT);
        
        // Calcular premio (todos pierden su apuesta, ganador gana el total)
        float premioTotal = 0;
        for (int i = 0; i < numJugadores; i++) {
            if (i != ganadores[0]) {
                premioTotal += jugadores[i].apuesta;
            }
        }
        
        jugadores[ganadores[0]].saldo += premioTotal;
    } else {
        setColor(COLOR_EMPATE);
        cout << "¡EMPATE entre: ";
        for (int i = 0; i < ganadores.size(); i++) {
            cout << jugadores[ganadores[i]].nombre;
            if (i < ganadores.size() - 1) cout << ", ";
        }
        cout << " con " << maxPuntos << " puntos!\n";
        setColor(COLOR_DEFAULT);
        
        // En caso de empate, cada ganador recupera su apuesta
        for (int i = 0; i < ganadores.size(); i++) {
            jugadores[ganadores[i]].saldo += jugadores[ganadores[i]].apuesta;
        }
    }

    // Mostrar saldos finales
    cout << "\nSaldos finales:\n";
    for (int i = 0; i < numJugadores; i++) {
        cout << jugadores[i].nombre << ": $" << jugadores[i].saldo << endl;
    }
}

// Función para Blackjack Solitario
void jugarBlackJackSolitario(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo insuficiente para jugar. Debes tener al menos $100." << endl;
        setColor(COLOR_DEFAULT);
        return;
    }

    float apuesta;
    while (true) {
        apuesta = leerFloatSeguro("\nHas elegido Black Jack. Ingrese el monto que desea apostar (mínimo $100): ");
        if (apuesta < 100 || apuesta > saldo) {
            setColor(COLOR_ERROR);
            cout << "Apuesta no válida. Debe ser al menos $100 y no mayor que tu saldo actual.\n";
            setColor(COLOR_DEFAULT);
        } else break;
    }

    Carta cartasJugador[10];
    Carta cartasBanca[10];
    int totalJugador = 0, totalBanca = 0;
    int asesJugador = 0, asesBanca = 0;

    animacionBarajeo();

    cartasJugador[0] = generarCarta();
    cartasJugador[1] = generarCarta();
    cartasBanca[0] = generarCarta();
    cartasBanca[1] = generarCarta();

    totalJugador = cartasJugador[0].valor + cartasJugador[1].valor;
    totalBanca = cartasBanca[0].valor + cartasBanca[1].valor;

    asesJugador += (cartasJugador[0].nombre == "As") + (cartasJugador[1].nombre == "As");
    asesBanca += (cartasBanca[0].nombre == "As") + (cartasBanca[1].nombre == "As");

    setColor(COLOR_SUCCESS);
    cout << "\nTus cartas: " << cartasJugador[0].nombre << " y " << cartasJugador[1].nombre
         << " (Total: " << totalJugador << ")\n";
    setColor(COLOR_INFO);
    cout << "Carta visible de la banca: " << cartasBanca[0].nombre << endl;
    setColor(COLOR_DEFAULT);

    int cartaExtra = 2;
    char opcion;

    while (totalJugador < 21) {
        opcion = leerCharSeguro("¿Deseas otra carta? (s = sí, n = no): ");
        if (opcion == 's') {
            cartasJugador[cartaExtra] = generarCarta();
            totalJugador += cartasJugador[cartaExtra].valor;
            if (cartasJugador[cartaExtra].nombre == "As") asesJugador++;

            while (totalJugador > 21 && asesJugador > 0) {
                totalJugador -= 10;
                asesJugador--;
            }

            setColor(COLOR_SUCCESS);
            cout << "Carta recibida: " << cartasJugador[cartaExtra].nombre << " (Total: " << totalJugador << ")\n";
            setColor(COLOR_DEFAULT);
            cartaExtra++;
            Sleep(700);
        } else {
            break;
        }
    }

    if (totalJugador > 21) {
        setColor(COLOR_ERROR);
        cout << "Te pasaste de 21. Pierdes.\n";
        setColor(COLOR_DEFAULT);
        saldo -= apuesta;
        return;
    }

    cout << "\nTurno de la banca...\n";
    Sleep(1000);
    setColor(COLOR_INFO);
    cout << "Cartas de la banca: " << cartasBanca[0].nombre << " y " << cartasBanca[1].nombre
         << " (Total: " << totalBanca << ")\n";
    setColor(COLOR_DEFAULT);

    int cartaBancaExtra = 2;
    while (totalBanca < 17) {
        Sleep(800);
        cartasBanca[cartaBancaExtra] = generarCarta();
        totalBanca += cartasBanca[cartaBancaExtra].valor;
        if (cartasBanca[cartaBancaExtra].nombre == "As") asesBanca++;

        while (totalBanca > 21 && asesBanca > 0) {
            totalBanca -= 10;
            asesBanca--;
        }

        setColor(COLOR_INFO);
        cout << "La banca saca: " << cartasBanca[cartaBancaExtra].nombre << " (Total: " << totalBanca << ")\n";
        setColor(COLOR_DEFAULT);
        cartaBancaExtra++;
    }

    Sleep(1000);
    if (totalBanca > 21 || totalJugador > totalBanca) {
        setColor(COLOR_SUCCESS);
        cout << "¡Ganaste!\n";
        setColor(COLOR_DEFAULT);
        saldo += apuesta;
    } else if (totalJugador == totalBanca) {
        setColor(COLOR_EMPATE);
        cout << "Empate. Se devuelve tu apuesta.\n";
        setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_ERROR);
        cout << "La banca gana. Pierdes tu apuesta.\n";
        setColor(COLOR_DEFAULT);
        saldo -= apuesta;
    }

    cout << "Tu saldo actual es: $" << saldo << endl;
}

int main() {
    srand(time(NULL));
    cout << "Bienvenido a Bet++, el casino donde convertimos a los ludopatas en millonarios o en ludupobres\n";
    string nombre;
    int edad;
    cout << "Nombre de usuario: ";
    cin >> nombre;
    edad = leerEnteroSeguro("Edad: ");
    if (edad < 18) {
        setColor(COLOR_ERROR);
        cout << "Debes tener al menos 18 años para jugar.\n";
        setColor(COLOR_DEFAULT);
        return 0;
    }

    float saldo = leerFloatSeguro("Ingrese su saldo inicial (mínimo $100): ");
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo insuficiente para comenzar a jugar.\n";
        setColor(COLOR_DEFAULT);
        return 0;
    }

    char seguirJugando = 's';
    while (seguirJugando == 's') {
        cout << "\nMenú de Juegos:\n";
        cout << "1. Blackjack Solitario\n";
        cout << "2. Blackjack Multijugador\n";
        cout << "3. Salir\n";
        int opcion = leerEnteroSeguro("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                jugarBlackJackSolitario(saldo);
                break;
            case 2:
                jugarBlackJackMultijugador();
                break;
            case 3:
                cout << "Gracias por jugar en Bet++.\n";
                return 0;
            default:
                setColor(COLOR_ERROR);
                cout << "Opción inválida. Intente nuevamente.\n";
                setColor(COLOR_DEFAULT);
        }

        if (saldo < 100) {
            setColor(COLOR_ERROR);
            cout << "Saldo insuficiente para seguir jugando.\n";
            setColor(COLOR_DEFAULT);
            break;
        }

        seguirJugando = leerCharSeguro("¿Desea volver al menú principal? (s/n): ");
    }

    cout << "Gracias por jugar en Bet++. ¡Hasta la próxima!\n";
    return 0;
}