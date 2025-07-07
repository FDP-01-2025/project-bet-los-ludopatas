#  Bet++

## Descripción del Proyecto

 Bet++ es una plataforma de casino en línea diseñada con el objetivo de ofrecer entretenimiento y diversión a personas que desean experimentar la emoción de apostar sin arriesgar dinero real.
 El juego incluye cuatro de las modalidades más clásicas de los casinos: Blackjack, tragamonedas, ruleta y Keno. El usuario tendrá la posibilidad de elegir la modalidad que más le guste y, además, podrá disfrutar la experiencia en compañía de sus amigos.

## Equipo

- **Nombre del equipo:** Bet++ (Los ludópatas)

### Integrantes del equipo

1. **Nombre completo:** García Osorio, Eduardo Daniel.
   **Carnet:** 00014325

2. **Nombre completo:** Girón Vigil, Saul Ernesto
   **Carnet:** 00033325

3. **Nombre completo:** Armando José Iglesias Aguilera
   **Carnet:** 00107425
4. **Nombre completo:** Alfredo Antonio Guarita Hernandez
   **Carnet:** 00155425

## Requisitos Previos
 Para poder disfrutar de Bet++ en tu computadora, necesitarás tener instaladas algunas herramientas. ¡No te preocupes, es más sencillo de lo que parece!

1. **Git:** Es una herramienta para descargar el código del juego Puedes obtenerlo 
desde la página oficial: https://git-scm.com/downloads

 **Instalación:**Sigue las instrucciones de instalación para tu sistema operativo. Generalmente, es un "siguiente, siguiente" sencillo.

2. **Un Compilador de C++ (GCC recomendado):** Esta herramienta es la que convierte el código del juego en un programa    que tu computadora puede entender y ejecutar.

 **Para Windows:** Te recomendamos instalar MinGW, que incluye el compilador GCC. Puedes encontrar una guía sencilla para instalarlo buscando en Google "instalar MinGW GCC en Windows".

 **Para Linux o macOS:** Es muy probable que ya lo tengas instalado. Si no, puedes instalarlo fácilmente a través de la terminal:

 Linux (basado en Debian/Ubuntu): Abre tu terminal y escribe: sudo apt install build-essential

 **macOS:** Abre tu terminal y escribe: xcode-select --install

## Instrucciones de Ejecución
1.  Abre una herramienta llamada "Git Bash"
2. Clona este repositorio en tu máquina local:
   git clone [https://github.com/FDP-01-2025/project-bet-los-ludopatas]
    y luego escribe code . para abrir el visual studio code si lo tienes instalado 
3. Abrir la terminal  para esto ocupa crt+ñ.
4. una vez abierto la terminal escribe esto:
 g++ -o "nombre de tu exe" "nombre del archivo recuerda agregar el .cpp al final"
 ejemplo:
 g++ -o baki ludopatas.cpp
   luego escribe esto:
   .\baki.exe
### si no tienes visual studio code
**Navegar a la Carpeta del Juego:**
    * Ahora, ingresa a la carpeta del juego en la terminal.Para eso ingresa en 
      Git Bash.
        cd project-bet-los-ludopatas
4.  **Compilar el Juego (prepararlo para ejecutar):**
     Vamos a convertir el código del juego en un programa que tu computadora pueda ejecutar. Escribe el siguiente comando y presiona enter :
        g++ -o baki ludopatas.cpp

5.  **Ejecutar el Juego:**
     ¡Casi listo! Ahora puedes iniciar Bet++. Escribe el siguiente comando y presiona Enter:
        ./baki.exe
        *(Si estás en Linux o macOS, simplemente usa: `./baki)*

 ## Cómo Jugar
Al iniciar Bet++, el programa te guiará a través de los primeros pasos:
1. **Ingreso de Datos:**Se te pedirá que ingreses tu nombre y edad.
nota: Solo para mayores de edad.
2. **Saldo Inicial:** Deberás ingresar un saldo inicial. El mínimo requerido para comenzar a jugar es $100.

3. **menu**:Una vez que hayas ingresado tus datos y saldo, el menú principal de Bet++ aparecerá, ofreciéndote las siguientes opciones de juego.
  ### Blackjack:
 cuenta con dos modos uno contra la banca y el otro multijugador.

**solitario :**Juega contra la banca. El objetivo es que tu mano sume lo más cerca posible de 21 sin pasarse,
 Puedes pedir más cartas o  quedarte con las que tienes. 

 **multijugador:** Configura una partida para 2 a 5 jugadores. Cada jugador gestiona su propia mano.

### Ruleta:
Tienen dos opciones de apuesta:

**Apostar a un Color:** Elige entre rojo o negro. Si aciertas el color donde cae la bola, duplicas tu apuesta 

Apostar a un Número: Elige un número entre 0 y 36. Si la bola cae en tu número exacto, ¡ganas!.

### Keno:
Tienen dos opciones de apuesta:

**Modo Solitario:** Elige 10 números entre 1 y 80. Se sortearán 10 números al azar. Cuantos más de tus números coincidan con los sorteados, mayor será tu premio.

**Modo Multijugador:** Tú y un segundo jugador eligen 10 números cada uno. El programa sortea 10 números y compara los aciertos de ambos jugadores. 

 ### Tragamonedas:
 Selecciona tu nivel de dificultad:

**Fácil:** Apuesta mínima, símbolos más comunes. Ganancia de 2 veces tu apuesta por 3 símbolos coincidentes en la línea central o diagonales.

**Intermedio:** Apuesta mayor, Jackpot (tres 7s) paga 10 veces tu apuesta, y una victoria normal (otros 3 símbolos) paga 3 veces tu apuesta.

**Difícil:** La mayor apuesta, Jackpot (tres 7s) paga 20 veces tu apuesta, y una victoria normal (otros 3 símbolos) paga 5 veces tu apuesta.

Cada modo tiene una opcion para seguir jugando o regresar al menu principal.

4. **Salir:** Termina tu sesión de juego y el programa te agradecerá por haber jugado.