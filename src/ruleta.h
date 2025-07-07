#ifndef RULETA_H
#define RULETA_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <windows.h>
#include "colors.h"

using namespace std;

const int redNumbers[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

bool isRed(int n) {
    for (int num : redNumbers) {
        if (num == n) return true;
    }
    return false;
}

// Función para apostar por color en la ruleta
void betColor(float& balance) {
    char option;
    float bet;

    do {
        setColor(INFO_COLOR);
        cout << "\n╔══════════════════════════════╗" << endl;
        cout << "║       COLOR BETTING         ║" << endl;
        cout << "╠══════════════════════════════╣" << endl;
        cout << "║ (r) Red    (pays 1:1)       ║" << endl;
        cout << "║ (b) Black  (pays 1:1)       ║" << endl;
        cout << "║ (g) Green (0) (pays 35:1)   ║" << endl;
        cout << "╚══════════════════════════════╝" << endl;
        cout << "Choose an option: ";
        setColor(DEFAULT_COLOR);
        cin >> option;
        option = tolower(option);
        clearBuffer();

        if (!(option == 'r' || option == 'b' || option == 'g')) {
            setColor(ERROR_COLOR);
            cout << "Invalid option, try again" << endl;
            setColor(DEFAULT_COLOR);
        }
    } while (!(option == 'r' || option == 'b' || option == 'g'));

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);

    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << (result == 0 ? " (Green)" : isRed(result) ? " (Red)" : " (Black)") << endl;

    balance -= bet;
    if (option == 'g' && result == 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 35 << "!" << endl;
        balance += bet * 36;
    } 
    else if (option == 'r' && isRed(result) && result != 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet << "!" << endl;
        balance += bet * 2;
    }
    else if (option == 'b' && !isRed(result) && result != 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet << "!" << endl;
        balance += bet * 2;
    }
    else {
        setColor(ERROR_COLOR);
        cout << "You lost" << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

// Función para apostar por rango en la ruleta
void betRange(float& balance) {
    int option;
    float bet;

    do {
        setColor(INFO_COLOR);
        cout << "\n╔══════════════════════════════╗" << endl;
        cout << "║       RANGE BETTING         ║" << endl;
        cout << "╠══════════════════════════════╣" << endl;
        cout << "║ 1. Low    (1-12)  (pays 2:1)║" << endl;
        cout << "║ 2. Medium (13-24) (pays 2:1)║" << endl;
        cout << "║ 3. High   (25-36) (pays 2:1)║" << endl;
        cout << "╚══════════════════════════════╝" << endl;
        cout << "Choose an option: ";
        setColor(DEFAULT_COLOR);
        cin >> option;
        clearBuffer();

        if (!(option >= 1 && option <= 3)) {
            setColor(ERROR_COLOR);
            cout << "Invalid option, try again" << endl;
            setColor(DEFAULT_COLOR);
        }
    } while (!(option >= 1 && option <= 3));

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);

    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << endl;

    balance -= bet;
    bool won = false;
    switch (option) {
        case 1: won = (result >= 1 && result <= 12); break;
        case 2: won = (result >= 13 && result <= 24); break;
        case 3: won = (result >= 25 && result <= 36); break;
    }

    if (result == 0) {
        setColor(ERROR_COLOR);
        cout << "It's 0. You lose." << endl;
    } else if (won) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 3 << "!" << endl;
        balance += bet * 3;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lose." << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

// Función para apostar por número específico en la ruleta
void betNumber(float& balance) {
    int number;
    float bet;

    do {
        setColor(INFO_COLOR);
        cout << "\n╔══════════════════════════════╗" << endl;
        cout << "║       NUMBER BETTING        ║" << endl;
        cout << "╠══════════════════════════════╣" << endl;
        cout << "║ Choose a number (0-36)      ║" << endl;
        cout << "║ (pays 35:1)                 ║" << endl;
        cout << "╚══════════════════════════════╝" << endl;
        cout << "Enter your number: ";
        setColor(DEFAULT_COLOR);
        cin >> number;
        clearBuffer();

        if (number < 0 || number > 36) {
            setColor(ERROR_COLOR);
            cout << "Invalid number, must be between 0 and 36" << endl;
            setColor(DEFAULT_COLOR);
        }
    } while (number < 0 || number > 36);

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);

    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << endl;

    balance -= bet;
    if (result == number) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 35 << "!" << endl;
        balance += bet * 36;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lose." << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

// Función principal para jugar a la ruleta
void playRoulette(float& balance) {
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100." << endl;
        setColor(DEFAULT_COLOR);
        return;
    }

    int option;
    char continuePlaying;

    do {
        setColor(CYAN_COLOR);
        cout << "\n╔══════════════════════════════╗" << endl;
        cout << "║         ROULETTE MENU        ║" << endl;
        cout << "╠══════════════════════════════╣" << endl;
        cout << "║ 1. Bet by color              ║" << endl;
        cout << "║ 2. Bet by range              ║" << endl;
        cout << "║ 3. Bet by number             ║" << endl;
        cout << "║ 4. Return to main menu       ║" << endl;
        cout << "╚══════════════════════════════╝" << endl;
        setColor(DEFAULT_COLOR);
        
        option = readSafeInt("Select an option: ", 1, 4);

        switch (option) {
            case 1: betColor(balance); break;
            case 2: betRange(balance); break;
            case 3: betNumber(balance); break;
            case 4: return;
        }

        if (balance < 100) {
            setColor(ERROR_COLOR);
            cout << "Insufficient balance to keep playing." << endl;
            setColor(DEFAULT_COLOR);
            return;
        }

        continuePlaying = readSafeChar("Do you want to place another bet? (y/n): ");
    } while (continuePlaying == 'y');
}


#endif // RULETA_H