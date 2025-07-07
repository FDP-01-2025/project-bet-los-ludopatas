#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "estructuras.h"
#include "colors.h"
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

const int MAX_JUGADORES = 5;
const int MAX_CARTAS = 10;

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
        c.name = "Jack";
        c.value = 10;
    } else if (number == 12) {
        c.name = "Queen";
        c.value = 10;
    } else {
        c.name = "King";
        c.value = 10;
    }
    return c;
}

// Implementación del Blackjack multijugador (2-5 jugadores)
void playMultiplayerBlackjack() {
    int numPlayers = readSafeInt("Enter number of players (2-5): ", 2, 5);
    vector<Player> players(numPlayers);
    
    for (int i = 0; i < numPlayers; i++) {
        cout << "\nPlayer " << i + 1 << " data:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, players[i].name);
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

    float bet = readSafeFloat("\nYou chose Blackjack. Enter the amount you want to bet (minimum $100): $", 100, balance);
    
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

#endif // BLACKJACK_H