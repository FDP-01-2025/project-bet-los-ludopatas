#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

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
string nombreDeusuario, edadDeusuario;

cout << "Bienvenido al casino Bet++, donde convertimos ludopatas en millonario o en ludopobres."<<endl;

cout << "Por favor, ingrese un nombre de usuario para continuar:";
getline (cin, nombreDeusuario);

cout << "Por favor, ingrese su edad:";
getline (cin, edadDeusuario);
if (edadDeusuario.empty()){
    cout << "La edad no puede estar vacia. Por favor, ingrese su edad." << endl;
    return 0;
}
ofstream archivoEdad ("edad.txt");
if (archivoEdad.is_open()){
    archivoEdad << "Edad del usuario" " " << edadDeusuario << endl;
    archivoEdad.close();
    cout << "La edad del usuario ha sido guardada exitosamente." " " <<endl;
}else {
    cout << "Error al abrir el archivo para guardar la edad del usuario." << endl;
}
if (edadDeusuario < "18"){
    cout << "Lo sentimos, debes de ser mayor de 18 años de edad para jugar en Bet++." << endl;
    return 0;
}



ofstream archivo ("usuario.txt");
if (archivo.is_open()){
    archivo << "Bienvenido al casino Bet++" " " << nombreDeusuario << endl;
    archivo.close();
    cout << "El nombre de usuario ha sido guardado exitosamente," " " << nombreDeusuario << " " ",gracias" <<endl;
}else {
    cout << "Error al abrir el archivo para guardar el nombre de usuario." << endl;
}



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

    do{
        cout << "\nAhora, por favor elija un modo de juego" << endl;
        cout << "____________________________ " << endl;
        cout << "|1. Black Jack              |" << endl;
        cout << "|2. Tragamonedas (no listo)|" << endl;
        cout << "|3. Ruleta (no listo)      |" << endl;
        cout << "|4. Keno (no listo)        |" << endl;
        cout << "|__________________________|" << endl;
        cout << "Opción: ";
        cin >> modo;
 switch (modo) {
            case 1: {
                if (saldo < 100) {
                    cout << "Saldo insuficiente para jugar. Debes tener al menos $100." << endl;
                    break;
                }

                cout << "\nHas elegido Black Jack. Ingrese el monto que desea apostar (mínimo $100): ";
                cin >> apuesta;

                if (apuesta < 100 || apuesta > saldo) {
                    cout << "Apuesta no válida. Debe ser al menos $100 y no mayor que tu saldo actual.\n";
                    break;
                }

                // Variables del juego
                Carta cartasJugador[10];
                Carta cartasBanca[10];
                int totalJugador = 0, totalBanca = 0;
                int asesJugador = 0, asesBanca = 0;

                // Cartas iniciales
                cartasJugador[0] = generarCarta();
                cartasJugador[1] = generarCarta();
                cartasBanca[0] = generarCarta();
                cartasBanca[1] = generarCarta();

                totalJugador = cartasJugador[0].valor + cartasJugador[1].valor;
                totalBanca = cartasBanca[0].valor + cartasBanca[1].valor;

                asesJugador += (cartasJugador[0].nombre == "As") + (cartasJugador[1].nombre == "As");
                asesBanca += (cartasBanca[0].nombre == "As") + (cartasBanca[1].nombre == "As");

                cout << "\nTus cartas: " << cartasJugador[0].nombre << " y " << cartasJugador[1].nombre
                    << " (Total: " << totalJugador << ")\n";
                cout << "Carta visible de la banca: " << cartasBanca[0].nombre << endl;

                int cartaExtra = 2;
                char opcion;

                while (totalJugador < 21) {
                    cout << "¿Deseas otra carta? (s = sí, n = no): ";
                    cin >> opcion;
                    if (opcion == 's' || opcion == 'S') {
                        cartasJugador[cartaExtra] = generarCarta();
                        totalJugador += cartasJugador[cartaExtra].valor;
                        if (cartasJugador[cartaExtra].nombre == "As") asesJugador++;

                        // Ajustar valor de As si te pasas de 21
                        while (totalJugador > 21 && asesJugador > 0) {
                            totalJugador -= 10;
                            asesJugador--;
                        }

                        cout << "Carta recibida: " << cartasJugador[cartaExtra].nombre << " (Total: " << totalJugador << ")\n";
                        cartaExtra++;
                    }
                    else {
                        break;
                    }
                }

                if (totalJugador > 21) {
                    cout << "Te pasaste de 21. Pierdes.\n";
                    saldo -= apuesta;
                    break;
                }

                cout << "\nTurno de la banca...\n";
                cout << "Cartas de la banca: " << cartasBanca[0].nombre << " y " << cartasBanca[1].nombre
                    << " (Total: " << totalBanca << ")\n";

                int cartaBancaExtra = 2;
                while (totalBanca < 17) {
                    cartasBanca[cartaBancaExtra] = generarCarta();
                    totalBanca += cartasBanca[cartaBancaExtra].valor;
                    if (cartasBanca[cartaBancaExtra].nombre == "As") asesBanca++;

                    while (totalBanca > 21 && asesBanca > 0) {
                        totalBanca -= 10;
                        asesBanca--;
                    }

                    cout << "La banca saca: " << cartasBanca[cartaBancaExtra].nombre << " (Total: " << totalBanca << ")\n";
                    cartaBancaExtra++;
                }

                if (totalBanca > 21 || totalJugador > totalBanca) {
                    cout << "¡Ganaste!\n";
                    saldo += apuesta;
                }
                else if (totalJugador == totalBanca) {
                    cout << "Empate. Se devuelve tu apuesta.\n";
                }
                else {
                    cout << "La banca gana. Pierdes tu apuesta.\n";
                    saldo -= apuesta;
                }

                cout << "Tu saldo actual es: $" << saldo << endl;
                break;
            }

            default:
                cout << "Modo de juego aún no implementado. Por favor, elige otra opción.\n";
        }

        if (saldo < 100) {
            cout << "Tu saldo es insuficiente para seguir jugando. ¡Gracias por apostar en Bet++!" << endl; 
            break;
        }

        cout << "\n¿Deseas jugar de nuevo? (s = sí, n = no): ";
        cin >> jugarDeNuevo;

    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S');

    cout << "Gracias por jugar en Bet++! Tu saldo final es: $" << saldo << endl;

    return 0;
}