//TODO-1:--->> Already Created a levelUpBackground() which will appear in between each level whenever we jump from one to another
//TODO-2:--->> Create a cover page and menu for game and also use sound on off system

#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#define PI 3.1416
#include <string>
using namespace std;


// Player position
float playerX = -18.0f;
float playerY = -11.0f;


// bullet position
float bulletX = 1.0f;
float bulletY = 1.0f;

// player, enemy, bullet active flag
bool isBulletActive = false;
bool isPlayerMoving = true;
bool isEnemyActive = false;

// score, level, enemy count, player health count
int score = 0;
int level = 1;
bool levelIncreased = false;
int enemyCount = 0;
int playerHealth = 3;

// enemy movement speed
float enemyMovementSpeed = 0.2f;

// Game start
bool isGameStarted = false;
bool isSoundOn = true;

// Course, semester up text
std::string course = "";
std::string nextSemester = "2nd Sem";




const int numEnemies = 1;  // Adjust the number of enemies as needed
std::vector<float> enemyX(numEnemies, 0.0f);
std::vector<float> enemyY(numEnemies, 0.0f);

void renderBitmapString(float x, float y, float z, void* font, char* string) {
    glColor3ub(255, 255, 255);
    char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}



// Function to display the game menu
void gameMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3ub(0, 181, 255);
    glVertex2f(-20.0f,20.0f);
    glVertex2f(20.0f,20.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);

     // Menu rectangle
    glBegin(GL_POLYGON);
    glColor3ub(45, 212, 204);
    glVertex2f(-6.0f,8.0f);
    glVertex2f(6.0f,8.0f);
    glVertex2f(6.0f,-8.0f);
    glVertex2f(-6.0f,-8.0f);
    glEnd();

    // Draw menu options

    glRasterPos2f(-8.0f, 10.0f);
    renderBitmapString(-8.0f, 10.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "PRESS THE CORRESPONDING KEYS (1 or 2 or 3 or 4 or 5)");

    glRasterPos2f(-3.0f, 5.0f);
    renderBitmapString(-3.0f, 5.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "1. NEW GAME");

    glRasterPos2f(-3.0f, 3.0f);
    renderBitmapString(-3.0f, 2.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "2. SOUND (On/Off)");

    glRasterPos2f(-3.0f, 1.0f);
    renderBitmapString(-3.0f, -1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "3. HIGH SCORE");

    glRasterPos2f(-3.0f, -1.0f);
    renderBitmapString(-3.0f, -4.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "4. CONTROLS");

    glRasterPos2f(-3.0f, 3.0f);
    renderBitmapString(-3.0f, -7.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "5. EXIT GAME");

    glutSwapBuffers();
}

// All Sounds

// Gun shoot sound by player
void gunShotSound() {
    sndPlaySound("gun_shoot_sound.wav", SND_ASYNC);
}

// enemy hit by bullet sound
void enemyHitByBulletSound(){
    sndPlaySound("deathSound.wav", SND_ASYNC);
}

// player hit by enemy sound
void playerHitByEnemySound(){
    sndPlaySound("playerHitByBulletSound.wav", SND_ASYNC);
}

// player death sound
void playerDeathSound(){
    sndPlaySound("playerDeathSound.wav", SND_ASYNC);
}

//// background for level up in between levels
//void levelUpBackground(){
//
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // screen color
//    glBegin(GL_POLYGON);
//    glColor3ub(0, 0, 0);
//    glVertex2f(-20.0f,20.0f);
//    glVertex2f(20.0f,20.0f);
//    glVertex2f(20.0f,-20.0f);
//    glVertex2f(-20.0f,-20.0f);
//    glEnd();
//
//
//}



// Check collision of bullet with enemy
void checkCollision() {
    for (int i = 0; i < numEnemies; ++i) {
        if (isBulletActive && bulletX >= enemyX[i] - 1.0f && bulletX <= enemyX[i] + 1.0f && bulletY >= enemyY[i] - 3.0f && bulletY <= enemyY[i] + 1.0f) {
            std::cout << "Collision detected!" << std::endl;
            if (isSoundOn == true){
                enemyHitByBulletSound();
            }
            else{
                isSoundOn = false;
            }

            score += 1;
            std::cout << "Score: " << score << std::endl;
            isBulletActive = false;

             // Regenerate enemy at initial position
            enemyX[i] = 20.0f;
            enemyY[i] = -30.0f + static_cast<float>(rand() % 300) / 100.0f;  // Randomize Y position
        }
    }

    // Increasing level from 1 to 2
     if (score > 10){
        //Sleep(1000);
//        // Reset player position
//        playerX = -18.0f;
//        playerY = -12.0f;
        level = 2;
        nextSemester = "3rd Sem";
        enemyMovementSpeed = 0.3;

    }

    if (score > 20){
        //Sleep(1000);
//      // Reset player position
//      playerX = -18.0f;
//      playerY = -12.0f;
        level = 3;
        nextSemester = "4th Sem";
        enemyMovementSpeed = 0.4;
    }
}

