#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
  int num;
//numero aleotorio 
   

    int numeros[10];
    int count = 0;

    while (count < 10) {
        int num = rand() % 80 + 1;
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

    
    for (int i = 0; i < 10; i++) {
       
    }
   
// Ingreso de numeros del jugador 
cout << " INGRESO DE NUMEROS DEL JUGADOR \n";

int numerosJugador[10];
for (int i = 0; i < 10; i++) {
    cout << "Numero #" << i + 1 << ": ";
    cin >> numerosJugador[i];
    
    if (num <=1 || num > 80) {
        cout << "NUMERO INVALIDO. INGRESA UNO ENTRE 1 Y 80\n";
        i--;
    } else {
        numerosJugador[i] = num;
    }
}

cout << "\nNumeros ingresados por el jugador:\n";
for (int i = 0; i < 10; i++) {
    cout << numerosJugador[i] << " ";
}
cout << " Fin del turno \n";

    return 0;
}
