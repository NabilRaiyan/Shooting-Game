#include <iostream>
#include <GL/glut.h>

// Player position
float playerX = 0.0f;
float playerY = 0.0f;

// Bullet position
float bulletX = 0.0f;
float bulletY = 0.0f;
bool isBulletActive = false;

void drawPlayer() {
    // Code to draw the player (e.g., a rectangle or sprite)
    glBegin(GL_QUADS);
    glVertex2f(playerX - 0.1f, playerY - 0.1f);
    glVertex2f(playerX + 0.1f, playerY - 0.1f);
    glVertex2f(playerX + 0.1f, playerY + 0.1f);
    glVertex2f(playerX - 0.1f, playerY + 0.1f);
    glEnd();
}

void drawBullet() {
    // Code to draw the bullet (e.g., a small rectangle or point)
    glBegin(GL_POINTS);
    glVertex2f(bulletX, bulletY);
    glEnd();
}

void update(int value) {
    // Update the bullet position if it is active
    if (isBulletActive) {
        bulletX += 0.1f;  // Adjust the speed of the bullet
        // Check if the bullet is out of bounds
        if (bulletX > 1.0f) {
            isBulletActive = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // 60 FPS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlayer();

    if (isBulletActive) {
        drawBullet();
    }

    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            playerX -= 0.1f;  // Move left
            break;
        case 'd':
            playerX += 0.1f;  // Move right
            break;
        case 's':
            if (!isBulletActive) {
                bulletX = playerX;
                bulletY = playerY;
                isBulletActive = true;
            }
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
     glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Shooting Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(25, update, 0);  // Timer function for game updates

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}
