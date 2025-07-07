#ifndef COLORES_H
#define COLORES_H

#include <windows.h>       // Para SetConsoleTextAttribute, STD_OUTPUT_HANDLE
#include <iostream>        // Para cout, cin
#include <string>          // Para std::string
#include <limits>          // Para numeric_limits
#include <climits>         // Para INT_MIN, INT_MAX
#include <cfloat>          // Para FLT_MAX, FLT_MIN
#include <ctime>           // Para time() en waitASecond
#include <algorithm>  
     // Para min(), max()
using namespace std;     

// Enumeración de colores
enum Colors {
    DEFAULT_COLOR = 7,      // Blanco por defecto
    SUCCESS_COLOR = 10,     // Verde brillante (éxito)
    INFO_COLOR = 9,         // Azul brillante (información)
    ERROR_COLOR = 12,       // Rojo brillante (error)
    TIE_COLOR = 14,         // Amarillo brillante (empate)
    MAGENTA_COLOR = 13,     // Magenta brillante
    CYAN_COLOR = 11         // Cyan brillante
};
// Prototipos
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Limpia el buffer de entrada en caso de error
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lee un entero de forma segura validando tipo y rango
int readSafeInt(string message, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail()) {
            clearBuffer();
            setColor(ERROR_COLOR);
            cout << "Invalid input. Try again.\n";
            setColor(DEFAULT_COLOR);
        } else if (value < min || value > max) {
            setColor(ERROR_COLOR);
            cout << "Value out of range (" << min << "-" << max << "). Try again.\n";
            setColor(DEFAULT_COLOR);
        } else {
            clearBuffer();
            return value;
        }
    }
}

// Lee un número decimal de forma segura validando tipo y rango
float readSafeFloat(string message, float min = -FLT_MAX, float max = FLT_MAX) {
    float value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail()) {
            clearBuffer();
            setColor(ERROR_COLOR);
            cout << "Invalid input. Please enter a valid number.\n";
            setColor(DEFAULT_COLOR);
        } else if (value < min) {
            setColor(ERROR_COLOR);
            cout << "Value too small. Minimum allowed is " << min << ". Try again.\n";
            setColor(DEFAULT_COLOR);
        } else if (value > max) {
            setColor(ERROR_COLOR);
            cout << "Value too large. Maximum allowed is " << max << ". Try again.\n";
            setColor(DEFAULT_COLOR);
        } else {
            clearBuffer();
            return value;
        }
    }
}

// Lee un carácter validando que sea 'y' o 'n' (yes/no)
char readSafeChar(string message) {
    char option;
    while (true) {
        cout << message;
        cin >> option;
        option = tolower(option);
        if (option == 'y' || option == 'n') {
            clearBuffer();
            return option;
        } else {
            setColor(ERROR_COLOR);
            cout << "Invalid option. Only 'y' or 'n'.\n";
            setColor(DEFAULT_COLOR);
            clearBuffer();
        }
    }
}

// Muestra una animación de barajeo de cartas
void shuffleAnimation() {
    cout << "Shuffling cards";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << "\n";
}

// Pausa el programa por un tiempo determinado
void waitASecond(double t) {
    time_t timer = time(nullptr);
    while(time(nullptr) - timer < t);
}

#endif // COLORES_H