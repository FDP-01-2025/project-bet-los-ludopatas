#ifndef TRAGAPERRAS_H
#define TRAGAPERRAS_H

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <windows.h>
#include <algorithm>
#include "colors.h"

using namespace std;

using namespace std;

void showLoss() {
    setColor(ERROR_COLOR);
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
         ░▒█▓▓▓██▓▓▓██████████████████▓▓▓██▓▓▓█░          
         ░█▓▓▓▓▓▓▓▓▓██▓████████████▓▓██▓▓▓▓▓▓█▒          )" << endl;
    cout << "             You lost! Hahaha" << endl;
    setColor(DEFAULT_COLOR);
}

/*
 * Muestra un mensaje de victoria con arte ASCII
 */
void showWin() {
    setColor(SUCCESS_COLOR);
    cout << R"(
            /\_/\___  _   _  __      _(_)_ __  
            \_ _/ _ \| | | | \ \ /\ / / | '_  )
             / | (_) | |_| |  \ V  V /| | | | |
             \_/\___/ \__,_|   \_/\_/ |_|_| |_| )" << endl;
    cout << "        You won! (The machine respects you and gives you some money)" << endl;
    setColor(DEFAULT_COLOR);
}

/*
 * Muestra un mensaje de jackpot con arte ASCII
 */
