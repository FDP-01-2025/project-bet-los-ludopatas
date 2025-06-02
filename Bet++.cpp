#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

int jugador [10];
int banca [10];
int totalJugador = 0 , totalBanca =0;
int i, modo;
float saldo, saldPerdido, saldGanado;

cout << "Bienvenido al casino Bet++, donde convertimos ludopatas en millonario o en ludopobres."<<endl;
cout << "Por favor ingrese el monoto de efectivo que desea utilizar (SALDO MINIMO REQUERIDO $100) "<<endl;
cin >> saldo;
cout << "Ahora, por favor elija un modo de juego"<<endl;
cout << "____________________________ "<<endl;
cout << "|1.Black Jack               |"<<endl;
cout << "|2.Tragamonedas             |"<<endl;
cout << "|3.Ruleta                   |"<<endl;
cout << "|4.Keno                     |"<<endl;
cout << "|___________________________|"<<endl;
cin >> modo;


}