// Check collision of enemy with player
void checkPlayerCollision() {
    if (isGameStarted == true){
        for (int i = 0; i < numEnemies; ++i) {
            if (playerX - 1.0f <= enemyX[i] + 1.0f &&
                playerX + 1.0f >= enemyX[i] - 1.0f &&
                playerY - 5.0f <= enemyY[i] + 1.0f &&
                playerY + 3.0f >= enemyY[i] - 4.0f) {
                std::cout << "Player collided with an enemy!" << std::endl;
                if (isSoundOn == true)
                {
                     playerHitByEnemySound();
                }
                else{
                    isSoundOn = false;
                }

                playerHealth--;  // Reduce player health
                std::cout << "Player Health: " << playerHealth << std::endl;

                // Reset player position
                playerX = -18.0f;
                playerY = -11.0f;

                // Reset enemies
                for (int j = 0; j < numEnemies; ++j) {
                    enemyX[j] = 20.0f;
                    enemyY[j] = -30.0f + static_cast<float>(rand() % 300) / 100.0f;  // Randomize Y position
                }

                // Check if player is out of health
                if (playerHealth <= 0) {
                        if (isSoundOn == true){
                            playerDeathSound();
                        }
                        else{
                            isSoundOn = false;
                        }

                    Sleep(1000);
                    std::cout << "Game over! Player is out of health." << std::endl;
                    //exit(0);  // Exit the game or handle game over state as needed
                }
            }
        }
    }
    else{
        gameMenu();
    }
}

// Level up sign
void levelUpSign(){
    glBegin(GL_POLYGON);
    glColor3ub(7, 48, 47);
    glVertex2f(17.0f,1.0f);
    glVertex2f(19.3f,1.0f);
    glVertex2f(19.3f,-1.0f);
    glVertex2f(17.0f,-1.0f);
    glEnd();

    glColor3ub(255, 255, 255);  // White color for text
    glRasterPos2f(17.2f, -0.3f);
    for (char l : nextSemester){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, l);
     }
}


// drawing notice board
void drawNoticeBoard(float r, float g, float b){
      // noticeboard border
    glBegin(GL_POLYGON);
    glColor3ub(136, 83, 63);
    glVertex2f(-3.3f,14.5f);
    glVertex2f(5.3f,14.5f);
    glVertex2f(5.3f,3.5f);
    glVertex2f(-3.3f,3.5f);
    glEnd();

    //noticeboard
    glBegin(GL_POLYGON);
    glColor3ub(r, g, b);
    glVertex2f(-3.0f,14.0f);
    glVertex2f(5.0f,14.0f);
    glVertex2f(5.0f,4.0f);
    glVertex2f(-3.0f,4.0f);
    glEnd();

}

// Draw Fingerprint 1

void drawFingerPrint1(){
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
}

// Draw Fingerprint 2
void drawFingerPrint2(){
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
}

// drawFirebox
void drawFireBox(){
    //fire box
    glBegin(GL_POLYGON);
    glColor3ub(219, 15, 36);
    glVertex2f(9.0f,6.00f);
    glVertex2f(12.00f,6.00f);
    glVertex2f(12.00f,3.00f);
    glVertex2f(9.00f,3.00f);
    glEnd();

    //fireboxsmall
    glBegin(GL_POLYGON);
    glColor3ub(47, 62, 66);
    glVertex2f(10.0f,5.00f);
    glVertex2f(11.00f,5.00f);
    glVertex2f(11.00f,4.00f);
    glVertex2f(10.00f,4.00f);
    glEnd();
}

// Creating dustbin

void drawDustbin(){
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
}

