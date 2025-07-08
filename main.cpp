/*
 
 * 
 * Este programa implementa un casino virtual con varios juegos:
 * - Blackjack (solitario y multijugador)
 * - Ruleta
 * - Keno
 * - Máquinas tragamonedas
 * 
 * Autores:  García Osorio, Eduardo Daniel.
   *Carnet:* 00014325

2. *Nombre completo:* Girón Vigil, Saul Ernesto,00033325
   *Carnet:* 00033325

3. *Nombre completo:* Armando José Iglesias Aguilera
   *Carnet:* 00107425

4. *Nombre completo:* Alfredo Antonio Guarita Hernandez
   *Carnet:* ,00155425

]
 * Fecha: [6 de julio de 2025]
 * Versión: 1.0 (esperamos que no sea la última :D)
 */
// * Casino Bet++ - Bet++ no es solo un juego de casino, es la emoción de arriesgar, la astucia del jugador y la adrenalina del todo o nada, envueltos en líneas de código que laten como un corazón apostador."

// ================== LIBRERÍAS NECESARIAS ================== //


#include "librerias.h"
#include "estructuras.h" 
#include "colors.h"
#include "blackJack.h"
#include "ruleta.h"
#include "keno.h"
#include "tragaMonedas.h"
    

using namespace std;

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);

    setColor(INFO_COLOR);
    cout << R"(
╔════════════════════════════════════════════════╗
║                                                ║
║                   🂠 🂠 🂠                       ║
║                BET++ CASINO                    ║
║                   🂠 🂠 🂠                       ║
║                                                ║
║      Where we turn gamblers into millionaires  ║
║                 ...or gambling poor.           ║
║                                                ║
╚════════════════════════════════════════════════╝
)" << endl;
    setColor(DEFAULT_COLOR);

    cout << "\nWelcome to Bet++, the casino where we turn gamblers into millionaires... or gambling poor.\n";

    User user;
    cout << "\nUsername: ";
    getline(cin, user.name);
    user.age = readSafeInt("Age: ", 1, 120);

    if (user.age < 18) {
        setColor(ERROR_COLOR);
        cout << "\nYou must be at least 18 years old to play.\n";
        setColor(DEFAULT_COLOR);
        return 0;
    }

    float balance = readSafeFloat("Enter your initial balance (minimum $100): $", 100);

    char keepPlaying = 'y';
    while (keepPlaying == 'y') {
        system("cls");
        setColor(CYAN_COLOR);
        cout << R"(
╔══════════════════════════════════════════════════════╗
║                     MAIN MENU                        ║
╠══════════════════════════════════════════════════════╣
║  1. Single Player Blackjack    🂠 🂡 🂢                ║
║  2. Multiplayer Blackjack      🂣 🂤 🂥                ║
║  3. Roulette                   🎡                   ║
║  4. Keno                       🎯                   ║
║  5. Slot Machine               🎰                   ║
║  6. Exit                       🚪                    ║
╚══════════════════════════════════════════════════════╝
)" << endl;
        setColor(DEFAULT_COLOR);

        int option = readSafeInt("\nSelect an option: ", 1, 6);

        switch (option) {
            case 1: playSingleBlackjack(balance); break;
            case 2: playMultiplayerBlackjack(); break;
            case 3: playRoulette(balance); break;
            case 4: playKeno(balance); break;
            case 5: playSlots(balance); break;
            case 6:
                setColor(MAGENTA_COLOR);
                cout << "\nThanks for playing at Bet++, " << user.name << ". See you next time!\n";
                setColor(DEFAULT_COLOR);
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
