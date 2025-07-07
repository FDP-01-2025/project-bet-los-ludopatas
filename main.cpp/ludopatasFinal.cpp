

// ================== REQUIRED LIBRARIES ================== //
#include <iostream>       // Para entrada/salida estándar (cout, cin)
#include <cstdlib>        // Para funciones como rand() y srand()
#include <ctime>          // Para time() usado en generación de números aleatorios
#include <windows.h>      // Para funciones específicas de Windows (colores en consola)
#include <vector>         // Para usar la estructura vector (listas dinámicas)
#include <climits>        // Para constantes como INT_MIN, INT_MAX
#include <random>         // Para generación de números aleatorios más avanzada
#include <string>         // Para manejo de strings
#include <limits>         // Para numeric_limits
#include <cfloat>         // Para FLT_MAX, FLT_MIN
#include <algorithm>      // Para funciones como min(), max()

using namespace std;

// ================== GLOBAL DEFINITIONS ================== //

// Enumeración de colores para la consola (solo Windows)
enum Colors {
    DEFAULT_COLOR = 7,      // Blanco por defecto
    SUCCESS_COLOR = 10,     // Verde brillante (éxito)
    INFO_COLOR = 9,         // Azul brillante (información)
    ERROR_COLOR = 12,       // Rojo brillante (error)
    TIE_COLOR = 14,         // Amarillo brillante (empate)
    MAGENTA_COLOR = 13,     // Magenta brillante
    CYAN_COLOR = 11         // Cyan brillante
};

// Constantes para el juego Keno
const int MAX_NUMBERS = 10;
const int KENO_RANGE = 80;

// Estructura para almacenar datos del usuario
struct User {
    string name;
    int age;
};

// Estructura para representar una carta en el Blackjack
struct Card {
    string name;
    int value;
};

// Estructura para representar un jugador en el Blackjack
struct Player {
    string name;
    float balance;
    float bet;
    Card cards[10];
    int total;
    int aces;
    bool eliminated;
};

// ================== UTILITY FUNCTIONS ================== //

// Cambia el color del texto en la consola (solo Windows)
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

// ================== BLACKJACK GAME ================== //

// Genera una carta aleatoria para el Blackjack
Card generateCard() {
    int number = rand() % 13 + 1;
    Card c;
    
    if (number == 1) {
        c.name = "Ace";
        c.value = 11;
    } else if (number >= 2 && number <= 10) {
        c.name = to_string(number);
        c.value = number;
    } else if (number == 11) {
        c.name = "J";
        c.value = 10;
    } else if (number == 12) {
        c.name = "Q";
        c.value = 10;
    } else {
        c.name = "K";
        c.value = 10;
    }
    return c;
}

