#ifndef KENO_H
#define KENO_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "colors.h"


using namespace std;

const int MAX_NUMBERS = 10;
const int KENO_RANGE = 80;

void generateKenoNumbers(int numbers[]) {
    int count = 0;
    while (count < MAX_NUMBERS) {
        int num = rand() % KENO_RANGE + 1;
        bool repeated = false;
        
        for (int i = 0; i < count; i++) {
            if (numbers[i] == num) {
                repeated = true;
                break;
            }
        }
        
        if (!repeated) {
            numbers[count++] = num;
        }
    }
}

// Muestra los números del Keno con color especial
void showKenoNumbers(int arr[]) {
    setColor(TIE_COLOR);
    for (int i = 0; i < MAX_NUMBERS; i++) {
        cout << arr[i] << " ";
    }
    setColor(DEFAULT_COLOR);
    cout << "\n";
}

// Proceso para que un jugador ingrese sus números en el Keno
void inputKenoNumbers(int player[], int playerNumber, float balance = 0) {
    if (playerNumber == 1 && balance > 0) {
        setColor(CYAN_COLOR);
        cout << "Player " << playerNumber << ", choose your numbers carefully.\n";
        setColor(DEFAULT_COLOR);
    }
    
    setColor(SUCCESS_COLOR);
    cout << "Player " << playerNumber << ", choose 10 numbers between 1 and 80:\n";
    setColor(DEFAULT_COLOR);

    for (int i = 0; i < MAX_NUMBERS;) {
        setColor(INFO_COLOR);
        cout << " #" << i + 1 << ": ";
        setColor(DEFAULT_COLOR);
        int num = readSafeInt("", 1, 80);

        bool repeated = false;
        for (int j = 0; j < i; j++) {
            if (player[j] == num) {
                repeated = true;
                break;
            }
        }

        if (repeated) {
            setColor(MAGENTA_COLOR);
            cout << "Repeated number! Try another.\n";
            setColor(DEFAULT_COLOR);
            continue;
        }

        player[i++] = num;
    }

    setColor(SUCCESS_COLOR);
    cout << "Numbers entered by player " << playerNumber << ":\n";
    setColor(DEFAULT_COLOR);
    showKenoNumbers(player);
}

// Cuenta los aciertos en el Keno comparando con los números sorteados
int countKenoHits(int player[], int drawn[]) {
    int hits = 0;
    for (int i = 0; i < MAX_NUMBERS; i++) {
        for (int j = 0; j < MAX_NUMBERS; j++) {
            if (player[i] == drawn[j]) {
                hits++;
                break;
            }
        }
    }
    return hits;
}

