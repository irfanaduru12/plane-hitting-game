# ✈️ 2D Airplane Shooter Game (OpenGL)

This project is a 2D shooter game developed using C++ and the **OpenGL (GLUT)** library. The player's objective is to shoot down enemy planes spawning from the right side of the screen within a 30-second time limit to achieve the highest possible score.

*Project / Assignment by:* **Irfan Alper Duru**

## 🌟 Key Features

* **Accuracy-Based Scoring:** The closer your shot lands to the center of the enemy plane (direct hit), the higher the points you earn (ranging from 0 to 5 points per hit).
* **Time Limit:** The game is limited to 30 seconds, and the remaining time is displayed on the screen in real-time.
* **Real-Time UI:** The remaining time, total score, and the points earned from the last hit are instantly updated and shown on the user interface.
* **Game State Control:** The game can be paused at any time or restarted with a single key press once the "Game Over" screen is reached.

## 🎮 Controls

The controls are simple and intuitive:

* **`W` Key:** Moves the cannon/weapon **up**.
* **`S` Key:** Moves the cannon/weapon **down**.
* **`Spacebar`:** Fires a bullet. (Only one active bullet is allowed on the screen at a time).
* **`F1` Key:** Pauses/Resumes the game, or Restarts the game from the "Game Over" screen.

## 🛠️ Technologies & Requirements

* **Language:** C++
* **Graphics API:** OpenGL / GLUT (FreeGLUT)
* **Standard Libraries:** `<cmath>`, `<ctime>`, `<cstdlib>`, `<string>`, `<vector>`, `<algorithm>`

## 🚀 Installation & Compilation (How to Run)

To compile and run this project on your local machine, you need a C++ compiler (GCC, MSVC, etc.) and the **OpenGL/GLUT** libraries installed on your system.

**For Windows (Visual Studio):**
1. Create an empty C++ project.
2. Link the FreeGLUT and OpenGL libraries to your project (Linker settings).
3. Paste the provided code into your `main.cpp` file and build the project.

**For Linux (G++):**
If you are compiling via the terminal using G++, you can use the following command to link the OpenGL libraries:
```bash
g++ main.cpp -o AirplaneGame -lGL -lGLU -lglut
./AirplaneGame