// Implementación del Blackjack multijugador (2-5 jugadores)
void playMultiplayerBlackjack() {
    int numPlayers = readSafeInt("Enter number of players (2-5): ", 2, 5);
    vector<Player> players(numPlayers);

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer UNA vez antes de getline

    for (int i = 0; i < numPlayers; i++) {
        cout << "\nPlayer " << i + 1 << " data:\n";
        cout << "Name: ";
        getline(cin, players[i].name);  // Usa getline para nombres completos sin errores
        players[i].balance = readSafeFloat("Initial balance (minimum $100): $", 100);
        players[i].total = 0;
        players[i].aces = 0;
        players[i].eliminated = false;
    }

    for (int i = 0; i < numPlayers; i++) {
        cout << "\n" << players[i].name << "'s betting turn (Balance: $" << players[i].balance << ")\n";
        players[i].bet = readSafeFloat("Enter your bet (minimum $100): $", 100, players[i].balance);
    }

    shuffleAnimation();

    for (int i = 0; i < numPlayers; i++) {
        players[i].cards[0] = generateCard();
        players[i].cards[1] = generateCard();
        players[i].total = players[i].cards[0].value + players[i].cards[1].value;
        players[i].aces = (players[i].cards[0].name == "Ace") + (players[i].cards[1].name == "Ace");
        
        setColor(SUCCESS_COLOR);
        cout << "\n" << players[i].name << " has: " << players[i].cards[0].name << " and " 
             << players[i].cards[1].name << " (Total: " << players[i].total << ")\n";
        setColor(DEFAULT_COLOR);
    }

    for (int i = 0; i < numPlayers; i++) {
        int currentCard = 2;
        while (!players[i].eliminated && players[i].total < 21) {
            cout << "\n" << players[i].name << "'s turn (Total: " << players[i].total << ")\n";
            char option = readSafeChar("Do you want another card? (y/n): ");
            
            if (option == 'y') {
                players[i].cards[currentCard] = generateCard();
                players[i].total += players[i].cards[currentCard].value;
                if (players[i].cards[currentCard].name == "Ace") players[i].aces++;

                while (players[i].total > 21 && players[i].aces > 0) {
                    players[i].total -= 10;
                    players[i].aces--;
                }

                setColor(SUCCESS_COLOR);
                cout << "Card received: " << players[i].cards[currentCard].name 
                     << " (Total: " << players[i].total << ")\n";
                setColor(DEFAULT_COLOR);
                
                if (players[i].total > 21) {
                    setColor(ERROR_COLOR);
                    cout << players[i].name << " busted. Eliminated.\n";
                    setColor(DEFAULT_COLOR);
                    players[i].eliminated = true;
                    players[i].balance -= players[i].bet;
                }
                currentCard++;
            } else {
                break;
            }
        }
    }

    int maxPoints = -1;
    vector<int> winners;
    
    for (int i = 0; i < numPlayers; i++) {
        if (!players[i].eliminated && players[i].total <= 21) {
            if (players[i].total > maxPoints) {
                maxPoints = players[i].total;
                winners.clear();
                winners.push_back(i);
            } else if (players[i].total == maxPoints) {
                winners.push_back(i);
            }
        }
    }

    cout << "\n\n=== FINAL RESULTS ===\n";
    if (winners.empty()) {
        setColor(ERROR_COLOR);
        cout << "All players busted. No winner.\n";
        setColor(DEFAULT_COLOR);
    } else if (winners.size() == 1) {
        setColor(SUCCESS_COLOR);
        cout << "WINNER: " << players[winners[0]].name << " with " << maxPoints << " points!\n";
        setColor(DEFAULT_COLOR);
        
        float totalPrize = 0;
        for (int i = 0; i < numPlayers; i++) {
            if (i != winners[0]) {
                totalPrize += players[i].bet;
            }
        }
        players[winners[0]].balance += totalPrize;
    } else {
        setColor(TIE_COLOR);
        cout << "TIE between: ";
        for (int i = 0; i < winners.size(); i++) {
            cout << players[winners[i]].name;
            if (i < winners.size() - 1) cout << ", ";
        }
        cout << " with " << maxPoints << " points!\n";
        setColor(DEFAULT_COLOR);

        for (int i = 0; i < winners.size(); i++) {
            players[winners[i]].balance += players[winners[i]].bet;
        }
    }

    cout << "\nFinal balances:\n";
    for (int i = 0; i < numPlayers; i++) {
        cout << players[i].name << ": $" << players[i].balance << endl;
    }
}



// Implementación del Blackjack solitario (contra la banca)
void playSingleBlackjack(float& balance) {
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Insufficient balance to play. You need at least $100." << endl;
        setColor(DEFAULT_COLOR);
        return;
    }

    float bet = readSafeFloat("\nYou chose Black Jack. Enter the amount you want to bet (minimum $100): $", 100, balance);
    
    Card playerCards[10], dealerCards[10];
    int playerTotal = 0, dealerTotal = 0;
    int playerAces = 0, dealerAces = 0;

    shuffleAnimation();

    playerCards[0] = generateCard();
    playerCards[1] = generateCard();
    dealerCards[0] = generateCard();
    dealerCards[1] = generateCard();

    playerTotal = playerCards[0].value + playerCards[1].value;
    dealerTotal = dealerCards[0].value + dealerCards[1].value;

    playerAces += (playerCards[0].name == "Ace") + (playerCards[1].name == "Ace");
    dealerAces += (dealerCards[0].name == "Ace") + (dealerCards[1].name == "Ace");

    setColor(SUCCESS_COLOR);
    cout << "\nYour cards: " << playerCards[0].name << " and " << playerCards[1].name
         << " (Total: " << playerTotal << ")\n";
    setColor(INFO_COLOR);
    cout << "Dealer's visible card: " << dealerCards[0].name << endl;
    setColor(DEFAULT_COLOR);

    int extraCard = 2;
    while (playerTotal < 21) {
        char option = readSafeChar("Do you want another card? (y/n): ");
        if (option == 'y') {
            playerCards[extraCard] = generateCard();
            playerTotal += playerCards[extraCard].value;
            if (playerCards[extraCard].name == "Ace") playerAces++;

            while (playerTotal > 21 && playerAces > 0) {
                playerTotal -= 10;
                playerAces--;
            }

            setColor(SUCCESS_COLOR);
            cout << "Card received: " << playerCards[extraCard].name << " (Total: " << playerTotal << ")\n";
            setColor(DEFAULT_COLOR);
            extraCard++;
            Sleep(700);
        } else {
            break;
        }
    }

    if (playerTotal > 21) {
        setColor(ERROR_COLOR);
        cout << "You busted. You lose.\n";
        setColor(DEFAULT_COLOR);
        balance -= bet;
        return;
    }

    cout << "\nDealer's turn...\n";
    Sleep(1000);
    setColor(INFO_COLOR);
    cout << "Dealer's cards: " << dealerCards[0].name << " and " << dealerCards[1].name
         << " (Total: " << dealerTotal << ")\n";
    setColor(DEFAULT_COLOR);

    int dealerExtraCard = 2;
    while (dealerTotal < 17) {
        Sleep(800);
        dealerCards[dealerExtraCard] = generateCard();
        dealerTotal += dealerCards[dealerExtraCard].value;
        if (dealerCards[dealerExtraCard].name == "Ace") dealerAces++;

        while (dealerTotal > 21 && dealerAces > 0) {
            dealerTotal -= 10;
            dealerAces--;
        }

        setColor(INFO_COLOR);
        cout << "Dealer draws: " << dealerCards[dealerExtraCard].name << " (Total: " << dealerTotal << ")\n";
        setColor(DEFAULT_COLOR);
        dealerExtraCard++;
    }

    Sleep(1000);
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        setColor(SUCCESS_COLOR);
        cout << "You win!\n";
        setColor(DEFAULT_COLOR);
        balance += bet;
    } else if (playerTotal == dealerTotal) {
        setColor(TIE_COLOR);
        cout << "Tie. Your bet is returned.\n";
        setColor(DEFAULT_COLOR);
    } else {
        setColor(ERROR_COLOR);
        cout << "Dealer wins. You lose your bet.\n";
        setColor(DEFAULT_COLOR);
        balance -= bet;
    }

    cout << "Your current balance is: $" << balance << endl;
}

