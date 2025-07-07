#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
#include <climits>
#include <random>
#include <string>
#include <limits>
#include <cfloat>
#include <algorithm>
using namespace std;

// ================== DEFINICIONES GLOBALES ================== //

// Definición de colores para consola (solo Windows)
enum Colores {
    COLOR_DEFAULT = 7,      // Blanco por defecto
    COLOR_SUCCESS = 10,     // Verde brillante
    COLOR_INFO = 9,         // Azul brillante
    COLOR_ERROR = 12,       // Rojo brillante
    COLOR_EMPATE = 14,      // Amarillo brillante
    COLOR_MAGENTA = 13,     // Magenta brillante
    COLOR_CYAN = 11         // Cyan brillante
};

// Constantes para Keno
const int MAX_NUMEROS = 10;
const int RANGO_KENO = 80;

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

// ================== FUNCIONES UTILITARIAS ================== //

// Función para cambiar color de texto
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función para limpiar buffer en caso de error de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Validar entrada de entero seguro
int leerEnteroSeguro(string mensaje, int min = INT_MIN, int max = INT_MAX) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            limpiarBuffer();
            setColor(COLOR_ERROR);
            cout << "Entrada inválida. Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else if (valor < min || valor > max) {
            setColor(COLOR_ERROR);
            cout << "Valor fuera de rango (" << min << "-" << max << "). Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

// Validar entrada float segura
float leerFloatSeguro(string mensaje, float min = -FLT_MAX, float max = FLT_MAX) {
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            limpiarBuffer();
            setColor(COLOR_ERROR);
            cout << "Entrada inválida. Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else if (valor < min || valor > max) {
            setColor(COLOR_ERROR);
            cout << "Valor fuera de rango (" << min << "-" << max << "). Intente nuevamente.\n";
            setColor(COLOR_DEFAULT);
        } else {
            limpiarBuffer();
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
            limpiarBuffer();
            return opcion;
        } else {
            setColor(COLOR_ERROR);
            cout << "Opción inválida. Solo 's' o 'n'.\n";
            setColor(COLOR_DEFAULT);
            limpiarBuffer();
        }
    }
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

// Función para pausa con temporizador
void waitASecond(double t) {
    time_t timer = time(nullptr);
    while(time(nullptr) - timer < t);
}

// ================== JUEGO BLACKJACK ================== //

// Función para generar una carta aleatoria
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

