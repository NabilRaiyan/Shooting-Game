#include <iostream>
#include <GL/glut.h>

// Player position
float playerX = -18.0f;
float playerY = -15.0f;

// Bullet position
float bulletX = 1.0f;
float bulletY = 1.0f;
bool isBulletActive = false;
bool isPlayerMoving = true;

void drawPlayer() {
    // Code to draw the player (e.g., a rectangle or sprite)
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerX - 1.0f, playerY - 1.0f);
    glVertex2f(playerX + 1.0f, playerY - 1.0f);
    glVertex2f(playerX + 1.0f, playerY + 1.0f);
    glVertex2f(playerX - 1.0f, playerY + 1.0f);
    glEnd();
}

void drawBullet() {
    // Code to draw the bullet in red and slightly larger
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    glBegin(GL_QUADS);
    glVertex2f(bulletX - 0.1f, bulletY - 0.1f);
    glVertex2f(bulletX + 0.1f, bulletY - 0.1f);
    glVertex2f(bulletX + 0.1f, bulletY + 0.1f);
    glVertex2f(bulletX - 0.1f, bulletY + 0.1f);
    glEnd();
}

void update(int value) {
    // Update the bullet position if it is active
    if (isBulletActive) {
        bulletX += 0.6f;  // Adjust the speed of the bullet
        // Check if the bullet is out of bounds
        if (bulletX > 20.0f) {
            isBulletActive = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);  // 60 FPS
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
            if (playerX < -18){
                isPlayerMoving = false;
            }
            else{
                playerX -= 0.5f;  // Move left
            }
            break;
        case 'd':
            playerX += 0.5f;  // Move right
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
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Course Shooting Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(25, update, 0);  // Timer function for game updates

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);

    glutMainLoop();
    return 0;
}