// Modo solitario del Keno (contra la máquina)
void playSingleKeno(float& balance) {
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    int playerNumbers[MAX_NUMBERS];
    int drawnNumbers[MAX_NUMBERS];
    
    float bet = readSafeFloat("How much do you want to bet (1-1000)? $", 1, min(1000.0f, balance));

    inputKenoNumbers(playerNumbers, 1, balance);
    
    generateKenoNumbers(drawnNumbers);

    setColor(TIE_COLOR);
    cout << "\nAnd the winning numbers are...\n";
    setColor(DEFAULT_COLOR);
    cout << "Drawn numbers: ";
    showKenoNumbers(drawnNumbers);

    int hits = countKenoHits(playerNumbers, drawnNumbers);
    
    setColor(SUCCESS_COLOR);
    cout << "\nYOU GOT " << hits << " NUMBERS RIGHT.\n";
    setColor(DEFAULT_COLOR);

    int percentage = 0;
    if (hits <= 3) {
        percentage = 0;
    } else if (hits <= 5) {
        percentage = 25;
    } else if (hits <= 7) {
        percentage = 50;
    } else {
        percentage = 100;
    }

    float winnings = bet * percentage / 100;
    balance = balance - bet + winnings;

    setColor(TIE_COLOR);
    cout << "\nBET: " << bet << " | WINNINGS: " << winnings << "\n";

    if (winnings == 0) {
        setColor(ERROR_COLOR);
        cout << "Nothing won...\n";
    } else if (winnings < bet) {
        setColor(CYAN_COLOR);
        cout << "You recovered something...\n";
    } else if (winnings == bet) {
        setColor(SUCCESS_COLOR);
        cout << "You broke even.\n";
    } else {
        setColor(SUCCESS_COLOR);
        cout << "You won!\n";
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

// Modo multijugador del Keno (2 jugadores compiten)
void playMultiplayerKeno() {
    int player1[MAX_NUMBERS];
    int player2[MAX_NUMBERS];
    int drawnNumbersMulti[MAX_NUMBERS];

    inputKenoNumbers(player1, 1);

    setColor(MAGENTA_COLOR);
    cout << "Changing players...\n";
    cout << "PRESS ENTER TO SWITCH TO PLAYER 2...\n";
    setColor(DEFAULT_COLOR);
    cin.ignore();
    cin.get();

    for (int i = 0; i < 50; i++) cout << "\n";

    inputKenoNumbers(player2, 2);
    
    generateKenoNumbers(drawnNumbersMulti);

    setColor(TIE_COLOR);
    cout << "\nAnd the winning numbers are...\n";
    setColor(DEFAULT_COLOR);
    cout << "DRAWN NUMBERS: ";
    showKenoNumbers(drawnNumbersMulti);

    int hits1 = countKenoHits(player1, drawnNumbersMulti);
    int hits2 = countKenoHits(player2, drawnNumbersMulti);

    setColor(SUCCESS_COLOR);
    cout << "\nPLAYER 1 GOT: " << hits1 << " NUMBERS RIGHT\n";
    cout << "PLAYER 2 GOT: " << hits2 << " NUMBERS RIGHT\n";
    setColor(DEFAULT_COLOR);

    setColor(INFO_COLOR);
    cout << "\nPlayer 1: ";
    setColor(DEFAULT_COLOR);
    if (hits1 == 0) {
        setColor(ERROR_COLOR);
        cout << "0 hits...\n";
        setColor(DEFAULT_COLOR);
    } else if (hits1 <= 3) {
        setColor(CYAN_COLOR);
        cout << "Some hits...\n";
        setColor(DEFAULT_COLOR);
    } else {
        setColor(SUCCESS_COLOR);
        cout << "Excellent!\n";
        setColor(DEFAULT_COLOR);
    }

    setColor(INFO_COLOR);
    cout << "Player 2: ";
    setColor(DEFAULT_COLOR);
    if (hits2 == 0) {
        setColor(ERROR_COLOR);
        cout << "0 hits...\n";
        setColor(DEFAULT_COLOR);
    } else if (hits2 <= 3) {
        setColor(CYAN_COLOR);
        cout << "Some hits...\n";
        setColor(DEFAULT_COLOR);
    } else {
        setColor(SUCCESS_COLOR);
        cout << "Fantastic!\n";
        setColor(DEFAULT_COLOR);
    }

    setColor(TIE_COLOR);
    cout << "\n*** FINAL RESULT ***\n";
    setColor(DEFAULT_COLOR);
    
    if (hits1 > hits2) {
        setColor(SUCCESS_COLOR);
        cout << "Player 1 wins!\n";
        setColor(DEFAULT_COLOR);
    } else if (hits2 > hits1) {
        setColor(SUCCESS_COLOR);
        cout << "Player 2 wins!\n";
        setColor(DEFAULT_COLOR);
    } else {
        setColor(MAGENTA_COLOR);
        cout << "Tie!\n";
        setColor(DEFAULT_COLOR);
    }
}

// Menú principal del Keno
void playKeno(float& balance) {
    int option;
    do {
        setColor(CYAN_COLOR);
        cout << " ______________________________________\n";
        cout << "|         WELCOME TO KENO GAME         |\n";
        cout << "|--------------------------------------|\n";
        setColor(SUCCESS_COLOR);
        cout << "|  1. Play keno solo                   |\n";
        cout << "|  2. Play multiplayer keno            |\n";
        setColor(ERROR_COLOR);
        cout << "|  3. Return to main menu              |\n";
        setColor(CYAN_COLOR);
        cout << "|______________________________________|\n";
        setColor(DEFAULT_COLOR);
        
        option = readSafeInt("Select an option: ", 1, 3);

        switch (option) {
            case 1: playSingleKeno(balance); break;
            case 2: playMultiplayerKeno(); break;
            case 3: return;
        }

        setColor(MAGENTA_COLOR);
        cout << "\n----------------------------\n\n";
        setColor(DEFAULT_COLOR);

    } while (option != 3 && balance >= 100);
}
#endif // KENO_H