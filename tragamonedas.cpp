#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <windows.h>
using namespace std;

void difficultyEasy(); // I prefer to declare the functions on the botoom of the code
void difficultyMid();
void difficultyMalphite();
void waitASecond(double t);

int main (){
    SetConsoleOutputCP(CP_UTF8); //This is to see the emojis on the code

    int select; //first menu to decide if you want to play 
    cout<<"================================ SPIN MACHINE MENU ================================"<< endl;
    cout<<"||                    Do you want to spin the slot machine?                      ||"<< endl;
    cout<<"|| 1.Yes, of course sir, the ludopathy has consumed me and my saves too(jijijaja)||"<< endl;
    cout<<"|| 2.Nao, im free, i dont have enemies                                           ||"<< endl;
    cout<<"==================================================================================="<< endl;
    cin >> select;

    switch(select){
        case 1: 
            do{ // a menu to select the difficulty
            cout <<"================================== Select your difficulty ==============================="<< endl;
            cout <<"||1.Easy win (...Only if you are unlucky, like me... also you cant win jackpot)        ||"<< endl;
            cout <<"||2.Normal (A normal slot machine experience)                                          ||"<< endl;
            cout <<"||3.Rock Solid (You can win a lot of money here... but its difficult to win)           ||"<< endl;
            cout <<"========================================================================================="<< endl;
            cin >> select;
            switch(select){
                case 1:
                    difficultyEasy();
                break;

                case 2:
                    difficultyMid();
                break;

                case 3:
                    difficultyMalphite();
                break;

                default:
                    cout <<"========================================="<< endl;
                    cout <<"||ERROR, PLEASE DONT TEST MORE THE CODE||"<< endl; // in case that the user dont follow the guide 👍
                    cout <<"========================================="<< endl;
                break;
            }
            cout <<"Spin again?"<<endl;
            cout <<"1.Yes 2.No"<< endl;
            cout <<"======================================================================="<< endl;
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
            cout <<"||ERROR balatro balatrez is playing balatro||"<< endl;// the same of the other default case
            cout <<"============================================="<< endl;
        break;
    }
    return 0;
}

    void difficultyEasy(){
        int matrix[3][3];
        string symbols[6] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍"};
        mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
        uniform_int_distribution<int> range(1,5);

        cout <<"======================================================================="<< endl;
        cout <<"The result is..."<< endl;
        cout << endl;

        for (int i = 0; i<3; i++){
            for (int j=0; j<3; j++){
                matrix[i][j]= range(rng);
                cout<<"| " << symbols[matrix[i][j]] << " |";
            }
            waitASecond(0.95);
            cout << endl;
        }
        cout << endl;

        if ((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2]) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2]) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2])){
            cout << R"(
            /\_/\___  _   _  __      _(_)_ __  
            \_ _/ _ \| | | | \ \ /\ / / | '_  )
             / | (_) | |_| |  \ V  V /| | | | |
             \_/\___/ \__,_|   \_/\_/ |_|_| |_| )" << endl;
            cout <<"        (You Won the machine respect and some money)"<< endl;
            cout <<"======================================================================="<< endl;
            
        } else {
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
         ░▒█▓▓▓██▓▓▓██████████████████▓▓▓██▓▓▓▓█░          
         ░█▓▓▓▓▓▓▓▓▓██▓████████████▓▓██▓▓▓▓▓▓▓▓█▒          )"<< endl;
            cout <<"             U lost, jijijija"<< endl;
            cout <<"=================================================================="<< endl;
        }
    }
     