void showJackpot() {
    setColor(MAGENTA_COLOR);
    cout << R"(
             __             _                _   
              \ \  __ _  ___| | ___ __   ___ | |_ 
               \ \/ _` |/ __| |/ / '_ \ / _ \| __|
            /\_/ / (_| | (__|   <| |_) | (_) | |_ 
            \___/ \__,_|\___|_|\_\ .__/ \___/ \__|
                                 |_| )" << endl;
    cout << "        JACKPOT! You win the grand prize!" << endl;
    setColor(DEFAULT_COLOR);
}

/*
 * Modo fácil de las tragamonedas (5 símbolos)
 * @param balance Referencia al saldo del jugador (se actualiza)
 */
void easyDifficulty(float& balance) {
    // Verificar saldo mínimo
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    // Obtener apuesta
    float bet = readSafeFloat("Enter your bet (minimum $100): $", 100, balance);
    
    // Configurar símbolos posibles (5 en modo fácil)
    int matrix[3][3];
    string symbols[6] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍"};
    
    // Configurar generador de números aleatorios
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,5);

    // Mostrar cabecera
    cout << "\n=======================================" << endl;
    cout << "      SLOT MACHINE - EASY MODE" << endl;
    cout << "=======================================" << endl;
    cout << "The result is...\n" << endl;

    // Generar y mostrar la matriz de símbolos
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);  // Pausa para dramatismo
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras (diagonales o línea central)
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        // Mostrar victoria y actualizar saldo (2x)
        showWin();
        balance += bet * 2;
    } else {
        // Mostrar derrota y actualizar saldo
        showLoss();
        balance -= bet;
    }
    
    // Mostrar saldo actual
    cout << "Current balance: $" << balance << endl;
    cout << "=======================================" << endl;
}

/*
 * Modo intermedio de las tragamonedas (7 símbolos)
 * @param balance Referencia al saldo del jugador (se actualiza)
 */
void mediumDifficulty(float& balance) {
    // Verificar saldo mínimo
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    // Obtener apuesta
    float bet = readSafeFloat("Enter your bet (minimum $100): $", 100, balance);
    
    // Configurar símbolos posibles (7 en modo intermedio)
    int matrix[3][3];
    string symbols[8] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ "};
    
    // Configurar generador de números aleatorios
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,7);

    // Mostrar cabecera
    cout << "\n=======================================" << endl;
    cout << "     SLOT MACHINE - MEDIUM MODE" << endl;
    cout << "=======================================" << endl;
    cout << "The result is...\n" << endl;

    // Generar y mostrar la matriz de símbolos
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);  // Pausa para dramatismo
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras
    bool won = false;
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        won = true;
        
        // Verificar jackpot (tres sietes)
        if ((matrix[0][0] == 7 && matrix[1][1] == 7 && matrix[2][2] == 7) ||
            (matrix[1][0] == 7 && matrix[1][1] == 7 && matrix[1][2] == 7) ||
            (matrix[2][0] == 7 && matrix[1][1] == 7 && matrix[0][2] == 7)) {
            
            // Mostrar jackpot y actualizar saldo (10x)
            showJackpot();
            balance += bet * 10;
        } else {
            // Mostrar victoria normal y actualizar saldo (3x)
            showWin();
            balance += bet * 3;
        }
    }
    
    // Si no ganó, mostrar derrota
    if (!won) {
        showLoss();
        balance -= bet;
    }
    
    // Mostrar saldo actual
    cout << "Current balance: $" << balance << endl;
    cout << "=======================================" << endl;
}

/*
 * Modo difícil de las tragamonedas (10 símbolos)
 * @param balance Referencia al saldo del jugador (se actualiza)
 */
void hardDifficulty(float& balance) {
    // Verificar saldo mínimo
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    // Obtener apuesta
    float bet = readSafeFloat("Enter your bet (minimum $100): $", 100, balance);
    
    // Configurar símbolos posibles (10 en modo difícil)
    int matrix[3][3];
    string symbols[11] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ ", u8"🔔", u8"🍀", u8"🗿"};
    
    // Configurar generador de números aleatorios
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,10);

    // Mostrar cabecera
    cout << "\n=======================================" << endl;
    cout << "      SLOT MACHINE - HARD MODE" << endl;
    cout << "=======================================" << endl;
    cout << "The result is...\n" << endl;

    // Generar y mostrar la matriz de símbolos
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = range(rng);
            cout << "| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);  // Pausa para dramatismo
        cout << endl;
    }
    cout << endl;
    
    // Verificar combinaciones ganadoras
    bool won = false;
    if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) || 
       (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2]) || 
       (matrix[2][0] == matrix[1][1] && matrix[1][1] == matrix[0][2])) {
        
        won = true;
        
        // Verificar jackpot (tres sietes)
        if ((matrix[0][0] == 7 && matrix[1][1] == 7 && matrix[2][2] == 7) ||
            (matrix[1][0] == 7 && matrix[1][1] == 7 && matrix[1][2] == 7) ||
            (matrix[2][0] == 7 && matrix[1][1] == 7 && matrix[0][2] == 7)) {
            
            // Mostrar jackpot y actualizar saldo (20x)
            showJackpot();
            balance += bet * 20;
        } else {
            // Mostrar victoria normal y actualizar saldo (5x)
            showWin();
            balance += bet * 5;
        }
    }
    
    // Si no ganó, mostrar derrota
    if (!won) {
        showLoss();
        balance -= bet;
    }
    
    // Mostrar saldo actual
    cout << "Current balance: $" << balance << endl;
    cout << "=======================================" << endl;
}

/*
 * Menú principal de las tragamonedas
 * @param balance Referencia al saldo del jugador (se actualiza)
 */
void playSlots(float& balance) {
    // Verificar saldo mínimo
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    int option;
    do {
        // Mostrar menú de tragamonedas
        setColor(CYAN_COLOR);
        cout << "\n=======================================" << endl;
        cout << "       SLOT MACHINE" << endl;
        cout << "=======================================" << endl;
        setColor(SUCCESS_COLOR);
        cout << "1. Easy mode (5 symbols)" << endl;
        cout << "2. Medium mode (7 symbols)" << endl;
        setColor(ERROR_COLOR);
        cout << "3. Hard mode (10 symbols)" << endl;
        cout << "4. Return to main menu" << endl;
        setColor(CYAN_COLOR);
        cout << "=======================================" << endl;
        setColor(DEFAULT_COLOR);
        
        // Obtener opción del usuario
        option = readSafeInt("Select an option: ", 1, 4);

        // Procesar opción seleccionada
        switch (option) {
            case 1: easyDifficulty(balance); break;
            case 2: mediumDifficulty(balance); break;
            case 3: hardDifficulty(balance); break;
            case 4: return;
        }

        // Verificar si el jugador puede seguir jugando
        if (balance < 100) {
            setColor(ERROR_COLOR);
            cout << "Insufficient balance to keep playing.\n";
            setColor(DEFAULT_COLOR);
            return;
        }

        // Preguntar si desea jugar otra vez
        char continuePlaying = readSafeChar("Do you want to play again? (y/n): ");
        if (continuePlaying != 'y') break;

    } while (option != 4 && balance >= 100);
}
#endif // TRAGAPERRAS_H