#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

struct Carta{
    string nombre;
    int valor;
};

Carta generarCarta() {
    int numero = rand() % 13 + 1;
    Carta c;

if (numero == 1) {
    c.nombre = "As";
    c.valor = 11;
}else if (numero >= 2 && numero <= 10){
    c.nombre = to_string(numero);
    c.valor = numero;
}else if ( numero == 11){
    c.nombre = "J";
    c.valor = 10;
}else if (numero == 12){
    c.nombre = "Q";
    c.valor = 10;
}else {
    c.nombre = "K";
    c.valor = 10;
}

return c;

}

int main() {

int jugador [10];
int banca [10];
int totalJugador = 0 , totalBanca =0;
int i, modo;
float saldo, saldPerdido, saldGanado, apuesta;
char jugarDeNuevo;

cout << "Bienvenido al casino Bet++, donde convertimos ludopatas en millonario o en ludopobres."<<endl;
cout << "Por favor ingrese el monoto de efectivo que desea utilizar (SALDO MINIMO REQUERIDO $100) "<<endl;
cin >> saldo;
if (saldo >= 100 && saldo <=200 ){
    cout <<"Por lo visto es tu primera vez en las Bet++. Bienvenido al mejor casino de apuestas online"<<endl;
}
else if (saldo >= 200 && saldo < 300){
    cout <<"¡Estas apostando cantidades grandes!, Esperamos y no las pierdas"<<endl;
}else if (saldo >= 300 && saldo < 400){
    cout << "¡WOW!, esas si son sumas de dimero elevadas, te regalaremos ¡$20 de bonus!. Tu saldo actualizado es de:"<< saldo + 20 << endl;
} else if (saldo >= 400 && saldo < 1000){
    cout << "La suma de dinero elegida es muy alta, eres un verdadero ludopata!"<<endl;
}else if (saldo > 1000){
    cout << "¡WOW! esa suma de dinero es muy grande, bienvendo al verdadero club de los ludopatas,"<<endl;
    cout <<" Por eso toma este humilde regalo:"<< saldo + 100 << endl;
}

srand(time(0));

    
        cout << "\nAhora, por favor elija un modo de juego" << endl;
        cout << "____________________________ " << endl;
        cout << "|1. Black Jack              |" << endl;
        cout << "|2. Tragamonedas (no listo)|" << endl;
        cout << "|3. Ruleta (no listo)      |" << endl;
        cout << "|4. Keno (no listo)        |" << endl;
        cout << "|__________________________|" << endl;
        cout << "Opción: ";
        cin >> modo;

return 0;
}