// drawing wall
void drawWall(float r, float g, float b){
    // Wall color
    glBegin(GL_POLYGON);
    glColor3ub(r, g, b);
    glVertex2f(-20.0f,20.0f);
    glVertex2f(20.0f,20.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();


    // Wall lower part
    glBegin(GL_POLYGON);
    glColor3ub(149, 112, 100);
    glVertex2f(-20.0f, -8.5f);
    glVertex2f(20.0f,-8.5f);
    glVertex2f(20.0f,-10.0f);
    glVertex2f(-20.0f,-10.0f);
    glEnd();

}

// drawing floor
void drawFloor(){
    //floor upper part
    glBegin(GL_POLYGON);
    glColor3ub(108, 120, 98);
    glVertex2f(-20.0f,-10.0f);
    glVertex2f(20.0f,-10.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();

    //floor lower part
    glBegin(GL_POLYGON);
    glColor3ub(50, 61, 47);
    glVertex2f(-20.0f,-17.0f);
    glVertex2f(20.0f,-17.0f);
    glVertex2f(20.0f,-20.0f);
    glVertex2f(-20.0f,-20.0f);
    glEnd();
}

// drawing left door
void drawLeftDoor(){
    //door 1
    glBegin(GL_POLYGON);
    glColor3ub(149, 112, 100);
    glVertex2f(-15.0f,14.0f);
    glVertex2f(-9.0f,14.0f);
    glVertex2f(-9.0f,-10.0f);
    glVertex2f(-15.0f,-10.0f);
    glEnd();

    // door 1 side bar
    glBegin(GL_POLYGON);
    glColor3ub(136, 83, 63);
    glVertex2f(-14.5f, 13.0f);
    glVertex2f(-9.5f,13.0f);
    glVertex2f(-9.5f,-8.5f);
    glVertex2f(-14.5f,-8.5f);
    glEnd();

    //door 1 glass upper glass
    glBegin(GL_POLYGON);
    glColor3ub(108, 165, 191);
    glVertex2f(-13.5f, 10.0f);
    glVertex2f(-10.5f,10.0f);
    glVertex2f(-10.5f,2.0f);
    glVertex2f(-13.5f,2.0f);
    glEnd();

    //door 1 glass lower glass
    glBegin(GL_POLYGON);
    glColor3ub(108, 165, 191);
    glVertex2f(-13.5f, -7.0f);
    glVertex2f(-10.5f,-7.0f);
    glVertex2f(-10.5f,-3.5f);
    glVertex2f(-13.5f,-3.5f);
    glEnd();

    // door handle
    glBegin(GL_POLYGON);
    glColor3ub(189, 178, 187);
    glVertex2f(-11.0f, 1.0f);
    glVertex2f(-10.5f,1.0f);
    glVertex2f(-10.5f,-2.0f);
    glVertex2f(-11.0f,-2.0f);
    glEnd();

}

// Drawing right door
void drawRightDoor(float r, float g, float b){
    //door 2
    glBegin(GL_POLYGON);
    glColor3ub(r, g, b);
    glVertex2f(10.0f,14.0f);
    glVertex2f(16.0f,14.0f);
    glVertex2f(16.0f,-10.0f);
    glVertex2f(10.0f,-10.0f);
    glEnd();

    // door 2 side bar
    glBegin(GL_POLYGON);
    glColor3ub(136, 83, 63);
    glVertex2f(10.5f, 13.0f);
    glVertex2f(15.5f,13.0f);
    glVertex2f(15.5f,-8.5f);
    glVertex2f(10.5f,-8.5f);
    glEnd();

    //door 2 glass upper glass
    glBegin(GL_POLYGON);
    glColor3ub(108, 165, 191);
    glVertex2f(14.5f, 10.0f);
    glVertex2f(11.5f,10.0f);
    glVertex2f(11.5f,2.0f);
    glVertex2f(14.5f,2.0f);
    glEnd();

    //door 2 glass lower glass
    glBegin(GL_POLYGON);
    glColor3ub(108, 165, 191);
    glVertex2f(14.5f, -7.0f);
    glVertex2f(11.5f,-7.0f);
    glVertex2f(11.5f,-3.5f);
    glVertex2f(14.5f,-3.5f);
    glEnd();

    // door 2 handle
    glBegin(GL_POLYGON);
    glColor3ub(189, 178, 187);
    glVertex2f(14.5f, 1.0f);
    glVertex2f(14.0f,1.0f);
    glVertex2f(14.0f,-2.0f);
    glVertex2f(14.5f,-2.0f);
    glEnd();

}
// Draw bench function
void drawBench(){
    //bench big back
    glBegin(GL_POLYGON);
    glColor3ub(96, 133, 158);
    glVertex2f(6.0f,-7.0f);
    glVertex2f(6.0f,-2.0f);
    glVertex2f(16.0f,-2.0f);
    glVertex2f(16.0f,-7.0f);

    glEnd();
    //bench middle rect
    glBegin(GL_POLYGON);
    glColor3ub(60, 113, 166);
    glVertex2f(5.50f,-8.0f);
    glVertex2f(5.50f,-7.0f);
    glVertex2f(16.50f,-7.0f);
    glVertex2f(16.50f,-8.0f);
    glEnd();


    //1st leg
    glBegin(GL_POLYGON);
    glColor3ub(96, 133, 158);
    glVertex2f(6.25f,-11.00f);
    glVertex2f(6.25f,-8.00f);
    glVertex2f(6.75f,-8.00f);
    glVertex2f(6.75f,-11.00f);
    glEnd();

    //2nd leg
    glBegin(GL_POLYGON);
    glColor3ub(96, 133, 158);
    glVertex2f(15.25f,-11.00f);
    glVertex2f(15.25f,-8.00f);
    glVertex2f(15.75f,-8.00f);
    glVertex2f(15.75f,-11.00f);
    glEnd();

    //bench line
    glBegin(GL_LINES);
    glColor3ub(23, 21, 21);
    glVertex2f(6.00f,-4.00f);
    glVertex2f(16.0f,-4.00f);
    glEnd();

    //line 2nd
    glBegin(GL_LINES);
    glColor3ub(23, 21, 21);
    glVertex2f(6.00f,-5.50f);
    glVertex2f(16.0f,-5.50f);
    glEnd();

}

// change color and text for enemy
void changeColorText(){
    if (enemyCount < 5){
                glColor3ub(255, 241, 118);  // Yellow color
                if (level == 1){
                    course = "Math1";
                }
                else if (level == 2){
                    course = "Math2";
                }
                else if (level == 3){
                    course = "Math3";
                }
            }
            else if (enemyCount < 10){
                glColor3ub(79, 195, 247);  // Sky blue color
                if (level == 1){
                    course = "C++";
                }
                else if (level == 2){
                    course = "C#";
                }
                else if (level == 3){
                    course = "Pyhton";
                }
            }
            else if (enemyCount < 15){
                glColor3ub(238, 238, 238);  // Grey color
                if (level == 1){
                    course = "English";
                }
                else if (level == 2){
                    course = "JAVA";
                }
                else if (level == 3){
                    course = "ADBMS";
                }

            }
}

// Draw enemy, player and bullet

void drawEnemy() {
    for (int i = 0; i < numEnemies; ++i) {
        if (enemyX[i] > -20.0f) {

            // Changing color of enemy
            changeColorText();
            glBegin(GL_POLYGON);
            glVertex2f(enemyX[i] + 1.3f, enemyY[i] - 3.0f);
            glVertex2f(enemyX[i] - 1.3f, enemyY[i] - 3.0f);
            glVertex2f(enemyX[i] - 1.3f, enemyY[i] + 1.0f);
            glVertex2f(enemyX[i] + 1.3f, enemyY[i] + 1.0f);
            glEnd();

            // Draw evaluation text on enemy
            glColor3ub(0, 0, 0);
            glRasterPos2f(enemyX[i] - 1.0f, enemyY[i] - 1.9f);
            std::string Text;
            switch (enemyCount % 5) {
                case 0: Text = "Quiz1"; break;
                case 1: Text = "Quiz2"; break;
                case 2: Text = "Attend"; break;
                case 3: Text = "Viva"; break;
                case 4: Text = "Exam"; break;
            }
            for (char c : Text) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }

            // Display course text on the enemy
            glColor3ub(0, 0, 0);  // Black color for text
            glRasterPos2f(enemyX[i] - 1.0f, enemyY[i] - 0.4f);
            for (char f : course){
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f);
            }
        }
    }
}