void jugarBlackJackMultijugador() {
    int numJugadores = leerEnteroSeguro("Ingrese el número de jugadores (2-5): ", 2, 5);
    vector<Jugador> jugadores(numJugadores);
    
    // Configuración inicial de jugadores
    for (int i = 0; i < numJugadores; i++) {
        cout << "\nDatos del Jugador " << i + 1 << ":\n";
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, jugadores[i].nombre);
        jugadores[i].saldo = leerFloatSeguro("Saldo inicial (mínimo $100): $", 100);
        jugadores[i].total = 0;
        jugadores[i].ases = 0;
        jugadores[i].eliminado = false;
    }

    // Ronda de apuestas
    for (int i = 0; i < numJugadores; i++) {
        cout << "\nTurno de apuestas de " << jugadores[i].nombre << " (Saldo: $" << jugadores[i].saldo << ")\n";
        jugadores[i].apuesta = leerFloatSeguro("Ingrese su apuesta (mínimo $100): $", 100, jugadores[i].saldo);
    }

    animacionBarajeo();

    // Repartir cartas iniciales
    for (int i = 0; i < numJugadores; i++) {
        jugadores[i].cartas[0] = generarCarta();
        jugadores[i].cartas[1] = generarCarta();
        jugadores[i].total = jugadores[i].cartas[0].valor + jugadores[i].cartas[1].valor;
        jugadores[i].ases = (jugadores[i].cartas[0].nombre == "As") + (jugadores[i].cartas[1].nombre == "As");
        
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

void jugarBlackJackSolitario(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo insuficiente para jugar. Debes tener al menos $100." << endl;
        setColor(COLOR_DEFAULT);
        return;
    }

    float apuesta = leerFloatSeguro("\nHas elegido Black Jack. Ingrese el monto que desea apostar (mínimo $100): $", 100, saldo);
    Carta cartasJugador[10], cartasBanca[10];
    int totalJugador = 0, totalBanca = 0;
    int asesJugador = 0, asesBanca = 0;

    animacionBarajeo();

    // Repartir cartas iniciales
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

    // Turno del jugador
    int cartaExtra = 2;
    while (totalJugador < 21) {
        char opcion = leerCharSeguro("¿Deseas otra carta? (s = sí, n = no): ");
        if (opcion == 's') {
            cartasJugador[cartaExtra] = generarCarta();
            totalJugador += cartasJugador[cartaExtra].valor;
            if (cartasJugador[cartaExtra].nombre == "As") asesJugador++;

            // Ajustar Ases si se pasa de 21
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

    // Turno de la banca
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

    // Determinar resultado
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

// ================== JUEGO RULETA ================== //

const int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

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
        cout << "Elige un color - (r) rojo, (n) negro: ";
        setColor(COLOR_DEFAULT);
        cin >> opcion;
        opcion = tolower(opcion);
        limpiarBuffer();
    } while (opcion != 'r' && opcion != 'n');

    apuesta = leerFloatSeguro("¿Cuánto deseas apostar?: $", 1, saldo);

    int resultado = rand() % 37;
    setColor(COLOR_SUCCESS);
    cout << "\nLa ruleta gira...\n";
    Sleep(1000);
    cout << "Resultado: " << resultado << (esRojo(resultado) ? " (Rojo)" : " (Negro)") << endl;

    saldo -= apuesta;
    if (resultado == 0) {
        setColor(COLOR_ERROR);
        cout << "Es 0. Pierdes.\n";
        setColor(COLOR_DEFAULT);
    } else if ((opcion == 'r' && esRojo(resultado)) || (opcion == 'n' && !esRojo(resultado))) {
        setColor(COLOR_SUCCESS);
        cout << "¡Ganaste $" << apuesta * 2 << "!\n";
        saldo += apuesta * 2;
    } else {
        setColor(COLOR_ERROR);
        cout << "Pierdes.\n";
        setColor(COLOR_DEFAULT);
    }
    cout << "Saldo actual: $" << saldo << endl;
}

void apostarNumero(float& saldo) {
    int numero = leerEnteroSeguro("Elige un número (0-36): ", 0, 36);
    float apuesta = leerFloatSeguro("¿Cuánto deseas apostar?: $", 1, saldo);

    int resultado = rand() % 37;
    setColor(COLOR_SUCCESS);
    cout << "\nLa ruleta gira...\n";
    Sleep(1000);
    cout << "Resultado: " << resultado << endl;

    saldo -= apuesta;
    if (resultado == numero) {
        setColor(COLOR_SUCCESS);
        cout << "¡Ganaste $" << apuesta * 36 << "!\n";
        saldo += apuesta * 36;
    } else {
        setColor(COLOR_ERROR);
        cout << "Pierdes.\n";
    }
    setColor(COLOR_DEFAULT);
    cout << "Saldo actual: $" << saldo << endl;
}

void jugarRuleta(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    int opcion;
    do {
        setColor(COLOR_INFO);
        cout << "\n------------------------------\n";
        cout << "|          MENÚ RULETA          |\n";
        cout << "|------------------------------|\n";
        cout << "| 1. Apostar por color         |\n";
        cout << "| 2. Apostar por número        |\n";
        cout << "| 3. Volver al menú principal  |\n";
        cout << "|------------------------------|\n";
        setColor(COLOR_DEFAULT);
        opcion = leerEnteroSeguro("Elige una opción: ", 1, 3);

        switch (opcion) {
            case 1: apostarColor(saldo); break;
            case 2: apostarNumero(saldo); break;
            case 3: return;
        }
    } while (saldo >= 100 && opcion != 3);

    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo insuficiente para seguir jugando.\n";
        setColor(COLOR_DEFAULT);
    }
}

// ================== JUEGO KENO ================== //

// Genera números aleatorios únicos para el Keno
void generarNumerosKeno(int numeros[]) {
    int count = 0;
    while (count < MAX_NUMEROS) {
        int num = rand() % RANGO_KENO + 1;
        bool repetido = false;
        for (int i = 0; i < count; i++) {
            if (numeros[i] == num) {
                repetido = true;
                break;
            }
        }
        if (!repetido) {
            numeros[count++] = num;
        }
    }
}

