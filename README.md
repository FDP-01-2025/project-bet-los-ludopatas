[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - Bet++
Casino bet++
![image](https://github.com/user-attachments/assets/71b3467a-0bf9-40a0-b14e-1ef08b32d1f1)
El juego Bet++ (Los Ludópatas) se basa en la temática de un casino virtual moderno, diseñado para ofrecer una experiencia de entretenimiento digital que simula dinámicas reales de un casino físico.
La ambientación se enfoca en brindar al usuario una variedad de modos de juego clásicos, como la ruleta, blackjack, tragamonedas y keno, cada modo de juego está pensado para ofrecer una dinámica distinta y mantener la atención del usuario.
Esta diversidad permite una experiencia más rica, entretenida y cercana a un casino real, dentro de un entorno digital simple y accesible.

🧠 Mecánica Principal del Juego
If-else: Determina si hay combinaciones ganadoras también maneja la lógica del juego y las decisiones del jugador.
While: Mantiene el juego en ejecución hasta que el jugador se quede sin créditos o desea salir. 
Switch-case: maneja el menú de opciones (jugar, ver créditos, salir).
For: Tiene diverso papel en cada modo de juego en blackjack es encargado de repartir las cartas. En tragamonedas generar 3 símbolos aleatorios en los rodillos. En keno se utiliza para que el jugador elija 5 números (validando cada uno). mostrar los números sorteados.
Arreglos: para almacenar y manipular datos, como las cartas en un mazo o los símbolos en una tragaperras.
vectores: Para listas dinámicas como cartas en mano (Blackjack), selección de números (Keno), o historial de resultados.

Librerías utilizadas:
- `<iostream>`: Entrada y salida de datos.
- 
- `<cstdlib>`: Generación de números aleatorios con `rand()`.
- 
- `<ctime>`: Inicialización del generador aleatorio (semilla).
- 
- `<vector>`: Listas dinámicas de datos.
- 
- `<algorithm>`: Búsqueda y validación de elementos repetidos.
- 
- `<windows.h>`: Para cambiar color del texto en consola (`SetConsoleTextAttribute`).
- 
- `<thread>` y `<chrono>`: Para simular tiempos de espera y animaciones (como carga y "giro" de ruleta o tragamonedas).
- 
- `<random>`: Generación avanzada de números aleatorios.
- 
- `<string>`: Permite trabajar con cadenas de texto.
- 
- `<limits>`: Proporciona información sobre los límites numéricos de los tipos de datos primitivos (como `int`, `float`, etc.).
- 
- `<cfloat>`: Contiene constantes que definen los límites y precisión de los tipos de datos de punto flotante (`float`, `double`, `long double`).


Funciones adicionales implementadas:

## Equipo

- **Nombre del equipo:** Bet++ (Los ludópatas)

### Integrantes del equipo

1. **Nombre completo:** [Nombre del estudiante 1]  
   **Carnet:** [Carnet del estudiante 1]

2. **Nombre completo:** [Nombre del estudiante 2]  
   **Carnet:** [Carnet del estudiante 2]

3. **Nombre completo:** [Nombre del estudiante 3]  
   **Carnet:** [Carnet del estudiante 3]
   
4. **Nombre completo:** Saul Ernesto Giron Vigil  
   **Carnet:** 00033325


## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [URL del repositorio]