// drawing bullet
void drawBullet() {
    if (isBulletActive) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(bulletX - 0.2f, bulletY - 0.2f);
        glVertex2f(bulletX + 0.2f, bulletY - 0.2f);
        glVertex2f(bulletX + 0.2f, bulletY + 0.2f);
        glVertex2f(bulletX - 0.2f, bulletY + 0.2f);
        glEnd();
    }
}

// drawing player
void drawPlayer() {
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerX - 1.0f, playerY - 5.0f);
    glVertex2f(playerX + 1.0f, playerY - 5.0f);
    glVertex2f(playerX + 1.0f, playerY + 3.0f);
    glVertex2f(playerX - 1.0f, playerY + 3.0f);
    glEnd();
}

// draw Scene
void background() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.5);

    //background
    drawWall(232, 224, 190);

    // level up sign
    levelUpSign();

    // drawing noticeboard
    drawNoticeBoard(73, 39, 33);

    // draw Left door
    drawLeftDoor();

    //door 2
    drawRightDoor(165, 112, 100);

    // Draw FingerPrint 1
    drawFingerPrint1();

    // fingerprint 2 draw
    drawFingerPrint2();


    // draw dustbin
    drawDustbin();

    //floor
    drawFloor();
}

// Level 2 background code
void background2(){

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.5);

    // Draw wall
    drawWall(212, 214, 198);

    // level up
    levelUpSign();

    // Draw left door
    drawLeftDoor();

    // draw fingerprint 1
    drawFingerPrint1();


    // draw dustbin
    drawDustbin();

    // draw firebox
    drawFireBox();

    // Drawing noticeboard
    drawNoticeBoard(4, 84, 77);

    // draw floor
    drawFloor();


}