// Muestra los números del Keno con color
void mostrarNumerosKeno(int arr[]) {
    setColor(COLOR_EMPATE);
    for (int i = 0; i < MAX_NUMEROS; i++) {
        cout << arr[i] << " ";
    }
    setColor(COLOR_DEFAULT);
    cout << "\n";
}

// Proceso para que un jugador ingrese sus números en el Keno
void ingresoNumerosKeno(int jugador[], int numJugador, float saldo = 0) {
    if (numJugador == 1 && saldo > 0) {
        setColor(COLOR_CYAN);
        cout << "Jugador " << numJugador << ", elige tus numeros con la misma precision con la que gastas tu sueldo.\n";
        cout << "Recuerda: aqui no hay sistemas infalibles, solo esperanzas rotas y creditos perdidos.\n";
        setColor(COLOR_DEFAULT);
    }
    
    setColor(COLOR_SUCCESS);
    cout << "Jugador " << numJugador << ", elige 10 numeros entre 1 y 80:\n";
    setColor(COLOR_DEFAULT);

    for (int i = 0; i < MAX_NUMEROS;) {
        setColor(COLOR_INFO);
        cout << " #" << i + 1 << ": ";
        setColor(COLOR_DEFAULT);
        int num = leerEnteroSeguro("", 1, 80);

        bool repetido = false;
        for (int j = 0; j < i; j++) {
            if (jugador[j] == num) {
                repetido = true;
                break;
            }
        }

        if (repetido) {
            setColor(COLOR_MAGENTA);
            cout << "¡Numero repetido! Como tus excusas para seguir jugando... intenta con otro.\n";
            setColor(COLOR_DEFAULT);
            continue;
        }

        jugador[i++] = num;
    }

    setColor(COLOR_SUCCESS);
    cout << "Numeros ingresados por el jugador " << numJugador << ":\n";
    setColor(COLOR_DEFAULT);
    mostrarNumerosKeno(jugador);
    setColor(COLOR_CYAN);
    cout << "Fin del turno (ahora reza, porque las matematicas no te ayudaran)\n";
    setColor(COLOR_DEFAULT);
}

// Cuenta los aciertos en el Keno
int contarAciertosKeno(int jugador[], int sorteados[]) {
    int aciertos = 0;
    for (int i = 0; i < MAX_NUMEROS; i++) {
        for (int j = 0; j < MAX_NUMEROS; j++) {
            if (jugador[i] == sorteados[j]) {
                aciertos++;
                break;
            }
        }
    }
    return aciertos;
}

// Modo solitario del Keno
void jugarKenoSolitario(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    int numerosJugador[MAX_NUMEROS];
    int numerosSorteados[MAX_NUMEROS];
    float apuesta = leerFloatSeguro("Cuanto deseas apostar (1-1000)? $", 1, min(1000.0f, saldo));

    ingresoNumerosKeno(numerosJugador, 1, saldo);
    generarNumerosKeno(numerosSorteados);

    setColor(COLOR_EMPATE);
    cout << "\nY los numeros ganadores son... el sonido de tu billetera llorando\n";
    setColor(COLOR_DEFAULT);
    cout << "Numeros sorteados: ";
    mostrarNumerosKeno(numerosSorteados);

    int aciertos = contarAciertosKeno(numerosJugador, numerosSorteados);
    
    setColor(COLOR_SUCCESS);
    cout << "\nACERTASTE " << aciertos << " NUMEROS.\n";
    setColor(COLOR_DEFAULT);

    // Calculamos porcentaje de ganancia basado en aciertos (4 niveles)
    int porcentaje = 0;
    if (aciertos <= 3) {
        porcentaje = 0;
    } else if (aciertos <= 5) {
        porcentaje = 25;
    } else if (aciertos <= 7) {
        porcentaje = 50;
    } else { // 8 a 10 aciertos
        porcentaje = 100;
    }

    float ganancia = apuesta * porcentaje / 100;
    saldo = saldo - apuesta + ganancia;

    // Mostrar resultados de apuesta y ganancia
    setColor(COLOR_EMPATE);
    cout << "\nAPUESTA: " << apuesta << " | GANANCIA: " << ganancia << "\n";

    if (ganancia == 0) {
        setColor(COLOR_ERROR);
        cout << "Nada ganado... tu billetera pide clemencia.\n";
    } else if (ganancia < apuesta) {
        setColor(COLOR_CYAN);
        cout << "Algo recuperaste... como cuando encuentras una moneda bajo el sofa.\n";
    } else if (ganancia == apuesta) {
        setColor(COLOR_SUCCESS);
        cout << "Recuperaste lo tuyo. No perdiste, pero tampoco saliste con gloria.\n";
    } else {
        setColor(COLOR_SUCCESS);
        cout << "¡Triunfo total! Aciertos y dinero, esto ya parece brujeria.\n";
    }
    setColor(COLOR_DEFAULT);
    cout << "Saldo actual: $" << saldo << endl;
}

