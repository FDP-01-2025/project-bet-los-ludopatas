#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    cout << " PROBANDO GENERACION ALEATORIA DE NUMEROS KENO <<\n";

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

    cout << "Numeros sorteados:<<\n";
    for (int i = 0; i < 10; i++) {
        cout << numeros[i] << " ";
    }
   

    return 0;
}