// Creating level 3 background
void background3() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.5);

    // draw wall
    drawWall(242, 234, 198);

    // level up
    levelUpSign();

    // Left door
    drawLeftDoor();

    // draw finger print
    drawFingerPrint1();

    // draw bench
    drawBench();

    // Draw fire box
    drawFireBox();

    // drawing noticeboard
    drawNoticeBoard(73, 39, 33);

    // Draw floor
    drawFloor();

}


// Update function
void update(int value) {

    if (isBulletActive) {
        bulletX += 0.4f;
        if (bulletX > 20.0f) {
            isBulletActive = false;
        }
    }

    if (isGameStarted){
        for (int i = 0; i < numEnemies; ++i) {
            enemyX[i] -= enemyMovementSpeed;
            if (enemyX[i] < -20.0f) {
                enemyX[i] = 20.0f;
                enemyY[i] = -11.0f + static_cast<float>(rand() % 300) / 100.0f;  // Randomize Y position

                // Increase enemy count
                enemyCount++;
                if (enemyCount >= 15) {
                    // Reset the count after 15 enemies
                    enemyCount = 0;
                }
            }

        }
    }else{
        gameMenu();
    }


    // Calling collision functions
    checkCollision();
    checkPlayerCollision();
    glutPostRedisplay();
    glutTimerFunc(5, update, 0);
}


// Display function
void display() {
    if (isGameStarted) {
        glClear(GL_COLOR_BUFFER_BIT);
        background();


    if (level == 2){
        background2();
    }
    else if (level == 3){
        background3();
    }

    // Draw player, bullet, and enemies
    drawPlayer();
    drawBullet();
    drawEnemy();

    // Render text and other UI elements
    renderBitmapString(-0.2f, 12.0f, 0.0f, GLUT_BITMAP_9_BY_15, "Notice Board");
    glRasterPos2f(-0.2f, 10.0f);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    // writing semester on screen
    glRasterPos2f(-0.2f, 8.0f);
    std::string levelText = "Semester: " + std::to_string(level);
    for (char c : levelText) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    // Writing player health on screen
     glRasterPos2f(-0.2f, 6.0f);
    std::string playerHealthText = "Health: " + std::to_string(playerHealth);
    for (char c : playerHealthText) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    }else {
        // Display the game menu
        gameMenu();
    }
    glutSwapBuffers();

}



// Function to handle menu key press events
void handleMenuKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case '1':  // New Game
        isGameStarted = true;
        glutDisplayFunc(display);
        break;
    case '2':  // Toggle Sound On/Off
        isSoundOn = !isSoundOn;
        if (isSoundOn) {
            isSoundOn = true;
        } else {
            isSoundOn = false;
        }
        break;
    case '3':
        // Show high score
        break;
    case '4':  // Controls
        // Implement control instructions display or handling
        break;
    case '5':  // Exit Game
        exit(0);
        break;
    }
    glutPostRedisplay();
}


// event handler
void handleKeypress(unsigned char key, int x, int y) {
    if (isGameStarted){


    switch (key) {
    case 'a':
        if (playerX < -18) {
            isPlayerMoving = false;
        }
        else {
            playerX -= 0.5f;
        }
        break;
    case 'd':
        playerX += 0.5f;
        break;
    case 'h':
        if (!isBulletActive) {
            // Fire bullet
            bulletX = playerX;
            bulletY = playerY;
            isBulletActive = true;
            if (isSoundOn == true){
                gunShotSound();
            }
        }
        break;
    case 'w':
        playerY += 0.5f;
        break;
    case 's':
        if (playerY < -11.0f){
            isPlayerMoving = false;
        }
        else{
             playerY -= 0.5f;
        }
        break;
    case 'b':
        glutDestroyWindow(glutGetWindow());
        gameMenu();
        break;
    }
    }else{
    // Handle menu-related keypress events
    handleMenuKeypress(key, x, y);
}
    glutPostRedisplay();
}


// main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 550);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Course Shooting Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(25, update, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);

    // Seed for random number generation
    srand(static_cast<unsigned int>(time(nullptr)));

    glutMainLoop();
    return 0;
}