// Modo multijugador del Keno
void jugarKenoMultijugador() {
    int jugador1[MAX_NUMEROS];
    int jugador2[MAX_NUMEROS];
    int numerosSorteadosMulti[MAX_NUMEROS];

    ingresoNumerosKeno(jugador1, 1);

    setColor(COLOR_MAGENTA);
    cout << "Cambio de jugador... Porque la miseria compartida es menos miseria.\n";
    cout << "PRESIONA ENTER PARA CAMBIAR AL JUGADOR 2 (y duplicar las perdidas)...\n";
    setColor(COLOR_DEFAULT);
    cin.ignore();
    cin.get();

    for (int i = 0; i < 50; i++) cout << "\n";

    ingresoNumerosKeno(jugador2, 2);
    generarNumerosKeno(numerosSorteadosMulti);

    setColor(COLOR_EMPATE);
    cout << "\nY los numeros ganadores son... el sonido de dos carteras vaciandose\n";
    setColor(COLOR_DEFAULT);
    cout << "NUMEROS SORTEADOS: ";
    mostrarNumerosKeno(numerosSorteadosMulti);

    int aciertos1 = contarAciertosKeno(jugador1, numerosSorteadosMulti);
    int aciertos2 = contarAciertosKeno(jugador2, numerosSorteadosMulti);

    setColor(COLOR_SUCCESS);
    cout << "\nJUGADOR 1 ACERTO: " << aciertos1 << " NUMEROS\n";
    cout << "JUGADOR 2 ACERTO: " << aciertos2 << " NUMEROS\n";
    setColor(COLOR_DEFAULT);

    // Comentarios individuales para cada jugador
    setColor(COLOR_INFO);
    cout << "\nJugador 1: ";
    setColor(COLOR_DEFAULT);
    if (aciertos1 == 0) {
        setColor(COLOR_ERROR);
        cout << "0 aciertos... Fallaste mas que un politico prometiendo.\n";
        setColor(COLOR_DEFAULT);
    } else if (aciertos1 <= 3) {
        setColor(COLOR_CYAN);
        cout << "Algunos aciertos... Como tus relaciones: algo funciona, pero no lo suficiente.\n";
        setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_SUCCESS);
        cout << "¡Excelente! Tienes mas suerte que dealer corrupto en Vegas.\n";
        setColor(COLOR_DEFAULT);
    }

    setColor(COLOR_INFO);
    cout << "Jugador 2: ";
    setColor(COLOR_DEFAULT);
    if (aciertos2 == 0) {
        setColor(COLOR_ERROR);
        cout << "0 aciertos... Al menos no eres el unico, en grupo la derrota es hermosa.\n";
        setColor(COLOR_DEFAULT);
    } else if (aciertos2 <= 3) {
        setColor(COLOR_CYAN);
        cout << "Algunos aciertos... Como recordar donde pusiste las llaves: es un milagro!!!!!.\n";
        setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_SUCCESS);
        cout << "¡Fantastico! Estas que ardes... matematicamente hablando.\n";
        setColor(COLOR_DEFAULT);
    }

    // Resultado final
    setColor(COLOR_EMPATE);
    cout << "\n*** RESULTADO FINAL ***\n";
    setColor(COLOR_DEFAULT);
    
    if (aciertos1 > aciertos2) {
        setColor(COLOR_SUCCESS);
        cout << "¡Jugador 1 gana! Como David vs Goliat, pero con numeros.\n";
        setColor(COLOR_DEFAULT);
    } else if (aciertos2 > aciertos1) {
        setColor(COLOR_SUCCESS);
        cout << "¡Jugador 2 gana! El poder del segundo turno es real.\n";
        setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_MAGENTA);
        cout << "¡Empate! Como una serie de Netflix: nadie gana, pero todos perdemos tiempo.\n";
        setColor(COLOR_DEFAULT);
    }
}

