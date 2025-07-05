#include <iostream>
#include <ctime>
#include <random>
#include <string>
using namespace std;

void difficult_easy();
void difficult_mid();
void difficult_malphite();

int main (){
    int select;
    cout<<"================================ SPIN MACHINE MENU ================================"<< endl;
    cout<<"||                 Do you want to spin the slot machine?                         ||"<< endl;
    cout<<"|| 1.Yes, of course sir, the ludopathy has consumed me and my saves too(jijijaja)||"<< endl;
    cout<<"|| 2.Nao, im free, i dont need balatro balatro anymore                           ||"<< endl;
    cout<<"==================================================================================="<< endl;
    cin >> select;

    switch(select){
        case 1:
            do{
            cout <<"================================== Select your difficult ==================================="<< endl;
            cout <<"||1.Fear of bet (An easy way to win but you dont win too much)                            ||"<< endl;
            cout <<"||2.Normal (A normal slot machine experience)                                             ||"<< endl;
            cout <<"||3.GO FOR THE BIG SHOOOT(nOt ToO MUCH P0S1BiLLIes tOO W1n but YOU can WIN A LOT OF MONEY)||"<< endl;
            cout <<"============================================================================================"<< endl;
            cin >> select;
            switch(select){
                case 1:
                    difficult_easy();
                break;

                case 2:
                    difficult_mid();
                break;

                case 3:
                    difficult_malphite();
                break;

                default:
                    cout <<"========================================="<< endl;
                    cout <<"||ERROR, PLEASE DONT TEST MORE THE CODE||"<< endl;
                    cout <<"========================================="<< endl;
                break;
            }
            cout <<"Spin again?"<<endl;
            cout <<"1.Yes"<< endl;
            cout <<"2.No"<< endl;
            cin >> select;
            } while(select != 2);
        break;

        case 2:
            cout <<"============================================================================================"<< endl;
            cout <<"||Why do you select slot machine, just to try?, dont be rude the machine have feelings too||"<< endl,
            cout <<"||Bro respect                                                                             ||"<< endl;
            cout <<"============================================================================================"<< endl;
        break;

        default:
            cout <<"============================================="<< endl;
            cout <<"||ERROR balatro balatrez is playing balatro||"<< endl;
            cout <<"============================================="<< endl;
        break;
    }
    return 0;
}

    void difficult_easy(){
        int matrix[3][3];
        std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
        std::uniform_int_distribution<int> range(1,7);

        string symbols[8] = {"", "*", "B", "C", "D", "E", "F", "7"};
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
    }
     
void difficult_mid(){
    int matrix[3][3];
    std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); /*La libreria "random" incluye una variedad de motores para generar numeros aleatorios
    , este es uno de ellos, el static cast lo ocupamos para que nos devuelva el valor que nos de time (nullptr)
    como un entero, y siendo time (nullptr) la cantidad de segundos actuales desde su creacion, por lo que su valor esta en constante cambio */
    std::uniform_int_distribution<int> range(1,10); //Con esto definimos la forma en la que se genera y el tipo de variable

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
}

void difficult_malphite(){
    int matrix[3][3];
    std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    std::uniform_int_distribution<int> range(1,15);

    string symbols[16] = {"", "*", "B", "C", "D", "E", "F", "7","8","X","$","Y","0","♪","¬","⨂"};
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
}