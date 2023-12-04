#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#define PI 3.1416
#include <vector>


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


void renderBitmapString(float x, float y, float z, void *font, char *string)
{
     glColor3f(1.0,1.0,1.0);
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

// Checking collision of bullet with enemy
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


//void drawEnemy(){
//    glBegin(GL_POLYGON);
//    glColor3f(0.f, 0.0f, 1.0f);
//    glVertex2f(enemyX + 1.0f,enemyY - 4.0f);
//    glVertex2f(enemyX - 1.0f,enemyY - 4.0f);
//    glVertex2f(enemyX - 1.0f,enemyY + 1.0f);
//    glVertex2f(enemyX + 1.0f, enemyY + 1.0f);
//    glEnd();
//
//    glEnd();
//
//}


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



// Draw background view
void background(){
glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.5);

    //background
    glBegin(GL_POLYGON);
    glColor3ub(184, 145, 150);
    glVertex2f(-20.0f,20.0f);
    glVertex2f(20.0f,20.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();

    //door 1
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(-15.0f,14.0f);
    glVertex2f(-9.0f,14.0f);
    glVertex2f(-9.0f,-10.0f);
    glVertex2f(-15.0f,-10.0f);
    glEnd();

    //door 1 glass
    glBegin(GL_POLYGON);
    glColor3ub(205, 209, 206);
    glVertex2f(-11.0f,11.0f);
    glVertex2f(-9.0f,11.0f);
    glVertex2f(-9.0f,5.0f);
    glVertex2f(-11.0f,5.0f);
    glEnd();

    //door 2
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(10.0f,14.0f);
    glVertex2f(16.0f,14.0f);
    glVertex2f(16.0f,-10.0f);
    glVertex2f(10.0f,-10.0f);
    glEnd();
    //door2 glass
     glBegin(GL_POLYGON);
    glColor3ub(205, 209, 206);
    glVertex2f(14.0f,11.0f);
    glVertex2f(16.0f,11.0f);
    glVertex2f(16.0f,5.0f);
    glVertex2f(14.0f,5.0f);
    glEnd();


    //fingerprint1
    glBegin(GL_POLYGON);
    glColor3ub(37, 48, 47);
    glVertex2f(-8.0f,5.0f);
    glVertex2f(-7.0f,5.0f);
    glVertex2f(-7.0f,2.0f);
    glVertex2f(-8.0f,2.0f);
    glEnd();

       //fingerprint1  display
    glBegin(GL_POLYGON);
    glColor3ub(205, 209, 206);
    glVertex2f(-7.75f,4.50f);
    glVertex2f(-7.25f,4.50f);
    glVertex2f(-7.25f,4.25f);
    glVertex2f(-7.75f,4.25f);
    glEnd();

    //finger print1 position


    glBegin(GL_POLYGON);
    glColor3ub(9, 230, 212);
    glVertex2f(-7.62f,3.00f);
    glVertex2f(-7.33f,3.00f);
    glVertex2f(-7.33f,2.50f);
    glVertex2f(-7.62f,2.50f);
    glEnd();

      //fingerprint 2
    glBegin(GL_POLYGON);
    glColor3ub(37, 48, 47);
    glVertex2f(18.0f,5.0f);
    glVertex2f(19.0f,5.0f);
    glVertex2f(19.0f,2.0f);
    glVertex2f(18.0f,2.0f);
    glEnd();
    //finer print 2 display
    glBegin(GL_POLYGON);
    glColor3ub(205, 209, 206);
    glVertex2f(18.25f,4.50f);
    glVertex2f(18.75f,4.50f);
    glVertex2f(18.75f,4.25f);
    glVertex2f(18.25f,4.25f);
    glEnd();
    //finger print2 position


    glBegin(GL_POLYGON);
    glColor3ub(9, 230, 212);
    glVertex2f(18.33f,3.00f);
    glVertex2f(18.62f,3.00f);
    glVertex2f(18.62f,2.50f);
    glVertex2f(18.33f,2.50f);
    glEnd();
    //noticeboard
            glBegin(GL_POLYGON);
     glColor3ub(4, 89, 81);
    glVertex2f(-3.0f,12.0f);
    glVertex2f(5.0f,12.0f);
    glVertex2f(5.0f,4.0f);
    glVertex2f(-3.0f,4.0f);
    glEnd();

     //dustbin trinagle
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-3.0f,0.0f);
    glVertex2f(-2.0f,1.0f);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(0.0f,0.0f);
    glEnd();
 //dustbin big rectangle
        glBegin(GL_POLYGON);
     glColor3ub(33, 156, 61);
    glVertex2f(-3.0f,0.0f);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.0f,-10.0f);
    glVertex2f(-3.0f,-10.0f);
    glEnd();

//dustbin midlle rectangle

      glBegin(GL_POLYGON);
    glColor3ub(256, 256, 256);
    glVertex2f(-2.0f,-2.0f);
    glVertex2f(-1.0f,-2.0f);
    glVertex2f(-1.0f,-3.0f);
    glVertex2f(-2.0f,-3.0f);
    glEnd();



    //floor
    glBegin(GL_POLYGON);
    glColor3ub(47, 62, 66);
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
    glutTimerFunc(5, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    drawPlayer();
    checkCollision();
//    drawEnemy();


    renderBitmapString(-1.5f, 8.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Notice Board");
    renderBitmapString(-1.5f, 6.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Cancel Final Term");

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
    glutInitWindowSize(1000, 550);
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