// Menú principal del Keno
void jugarKeno(float& saldo) {
    int opcion;
    do {
        setColor(COLOR_CYAN);
        cout << " ______________________________________\n";
        cout << "|         BIENVENIDO AL JUEGO KENO     |\n";
        cout << "|--------------------------------------|\n";
        setColor(COLOR_SUCCESS);
        cout << "|  1. Jugar keno solo                  |\n";
        cout << "|  2. Jugar keno multijugador          |\n";
        setColor(COLOR_ERROR);
        cout << "|  3. Volver al menú principal         |\n";
        setColor(COLOR_CYAN);
        cout << "|______________________________________|\n";
        setColor(COLOR_DEFAULT);
        opcion = leerEnteroSeguro("Seleccione una opcion: ", 1, 3);

        switch (opcion) {
            case 1: jugarKenoSolitario(saldo); break;
            case 2: jugarKenoMultijugador(); break;
            case 3: return;
        }

        setColor(COLOR_MAGENTA);
        cout << "\n----------------------------\n\n";
        setColor(COLOR_DEFAULT);

    } while (opcion != 3 && saldo >= 100);
}

// ================== JUEGO TRAGAMONEDAS ================== //

void mostrarPerdida() {
    setColor(COLOR_ERROR);
    cout << R"(
                                    ░▒░▒▓▒▒░░░                         
                     ░▓███░█░░▒▒▓█▓ ▒░░                    
                   ▒██▒▒▒███▒░▒▒▒█▓▓█▓█▓░                  
                   ▒█▒▒▒▒██▓░░▒▒▒███▒▒▒▒██░                
                   ░█▒▒▒▒▒░░░░▒▒▒▒█▒▒▒▒▓█░░                
                    ▓▓▒▒▒▒░░░░▒▒▒▒▒▒▒▒▓█                   
                    ▒█▒▒▒▒░░░░▒▒▒▒▒▒▒▓█░░░                 
                    ░█▓▒▓▓▓▓▓▓▓▓▒▒▒▒▓█░░                   
                     ▒██▓▓▓▓▓▓▓▓▓▓▓█▓                      
                       ▒▓███▓▓▓▓▓██▓░                      
                           ░░░░░░░░░░                      
                   ▒▒░░█████▓▓▓▒▒▒▒█▒ ░                    
                  ▓██▓████▒▒▒▒▒▒███████▒                   
                  ▓██████▓▒▒▒▒▒▒▓██████▓                   
                   ▒█▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▓██░                   
                 ░▓█▒███▒▒▒▒▒▒▒▓▒▒▓█▓▒█░                   
             ▒█████▒▒▒▒██▒▒▒▒▒▒▓▒██▓▓▓▒█▒████▓░            
            ░██████▒▒▒▒▒▓▒▒▒▒▒▒▓▓▓▓▒▒▒▒▓██████░            
            ░▓██████████▓▓▒▒▒▒▒▓▓▓████████████░            
             ░▓█████████████████████████████▓░             
             ▒██▓   ░▒     ░▒░░░   ░▒    ▓██▓              
           ░▓█████▓░░▒      ░░     ░▒ ░▓▓▓▓███░            
          ░███████████▓▒▒▒▒░▒░░▒▒▒▒▓▓▓▓▓▓▓▓████            
         ░█████████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█████▓           
         ░██████▓███▓▓▓▓█████████▓▓▓▓▓▓▓▓▓█████░           
          ░█████▓▓▓▓▓▓▓▓█████▓██▓▓▓▓▓▓▓▓▓▓████░            
            ▒████▒░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░▒████▓ ░           
            ▓█████▒ ░░  ░░░░░▒░░░░░ ░░ ▓██████░            
           ▒█▓▓▓████▓░      ░▒░   ░ ░▓████▓▓▓██░           
          ░███▓▓▓▓██████▓░░░░▒░ ░▒██████▓▓▓▓▓██▒           
         ░▒█▓▓▓██▓▓▓██████████████████▓▓▓██▓▓▓▓█░          
         ░█▓▓▓▓▓▓▓▓▓██▓████████████▓▓██▓▓▓▓▓▓▓▓█▒          )" << endl;
    cout << "             ¡Perdiste! jijijija" << endl;
    setColor(COLOR_DEFAULT);
}

