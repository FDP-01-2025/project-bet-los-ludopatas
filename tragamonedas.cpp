#include <iostream>
#include <ctime>
#include <random>
using namespace std;

int main (){

    std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); /*La libreria "random" incluye una variedad de motores para generar numeros aleatorios
    , este es uno de ellos, el static cast lo ocupamos para que nos devuelva el valor que nos de time (nullptr)
    como un entero, y siendo time (nullptr) la cantidad de segundos actuales desde su creacion, por lo que su valor esta en constante cambio */
    std::uniform_int_distribution<int> range(1,10); //Con esto definimos la forma en la que se genera y el tipo de variable

    for (int i = 0; i<3; i++){
        cout <<range(rng)<< endl;
    }

    return 0;
}