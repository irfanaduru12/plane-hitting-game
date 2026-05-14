/* Irfan Alper Duru
Additional Features:
- Scoring system based on hit accuracy (0-5 pts)
- Last hit score is displayed on the User Interface
*/

#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

struct Bullet {
    float x, y;
    bool active;
};

struct Target {
    float x, y;
    bool active;
};

std::vector<Target> targets;
Bullet bullet = { 0, 0, false };
int score = 0;
int lastScore = 0;
float weaponY = 0.0f;
int remainingTime = 30;
bool isPaused = false;
bool gameOver = false;
int spawnTimer = 0;
void timer(int);

void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void resetGame() {
    score = 0;
    lastScore = 0;
    remainingTime = 30;
    gameOver = false;
    targets.clear();
    bullet.active = false;
    spawnTimer = 0;
    glutTimerFunc(1000, [](int) {
        if (!isPaused && !gameOver) {
            remainingTime--;
            if (remainingTime <= 0) {
                gameOver = true;
            }
            else {
                glutTimerFunc(1000, timer, 0);
            }
            glutPostRedisplay();
        }
        else if (!gameOver) {
            glutTimerFunc(1000, timer, 0);
        }
        }, 0);
}

// Drawing the cannon
void drawWeapon()
{
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-0.97f, weaponY - 0.05f);
    glVertex2f(-0.85f, weaponY - 0.05f);
    glVertex2f(-0.85f, weaponY + 0.05f);
    glVertex2f(-0.97f, weaponY + 0.05f);

    glColor3f(0.26f, 0.15f, 0.07f);
    glVertex2f(-1.0f, weaponY - 0.05f);
    glVertex2f(-0.97f, weaponY - 0.05f);
    glVertex2f(-0.97f, weaponY + 0.05f);
    glVertex2f(-1.0f, weaponY + 0.05f);
    glEnd();
}

//Drawing the bullets
void drawBullet() {
    if (bullet.active) {
        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(bullet.x - 0.01f, bullet.y - 0.01f);
        glVertex2f(bullet.x + 0.01f, bullet.y - 0.01f);
        glVertex2f(bullet.x + 0.01f, bullet.y + 0.01f);
        glVertex2f(bullet.x - 0.01f, bullet.y + 0.01f);
        glEnd();
    }
}

void drawTargets() {
    for (auto& t : targets) {
        if (!t.active) continue;

        glPushMatrix();
        glTranslatef(t.x, t.y, 0.0f);

        // Body 
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(-0.04f, -0.015f);
        glVertex2f(0.04f, -0.015f);
        glVertex2f(0.04f, 0.015f);
        glVertex2f(-0.04f, 0.015f);
        glEnd();

        // Wings 
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.01f);
        glVertex2f(-0.03f, 0.01f);
        glVertex2f(0.02f, 0.035f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -0.01f);
        glVertex2f(-0.03f, -0.01f);
        glVertex2f(0.02f, -0.035f);
        glEnd();

        //Nose
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.04f, 0.015f);
        glVertex2f(-0.04f, -0.015f);
        glVertex2f(-0.06f, 0.0f);
        glEnd();

        // Tail
        glBegin(GL_TRIANGLES);
        glVertex2f(0.04f, 0.015f);
        glVertex2f(0.024f, 0.015f);
        glVertex2f(0.032f, 0.035f);
        glEnd();

        glPopMatrix();
    }
}


void spawnTarget() {
    if (targets.size() < 5) {
        Target t = { 1.0f, (rand() % 180 - 90) / 100.0f, true };
        targets.push_back(t);
    }
}

void checkCollisions() {
    if (!bullet.active) return;
    for (auto& t : targets) {
        if (t.active && fabs(bullet.x - t.x) < 0.04f && fabs(bullet.y - t.y) < 0.04f) {
            t.active = false;
            bullet.active = false;
            float dist = std::sqrt((bullet.x - t.x) * (bullet.x - t.x) + (bullet.y - t.y) * (bullet.y - t.y));
            lastScore = std::max(0, 5 - int(dist * 100));
            score += lastScore;
            return;
        }
    }
}

void update(int) {
    if (!isPaused && !gameOver) {
        for (auto& t : targets)
            if (t.active) t.x -= 0.01f;

        targets.erase(std::remove_if(targets.begin(), targets.end(), [](Target& t) {
            return t.x < -1.0f || !t.active;
            }), targets.end());

        if (bullet.active) {
            bullet.x += 0.03f;
            if (bullet.x > 1.0f) bullet.active = false;
        }

        checkCollisions();

        spawnTimer++;
        if (spawnTimer >= 50) {
            spawnTarget();
            spawnTimer = 0;
        }

        glutPostRedisplay();
    }

    glutTimerFunc(16, update, 0); // ~60fps
}

void drawUI() {
    glColor3f(1, 1, 1);
    drawText(0.6f, 0.9f, "Remaining Time: " + std::to_string(remainingTime));
    drawText(0.6f, 0.8f, "Score: " + std::to_string(score));
    drawText(0.6f, 0.7f, "Last Hit: " + std::to_string(lastScore));

    drawText(-0.6f, -0.4f, "W/S: Move");
    drawText(-0.2f, -0.4f, "Space: Fire");
    drawText(0.2f, -0.4f, "F1: Pause/Restart");

    if (gameOver)
    {
        glColor3f(1, 0, 0);
        drawText(-0.3f, 0.2f, "GAME OVER - Press F1 to Restart");
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Background
    glColor3f(0.1f, 0.1f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    drawWeapon();
    drawBullet();
    drawTargets();
    drawUI();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
    case 'w':
    case 'W':
        if (weaponY < 0.9f) weaponY += 0.05f;
        break;
    case 's':
    case 'S':
        if (weaponY > -0.9f) weaponY -= 0.05f;
        break;
    case 32: // Spacebar
        if (!bullet.active) {
            bullet = { -0.9f, weaponY, true };
        }
        break;
    }
}

void special(int key, int, int) {
    if (key == GLUT_KEY_F1) {
        if (gameOver) {
            resetGame();
        }
        isPaused = !isPaused;
    }
}

void timer(int) {
    if (!isPaused && !gameOver) {
        remainingTime--;
        if (remainingTime <= 0) {
            gameOver = true;
        }
        else {
            glutTimerFunc(1000, timer, 0);
        }
        glutPostRedisplay();
    }
    else if (!gameOver) {
        glutTimerFunc(1000, timer, 0);
    }
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Irfan Alper Duru Homework 2");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0, update, 0);
    glutTimerFunc(1000, timer, 0);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();
    return 0;
}
