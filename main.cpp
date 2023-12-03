#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#define PI 3.1416


// Player position
float playerX = -18.0f;
float playerY = -12.0f;


float enemyX = 18.3f;
float enemyY = -12.0f;


// Bullet position
float bulletX = 1.0f;
float bulletY = 1.0f;

bool isBulletActive = false;
bool isPlayerMoving = true;

bool isCollide = false;
int score = 0;

void checkCollision(){
    if (bulletX >= enemyX && bulletX <= enemyX + 0.3f){
        std::cout << "Collision detected!" << std::endl;
        isCollide = true;
        if (isCollide){

            score += 1;

            std::cout << "Score: " << score << std::endl;
            isCollide = false;
        }
    }


}


void drawEnemy(){
    glBegin(GL_POLYGON);
    glColor3f(0.f, 0.0f, 1.0f);
    glVertex2f(enemyX + 1.0f,enemyY - 4.0f);
    glVertex2f(enemyX - 1.0f,enemyY - 4.0f);
    glVertex2f(enemyX - 1.0f,enemyY + 1.0f);
    glVertex2f(enemyX + 1.0f, enemyY + 1.0f);
    glEnd();

    glEnd();

}

void drawPlayer() {
    // Code to draw the player (e.g., a rectangle or sprite)
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerX - 1.0f, playerY - 5.0f);
    glVertex2f(playerX + 1.0f, playerY - 5.0f);
    glVertex2f(playerX + 1.0f, playerY + 3.0f);
    glVertex2f(playerX - 1.0f, playerY + 3.0f);
    glEnd();
}

void drawBullet() {
    // Code to draw the bullet in red and slightly larger
    glColor3f(1.0f, 1.0f, 0.0f);  // Red color
    glBegin(GL_QUADS);
    glVertex2f(bulletX - 0.2f, bulletY - 0.2f);
    glVertex2f(bulletX + 0.2f, bulletY - 0.2f);
    glVertex2f(bulletX + 0.2f, bulletY + 0.2f);
    glVertex2f(bulletX - 0.2f, bulletY + 0.2f);
    glEnd();
}




// Draw background view
void background(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.5);

    //background
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-20.0f,20.0f);
    glVertex2f(20.0f,20.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();

    //door 1
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(-18.0f,14.0f);
    glVertex2f(-9.0f,14.0f);
    glVertex2f(-9.0f,-8.0f);
    glVertex2f(-18.0f,-8.0f);
    glEnd();
    //door 1 glass
    glBegin(GL_POLYGON);
    glColor3f(0.f, 0.0f, 1.0f);
    glVertex2f(-12.0f,11.0f);
    glVertex2f(-9.0f,11.0f);
    glVertex2f(-9.0f,5.0f);
    glVertex2f(-12.0f,5.0f);
    glEnd();

    //door 2
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(5.0f,14.0f);
    glVertex2f(16.0f,14.0f);
    glVertex2f(16.0f,-8.0f);
    glVertex2f(5.0f,-8.0f);
    glEnd();
    //door2 glass
    glBegin(GL_POLYGON);
    glColor3f(0.f, 0.0f, 1.0f);
    glVertex2f(13.0f,11.0f);
    glVertex2f(16.0f,11.0f);
    glVertex2f(16.0f,5.0f);
    glVertex2f(13.0f,5.0f);
    glEnd();



     //dustbin trinagle
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-5.0f,0.0f);
    glVertex2f(-3.0f,2.0f);
    glVertex2f(-1.0f,2.0f);
    glVertex2f(1.0f,0.0f);
    glEnd();
    //dustbin big rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-5.0f,0.0f);
    glVertex2f(1.0f,0.0f);
    glVertex2f(1.0f,-8.0f);
    glVertex2f(-5.0f,-8.0f);
    glEnd();

    //dustbin midlle rectangle

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-4.0f,-2.0f);
    glVertex2f(0.0f,-2.0f);
    glVertex2f(0.0f,-4.0f);
    glVertex2f(-4.0f,-4.0f);
    glEnd();


    //floor
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(-20.0f,-10.0f);
    glVertex2f(20.0f,-10.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();


}

// Play gun shoot sound
void gunShotSound(){
    sndPlaySound("gun_shoot_sound.wav", SND_ASYNC);
}


void update(int value) {
    // Update the bullet position if it is active
    if (isBulletActive) {
        bulletX += 0.5f;  // Adjust the speed of the bullet
        // Check if the bullet is out of bounds
//        std::cout <<  "Bullet possition" << std::endl;
//        std::cout <<  bulletX << std::endl;
        if (bulletX > 20.0f) {
            isBulletActive = false;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);  // 60 FPS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    drawEnemy();
    drawPlayer();
    checkCollision();


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
                gunShotSound();
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
