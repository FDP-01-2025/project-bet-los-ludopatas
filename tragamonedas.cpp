#include <iostream>
#include <ctime>
#include <random>
#include <string>
using namespace std;

int main (){

    std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); /*La libreria "random" incluye una variedad de motores para generar numeros aleatorios
    , este es uno de ellos, el static cast lo ocupamos para que nos devuelva el valor que nos de time (nullptr)
    como un entero, y siendo time (nullptr) la cantidad de segundos actuales desde su creacion, por lo que su valor esta en constante cambio */
    std::uniform_int_distribution<int> range(1,10); //Con esto definimos la forma en la que se genera y el tipo de variable

    int matrix [3][3], select, valor;

    cout<<"Do you want to spin the slot machine?"<< endl;
    cout<<"1.Yes, of course sir, the ludopathy has consumed me and my saves too(jijijaja)"<< endl;
    cout<<"2.Nao, im free, i dont need balatro balatro anymore"<< endl;
    cout<<"3.I want to play other game this one sucks"<< endl;
    cin >> select;

    switch(select){
        case 1:
        do{
        string symbols[11] = {"", "*", "B", "C", "D", "E", "F", "7", "8", "X", "$"};
        cout <<"The result is:"<< endl;
        cout << endl;
        for (int i = 0; i<3; i++){
            for (int j=0; j<3; j++){
            matrix[i][j]= range(rng);
            cout<< symbols[matrix[i][j]] << " ";
            }
            cout << endl;
        }
        cout << endl;

        if ((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2]) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2]) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2])){
            cout <<"You Won the machine respect and 2 dollars"<< endl;
        } else {
            cout <<"U lost, jijija"<< endl;
        }
        
        cout<< "Do you want to play again? dont give up the ludopathy waits..."<< endl;
        cout<< "1.Yeah buddy"<< endl;
        cout<< "Any other key.Nooooooooooooo"<< endl;
        cin >> select;

        } while(select==1);
        break;

        case 2:
            cout <<"Why do you select slot machine, just to try?, dont be rude the machine have feelings too"<< endl,
            cout <<"Bro respect"<< endl;
        break;

        case 3:
            cout <<"Be free my little ludopatus"<< endl;
        break;

        default:
            cout <<"ERROR balatro balatrez is playing balatro"<< endl;
        break;
    }

    return 0;
}