// ================== ROULETTE GAME ================== //

// Red numbers in roulette (standard positions)
const int redNumbers[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};

// Determina si un número es rojo en la ruleta
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
        cout << "║ 1. Bet by color (Easy)       ║" << endl;
        cout << "║ 2. Bet by range (Medium)     ║" << endl;
        cout << "║ 3. Bet by number (Hard)      ║" << endl;
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

// ================== KENO GAME ================== //

// Genera números aleatorios únicos para el Keno
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

// ================== SLOT MACHINE GAME ================== //

// Muestra un mensaje de derrota con arte ASCII
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
             \_/\___/ \__,_|   \_/\_/ |_|_| |_|  )" << endl;
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
                                 |_|)" << endl;
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
// ================== MAIN MENU ================== //

// Función principal del programa
int main() {
    srand(time(NULL));
    
    SetConsoleOutputCP(CP_UTF8);
    
    setColor(INFO_COLOR);
    cout << "Welcome to Bet++, the casino where we turn gamblers into millionaires... or gambling poor.\n";
    setColor(DEFAULT_COLOR);

    User user;
    cout << "Username: ";
    getline(cin, user.name);
    user.age = readSafeInt("Age: ", 1, 120);

    if (user.age < 18) {
        setColor(ERROR_COLOR);
        cout << "You must be at least 18 years old to play.\n";
        setColor(DEFAULT_COLOR);
        return 0;
    }

    float balance = readSafeFloat("Enter your initial balance (minimum $100): $", 100);

    char keepPlaying = 'y';
    while (keepPlaying == 'y') {
        setColor(INFO_COLOR);
        cout << "\n-------------------------------\n";
        cout << "|      MAIN MENU              |\n";
        cout << "|-----------------------------|\n";
        cout << "| 1. Single Player Blackjack  |\n";
        cout << "| 2. Multiplayer Blackjack    |\n";
        cout << "| 3. Roulette                 |\n";
        cout << "| 4. Keno                     |\n";
        cout << "| 5. Slot Machine             |\n";
        cout << "| 6. Exit                     |\n";
        cout << "-------------------------------\n";
        setColor(DEFAULT_COLOR);
        
        int option = readSafeInt("Select an option: ", 1, 6);
        
        switch (option) {
            case 1: playSingleBlackjack(balance); break;
            case 2: playMultiplayerBlackjack(); break;
            case 3: playRoulette(balance); break;
            case 4: playKeno(balance); break;
            case 5: playSlots(balance); break;
            case 6: 
                cout << "Thanks for playing at Bet++, " << user.name << ". See you next time!\n";
                return 0;
        }

        if (balance < 100) {
            setColor(ERROR_COLOR);
            cout << "\nInsufficient balance to keep playing.\n";
            setColor(DEFAULT_COLOR);
            break;
        }

        keepPlaying = readSafeChar("\nDo you want to return to the main menu? (y/n): ");
    }

    setColor(INFO_COLOR);
    cout << "\nThanks for playing at Bet++, " << user.name << ". Come back soon!\n";
    setColor(DEFAULT_COLOR);
    return 0;
}
