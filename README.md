[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - Casino Bet++


![image](https://github.com/user-attachments/assets/71b3467a-0bf9-40a0-b14e-1ef08b32d1f1)

El juego Bet++ se basa en la temática de un casino virtual moderno, diseñado para ofrecer una experiencia de entretenimiento digital que simula dinámicas reales de un casino físico.

La ambientación se enfoca en brindar al usuario una variedad de modos de juego clásicos, como la ruleta, blackjack, tragamonedas y keno, cada modo de juego está pensado para ofrecer una dinámica distinta y mantener la atención del usuario.

Esta diversidad permite una experiencia más rica, entretenida y cercana a un casino real, dentro de un entorno digital simple y accesible.


# 🧠 Mecánica Principal del Juego


If-else: Determina si hay combinaciones ganadoras también maneja la lógica del juego y las decisiones del jugador.

While: Mantiene el juego en ejecución hasta que el jugador se quede sin créditos o desea salir. 

Switch-case: maneja el menú de opciones (jugar, ver créditos, salir).

For: Tiene diverso papel en cada modo de juego en blackjack es encargado de repartir las cartas. En tragamonedas generar 3 símbolos aleatorios en los rodillos. En keno se utiliza para que el jugador elija 5 números (validando cada uno). mostrar los números sorteados.

Arreglos: para almacenar y manipular datos, como las cartas en un mazo o los símbolos en una tragaperras.

vectores: Para listas dinámicas como cartas en mano (Blackjack), selección de números (Keno), o historial de resultados.


Librerías utilizadas:

`<iostream>`: Para entrada/salida estándar (cout, cin).

`<cstdlib>`: Para funciones como rand() y srand().

`<ctime>`: Para time() usado en generación de números aleatorios.

`<windows.h>`: Para funciones específicas de Windows (colores en consola).

`<vector>`: Para usar la estructura vector (listas dinámicas).

`<climits>`: Para constantes como INT_MIN, INT_MAX.

`<random>`: Para generación de números aleatorios más avanzada.

`<string>`: Para manejo de strings.

`<limits>`: Para numeric_limits.

`<cfloat>`: Para FLT_MAX, FLT_MIN.

`<algorithm>`: Para funciones como min(), max().


Funciones adicionales implementadas:

•	setColor(int): Cambia el color del texto en consola.

•	simularCargando(string): Simula un proceso de carga visual (espera con puntos).

•	validarEntero(min, max): Pide y valida un número entero dentro de un rango.

•	validarFlotante(min, max): Igual que el anterior, pero con números flotantes.

•	validarNombre(string): Asegura que el nombre ingresado no esté vacío.

•	validarEdad(): Verifica si el usuario es mayor de edad.

•	menuPrincipal(): Muestra el menú principal del casino.

•	mostrarCartas(vector<int>): Muestra las cartas actuales del jugador.

•	sumaCartas(vector<int>): Devuelve la suma de cartas del jugador.

•	generarSimbolos() / verificarCombinacion(): Para tragamonedas.

•	generarNumerosKeno() / compararNumerosKeno() / calcularGananciaKeno(): Para el juego de Keno.


# 🎨 Elementos visuales (interfaz de consola)

Gráficos en ASCII y UTF-8: Se implementaron funciones como showWin(), showLoss() y showJackpot() que muestran animaciones en arte ASCII para representar de manera visual si el jugador ganó, perdió o consiguió un premio especial.

Uso de colores en consola: Gracias a la función setColor() (basada en windows.h), se logra una diferenciación visual entre mensajes de error, información, éxito y menús.

Codificación UTF-8 (SetConsoleOutputCP(CP_UTF8)): Permite mostrar correctamente caracteres especiales como emojis


Validaciones adicionales:

•	Restricción por edad (<18).

•	Saldo mínimo obligatorio para entrar.

•	Validación de todas las apuestas (no pueden exceder el saldo).

•	Control de entradas erróneas (caracteres no numéricos, vacíos, fuera de rango).


# 🧩 Estructura general del juego

El juego comienza solicitando información básica del usuario o usuarios, como nombre, edad y saldo inicial. Se valida que todos los jugadores sean mayores de edad (18+) y que posean un saldo positivo para ingresar al casino. Esta verificación se realiza mediante funciones que controlan los datos ingresados y previenen errores o comportamientos no deseados, aplicando ciclos do-while y estructuras condicionales.

El núcleo del sistema está compuesto por funciones separadas para cada parte lógica del juego. Esto permite una organización clara y escalable, respetando principios de programación estructurada. Además, se utilizan switch-case para navegación de menús, vectores y arreglos para manejar datos internos (como cartas o combinaciones) y funciones auxiliares para validación y presentación visual.


# 🎰 Descripción de los modos de juego

![image](https://github.com/user-attachments/assets/a8030d91-490c-434b-84df-c8de1b70fe64)


🎯 1. Ruleta 

En este modo, el jugador puede apostar de tres maneras distintas: 

Color rojo o negro: en el cual la paga se duplica

rango de números (bajo: 1-12, medio: 13-24, alto: 25-36): en este caso la paga se triplica

Apostar a un número específico entre 0 y 36:  Seleccionar un solo numero, en este modo la apuesta se multiplica por 36.

El sistema utiliza la función rand() para simular el giro de la ruleta y generar un número aleatorio. La función isRed() permite determinar si el número resultante pertenece al conjunto de números rojos, definido previamente mediante un arreglo


🃏 2. Blackjack

El jugador recibe dos cartas con valores aleatorios del 1 al 11. Puede optar por pedir más cartas (hit) o plantarse (stand). El objetivo es acercarse lo más posible a 21 sin pasarse. Si el jugador se pasa, pierde automáticamente.

En multijugador, todos compiten bajo la misma lógica, y el que más se acerque a 21 sin pasarse es el ganador.

Se utilizan vectores para almacenar las cartas y se hace uso de funciones para sumar valores, mostrar el juego y determinar el ganador de la ronda.


🎰 3. Tragamonedas

Se genera una matriz 3x3 con símbolos aleatorios seleccionados de un arreglo. El jugador gana si consigue tres símbolos iguales en una fila

En ciertos casos, se activa un “jackpot” si todos los símbolos son idénticos, lo que multiplica la ganancia significativamente.

Aquí se hace uso de estructuras de bucle para recorrer la matriz, funciones de validación y detección de coincidencias.


🔢 4. Keno

El jugador selecciona 10 números del 1 al 80. El sistema genera aleatoriamente una lista de números ganadores. Luego, se compara cuántos aciertos tuvo el jugador, y en base a esa cantidad, se devuelve un porcentaje de ganancia sobre la apuesta.

Se utiliza la función rand() para la generación aleatoria y vectores para manejar los números seleccionados y los ganadores.

También se hace uso de bucles anidados para comparar ambos vectores y determinar la cantidad de aciertos.


 # Aplicación de los temas vistos
 
**if – else: **
Se utiliza para tomar decisiones en el flujo del programa.

![image](https://github.com/user-attachments/assets/3b68b725-4894-45c8-92b7-7d8caef4e208)


**switch – case:**
 Sirve para gestionar menús y opciones múltiples de forma estructurada.
 
![image](https://github.com/user-attachments/assets/4eb8ac60-5097-41f5-9e49-fbfa64c915c8)


**For:**
 Se usa para recorrer arreglos y vectores.

![image](https://github.com/user-attachments/assets/3e0ef574-62f6-421b-b45e-9910a67bf896)


**while y do-while:**
 Se aplican en validaciones y repeticiones hasta que se cumpla una condición válida.

![image](https://github.com/user-attachments/assets/f47aefe4-d942-4334-84f1-8702d6661e75)

 
**Funciones:**
 El código está dividido en funciones para organizar mejor el flujo.

![image](https://github.com/user-attachments/assets/c2c20f3c-823d-4306-be0d-e761a98cd079)

 
**Estructuras:**
 Sirven para agrupar datos relacionados de un jugador.
 
![image](https://github.com/user-attachments/assets/2c85700d-6c6b-42f1-8756-27dae853458f)


**Matrices:**
 Se utilizan para almacenar datos en forma de tabla, es decir, en filas y columnas.
 
![image](https://github.com/user-attachments/assets/ff83a17a-2f7d-4fb0-afce-024b50cfc6bb)


# Consideraciones técnicas del Desarrollo

**Modularización del código:** 
Todo el proyecto se dividió en funciones específicas para cada tarea: validar datos, ejecutar cada juego, mostrar menús, aplicar colores, calcular ganancias, etc

**Validación de entradas:** 
Para evitar errores o que el programa se crashee, se implementaron funciones como validarEntero() y validarFlotante(), que aseguran que el usuario ingrese datos numéricos dentro de un rango permitido. También se verifica la edad del jugador y que el saldo y las apuestas sean válidas.

**Uso de estructuras para jugadores:** 
Se definió una estructura Jugador para almacenar nombre, edad y saldo. Esto permite manejar múltiples usuarios de forma ordenada y asociar sus datos en una sola entidad.

**Separación por modos de juego:**
Cada juego (ruleta, blackjack, tragamonedas, keno) tiene su propia función que encapsula toda su lógica.

**Uso de rand() con srand(time(0)):**
Para asegurar que los resultados de cada juego sean realmente aleatorios.

**Mejora visual con setColor() y animaciones:**
Se empleó windows.h para cambiar el color del texto en consola y se implementaron funciones como simularCargando() para dar una sensación de espera o animación al usuario.

**Control de flujo:**
Se usaron estructuras do-while, while e if-else para manejar correctamente los bucles del menú, las validaciones y las decisiones del juego.

# Guia Tecnica:

## Documentos principales:

-**Main.cpp:** Main.cpp

-**src:**: blackJack.h, colors.h, estructuras.h, keno.h, librerias.h, ruleta.h, tragaMonedas.h

## Funciones principales:

-**BlackJack:** 
playSingleBlackJack() – Inicia una partida de blackjack donde juegas contra la máquina.
playMultiplayerBlackJack() – Inicia una partida de blackjack multijugador.
generateCard() – Sistema de generación de cartas.

-**Ruleta:** 
playRoulette() –Inicia el menu para jugar en la ruleta.
betColor() – Apuesta a través de la selección de colores.
betRange() – Apuesta a través de la selección de rangos.
betNumber() –Apuesta a través de la selección de un número en específico.

-**Keno:** 
playKeno() – Menú de selección de modalidad de keno.
playSingleKeno() – Inicia una partida de keno en solitario.
playMultiplayerKeno() – Inicia una partida de keno multijugador.

-**Tragamonedas:** 
playSlots() – Menu de seleccion de dificultad.
easyDifficulty() – Inicia una partida pero solo entre 1 a 5 simbolos posibles
mediumDifficulty() – Inicia una partida pero solo entre 1 a 7 simbolos posibles
hardDifficulty() – Inicia una partida entre 1 a 10 simbolos posibles

-**Utilidades:**
readSafeInt() – Leer valor de un int y lo valida entre un rango
readSafeFloat() – Leer valor de un float y lo valida entre un rango
setColor() – Configuración del color de el texto
clearBuffer() – Limpia el buffer

# Guia de usuario
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

## Equipo

- **Nombre del equipo:** Bet++ (Los ludópatas)

### Integrantes del equipo

1. **Nombre completo:** García Osorio, Eduardo Daniel 
   **Carnet:** 00014325

2. **Nombre completo:** Armando José Iglesias Aguilera  
   **Carnet:** 00107425

3. **Nombre completo:** Alfredo Antonio Guarita Hernandez 
   **Carnet:** 00155425
   
4. **Nombre completo:** Saul Ernesto Giron Vigil  
   **Carnet:** 00033325