void difficultyMid(){
    int matrix[3][3];
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); /*La libreria "random" incluye una variedad de motores para generar numeros aleatorios
    , este es uno de ellos, el static cast lo ocupamos para que nos devuelva el valor que nos de time (nullptr)
    como un entero, y siendo time (nullptr) la cantidad de segundos actuales desde su creacion, por lo que su valor esta en constante cambio */
    uniform_int_distribution<int> range(1,7); //Con esto definimos la forma en la que se genera y el tipo de variable

    string symbols[8] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ "};
    cout <<"======================================================================="<< endl;
    cout <<"The result is:"<< endl;
    cout << endl;

    for (int i = 0; i<3; i++){
        for (int j=0; j<3; j++){
            matrix[i][j]= range(rng);
            cout<<"| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);
        cout << endl;
        }
    cout << endl;

    if ((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2]) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2]) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2])){
            if((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2] and matrix[0][0] == 7) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2] and matrix[1][0] == 7) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2] and matrix[2][0] == 7)){
            cout <<R"(
              __             _                _   
              \ \  __ _  ___| | ___ __   ___ | |_ 
               \ \/ _` |/ __| |/ / '_ \ / _ \| __|
            /\_/ / (_| | (__|   <| |_) | (_) | |_ 
            \___/ \__,_|\___|_|\_\ .__/ \___/ \__|
                                 |_|)"<< endl; //apparently the R"()" is use to put ascii art cuz this allow you to put exactly the same text that you putted inside including the jump of the lines
            cout <<"======================================================================="<< endl;
            }else{
            cout << R"(
            /\_/\___  _   _  __      _(_)_ __  
            \_ _/ _ \| | | | \ \ /\ / / | '_  )
             / | (_) | |_| |  \ V  V /| | | | |
             \_/\___/ \__,_|   \_/\_/ |_|_| |_| )" << endl;
            cout <<"        (You Won the machine respect and some money)"<< endl;
            cout <<"======================================================================="<< endl;
            }
        } else {
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
         ░▒█▓▓▓██▓▓▓██████████████████▓▓▓██▓▓▓▓█░          
         ░█▓▓▓▓▓▓▓▓▓██▓████████████▓▓██▓▓▓▓▓▓▓▓█▒          )"<< endl;
            cout <<"             U lost, jijijija"<< endl;
            cout <<"=================================================================="<< endl;
        }
}

void difficultyMalphite(){
    int matrix[3][3];
    mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    uniform_int_distribution<int> range(1,10);

    string symbols[11] = {"", u8"🃏", u8"👑", u8"✨", u8"💎", u8"💍", u8"💰", u8"7️⃣ ", u8"🔔", u8"🍀", u8"🗿"};
    cout <<"======================================================================="<< endl;
    cout <<"The result is:"<< endl;
    cout << endl;

    for (int i = 0; i<3; i++){
        for (int j=0; j<3; j++){
            matrix[i][j]= range(rng);
            cout<<"| " << symbols[matrix[i][j]] << " |";
        }
        waitASecond(0.95);
        cout << endl;
        }
    cout << endl;

    if ((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2]) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2]) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2])){
            if((matrix[0][0] == matrix[1][1] and matrix[1][1] == matrix[2][2] and matrix[0][0] == 7) or (matrix[1][0] == matrix[1][1] and matrix[1][1] == matrix[1][2] and matrix[1][0] == 7) or (matrix[2][0] == matrix[1][1] and matrix[1][1] == matrix[0][2] and matrix[2][0] == 7)){
            cout <<R"(
              __             _                _   
              \ \  __ _  ___| | ___ __   ___ | |_ 
               \ \/ _` |/ __| |/ / '_ \ / _ \| __|
            /\_/ / (_| | (__|   <| |_) | (_) | |_ 
            \___/ \__,_|\___|_|\_\ .__/ \___/ \__|
                                 |_|)"<< endl; //apparently the R"()" is use to put ascii art cuz this allow you to put exactly the same text that you putted inside including the jump of the lines
            cout <<"======================================================================="<< endl;
            }else{
            cout << R"(
            /\_/\___  _   _  __      _(_)_ __  
            \_ _/ _ \| | | | \ \ /\ / / | '_  )
             / | (_) | |_| |  \ V  V /| | | | |
             \_/\___/ \__,_|   \_/\_/ |_|_| |_| )" << endl;
            cout <<"        (You Won the machine respect and some money)"<< endl;
            cout <<"======================================================================="<< endl;
            }
        } else {
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
         ░▒█▓▓▓██▓▓▓██████████████████▓▓▓██▓▓▓▓█░          
         ░█▓▓▓▓▓▓▓▓▓██▓████████████▓▓██▓▓▓▓▓▓▓▓█▒          )"<< endl;
            cout <<"             U lost, jijijija"<< endl;
            cout <<"=================================================================="<< endl;
    }
}

void waitASecond(double t){
  time_t timer = time(nullptr);
  while(time(nullptr) - timer < t);
}