void mostrarVictoria() {
    setColor(COLOR_SUCCESS);
    cout << R"(
            /\_/\___  _   _  __      _(_)_ __  
            \_ _/ _ \| | | | \ \ /\ / / | '_  )
             / | (_) | |_| |  \ V  V /| | | | |
             \_/\___/ \__,_|   \_/\_/ |_|_| |_| )" << endl;
    cout << "        ¡Ganaste! (La máquina te respeta y algo de dinero)" << endl;
    setColor(COLOR_DEFAULT);
}

void mostrarJackpot() {
    setColor(COLOR_MAGENTA);
    cout << R"(
              __             _                _   
              \ \  __ _  ___| | ___ __   ___ | |_ 
               \ \/ _` |/ __| |/ / '_ \ / _ \| __|
            /\_/ / (_| | (__|   <| |_) | (_) | |_ 
            \___/ \__,_|\___|_|\_\ .__/ \___/ \__|
                                 |_| )" << endl;
    cout << "        ¡JACKPOT! ¡Ganas el premio mayor!" << endl;
    setColor(COLOR_DEFAULT);
}

void dificultadFacil(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    float apuesta = leerFloatSeguro("Ingrese su apuesta (mínimo $100): $", 100, saldo);
    int matrix[3][3];
    string symbols[6] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍"};
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,5);

    cout << "\n=======================================" << endl;
    cout << "      TRAGAPERRAS - MODO FÁCIL" << endl;
    cout << "=======================================" << endl;
    cout << "El resultado es...\n" << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        mostrarVictoria();
        saldo += apuesta * 2; // Ganancia 2x
    } else {
        mostrarPerdida();
        saldo -= apuesta;
    }
    
    cout << "Saldo actual: $" << saldo << endl;
    cout << "=======================================" << endl;
}

void dificultadMedia(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    float apuesta = leerFloatSeguro("Ingrese su apuesta (mínimo $100): $", 100, saldo);
    int matrix[3][3];
    string symbols[8] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ "};
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,7);

    cout << "\n=======================================" << endl;
    cout << "     TRAGAPERRAS - MODO INTERMEDIO" << endl;
    cout << "=======================================" << endl;
    cout << "El resultado es...\n" << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras
    bool gano = false;
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        gano = true;
        
        // Verificar jackpot (tres sietes)
        if ((matrix[0][0] == 7 && matrix[1][1] == 7 && matrix[2][2] == 7) ||
            (matrix[1][0] == 7 && matrix[1][1] == 7 && matrix[1][2] == 7) ||
            (matrix[2][0] == 7 && matrix[1][1] == 7 && matrix[0][2] == 7)) {
            
            mostrarJackpot();
            saldo += apuesta * 10; // Jackpot 10x
        } else {
            mostrarVictoria();
            saldo += apuesta * 3; // Ganancia normal 3x
        }
    }
    
    if (!gano) {
        mostrarPerdida();
        saldo -= apuesta;
    }
    
    cout << "Saldo actual: $" << saldo << endl;
    cout << "=======================================" << endl;
}

void dificultadDificil(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    float apuesta = leerFloatSeguro("Ingrese su apuesta (mínimo $100): $", 100, saldo);
    int matrix[3][3];
    string symbols[11] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ ", u8"🔔", u8"🍀", u8"🗿"};
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,10);

    cout << "\n=======================================" << endl;
    cout << "      TRAGAPERRAS - MODO DIFÍCIL" << endl;
    cout << "=======================================" << endl;
    cout << "El resultado es...\n" << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras
    bool gano = false;
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        gano = true;
        
        // Verificar jackpot (tres sietes)
        if ((matrix[0][0] == 7 && matrix[1][1] == 7 && matrix[2][2] == 7) ||
            (matrix[1][0] == 7 && matrix[1][1] == 7 && matrix[1][2] == 7) ||
            (matrix[2][0] == 7 && matrix[1][1] == 7 && matrix[0][2] == 7)) {
            
            mostrarJackpot();
            saldo += apuesta * 20; // Jackpot 20x
        } else {
            mostrarVictoria();
            saldo += apuesta * 5; // Ganancia normal 5x
        }
    }
    
    if (!gano) {
        mostrarPerdida();
        saldo -= apuesta;
    }
    
    cout << "Saldo actual: $" << saldo << endl;
    cout << "=======================================" << endl;
}

void jugarTragaperras(float& saldo) {
    if (saldo < 100) {
        setColor(COLOR_ERROR);
        cout << "Saldo mínimo requerido: $100.\n";
        setColor(COLOR_DEFAULT);
        return;
    }

    int opcion;
    do {
        setColor(COLOR_CYAN);
        cout << "\n=======================================" << endl;
        cout << "       MÁQUINA TRAGAMONEDAS" << endl;
        cout << "=======================================" << endl;
        setColor(COLOR_SUCCESS);
        cout << "1. Modo fácil (5 símbolos)" << endl;
        cout << "2. Modo intermedio (7 símbolos)" << endl;
        setColor(COLOR_ERROR);
        cout << "3. Modo difícil (10 símbolos)" << endl;
        cout << "4. Volver al menú principal" << endl;
        setColor(COLOR_CYAN);
        cout << "=======================================" << endl;
        setColor(COLOR_DEFAULT);
        
        opcion = leerEnteroSeguro("Seleccione una opción: ", 1, 4);

        switch (opcion) {
            case 1: dificultadFacil(saldo); break;
            case 2: dificultadMedia(saldo); break;
            case 3: dificultadDificil(saldo); break;
            case 4: return;
        }

        if (saldo < 100) {
            setColor(COLOR_ERROR);
            cout << "Saldo insuficiente para seguir jugando.\n";
            setColor(COLOR_DEFAULT);
            return;
        }

        char continuar = leerCharSeguro("¿Desea jugar otra vez? (s/n): ");
        if (continuar != 's') break;

    } while (opcion != 4 && saldo >= 100);
}
// ================== MENÚ PRINCIPAL ================== //
int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); // Para mostrar emojis correctamente
    
    setColor(COLOR_INFO);
    cout << "Bienvenido a Bet++, el casino donde convertimos a los ludopatas en millonarios... o en ludopobres.\n";
    setColor(COLOR_DEFAULT);

    // Configuración inicial del usuario
    Usuario usuario;
    cout << "Nombre de usuario: ";
    getline(cin, usuario.nombre);
    usuario.edad = leerEnteroSeguro("Edad: ", 1, 120);

    if (usuario.edad < 18) {
        setColor(COLOR_ERROR);
        cout << "Debes tener al menos 18 años para jugar.\n";
        setColor(COLOR_DEFAULT);
        return 0;
    }

    float saldo = leerFloatSeguro("Ingrese su saldo inicial (mínimo $100): $", 100);

    char seguirJugando = 's';
    while (seguirJugando == 's') {
        setColor(COLOR_INFO);
        cout << "\n-------------------------------\n";
        cout << "|      MENÚ PRINCIPAL         |\n";
        cout << "|-----------------------------|\n";
        cout << "| 1. Blackjack Solitario      |\n";
        cout << "| 2. Blackjack Multijugador   |\n";
        cout << "| 3. Ruleta                   |\n";
        cout << "| 4. Keno                     |\n";
        cout << "| 5. Máquina Tragamonedas     |\n";
        cout << "| 6. Salir                    |\n";
        cout << "-------------------------------\n";
        setColor(COLOR_DEFAULT);
        int opcion = leerEnteroSeguro("Seleccione una opción: ", 1, 6);
        
        switch (opcion) {
            case 1: jugarBlackJackSolitario(saldo); break;
            case 2: jugarBlackJackMultijugador(); break;
            case 3: jugarRuleta(saldo); break;
            case 4: jugarKeno(saldo); break;
            case 5: jugarTragaperras(saldo); break;
            case 6: 
                cout << "Gracias por jugar en Bet++, " << usuario.nombre << ". ¡Hasta la próxima!\n";
                return 0;
        }

        if (saldo < 100) {
            setColor(COLOR_ERROR);
            cout << "\nSaldo insuficiente para seguir jugando.\n";
            cout << "Te esperamos cuando tengas más suerte... o más dinero.\n";
            setColor(COLOR_DEFAULT);
            break;
        }

        seguirJugando = leerCharSeguro("\n¿Deseas volver al menú principal? (s/n): ");
    }

    setColor(COLOR_INFO);
    cout << "\nGracias por jugar en Bet++, " << usuario.nombre << ". ¡Vuelve pronto!\n";
    setColor(COLOR_DEFAULT);
    return 0;
}