#pragma once
#include <GL/glut.h>
#include <iostream>

#define REVEAL_SPEED_DEFAULT 0.02
#define ROTATION_SPEED_DEFAULT 2
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define GAME_FONT GLUT_BITMAP_TIMES_ROMAN_24
#define SAVEFILE "savefile.save"
const char ENTER_KEY = (char)13;

extern std::string USERNAME;
extern bool WAITING_FOR_CHOICE;
extern bool WAITING_FOR_INPUT;

// levels where LEVELS[i][0] and LEVELS[i][1] are the rotation speed and number of iterations of the level i, respectively
const int LEVELS[][2] =
    {
        {4, 6},
        {4, 12},
        {4, 16},
        {5, 16},
        {6, 20},
        {9, 10},
        {9, 15},
        {9, 23},
        {10, 5},
        {10, 10},
        {10, 15},
        {12, 5},
        {12, 9},
        {12, 17},
        {15, 5},
        {15, 10},
        {15, 15},
        {15, 20},
        {15, 30},
        {18, 5},
        {18, 10},
        {18, 15},
        {18, 20},
        {20, 5},
        {20, 15},
        {20, 20},
        {30, 5},
        {30, 10},
        {30, 15},
        {30, 20},
        {30, 25},
        {30, 30},
        {45, 20},
};

const GLfloat REVEAL_SPEED = REVEAL_SPEED_DEFAULT; // incements/decrements of height per frame (multiples of 0.02)

extern int highscore;
extern int alltime_highscore;
extern std::string alltime_highscore_username;
extern int currentLevel;
extern int iterationsDone;
extern int WINDOW_ID;        // window id, use this to dispose of the window glutDestroyWindow(id)

enum Location
{
    UNDEFINED = -1,
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};
extern Location smallCubeLocation;
extern Location choice;

enum Animation
{
    NONE = 0,
    REVEALING = 1,
    SPINNING = 2
};
extern Animation currentAnimation;

// vertex index
extern GLint LUF, LLF, RLF, RUF, LUB, LLB, RLB, RUB;

// array to hold cube's 8 vertices
extern const float ver[8][3];

// array to hold color of cube's 6 faces
extern const GLfloat color[8][3];

extern GLboolean p1, p2;
extern GLfloat SC;
extern GLfloat p1_a;
extern GLfloat p2_a;
extern int dir; // rand()%2 +1;

// For use in animation through keyboard
extern double rotate_y, rotate_x, translate_x, translate_y;

void startLevel(int v);
void revealAll();
void reveal(int v); // play the reveal animation
void slideDown(int v);

void rotateP1(int v); // play the rotate around P1 animation
void rotateP2(int v); // play the rotate around P2 animation

// Function to draw a quad: every call draws a face for a cube
void quad(int clr, int ver1, int ver2, int ver3, int ver4);
void cube();

void Center_R();
void Center_L();
void Left();
void Right();

void drawSmallCube();
void drawCenterCube();
void drawRightCube();
void drawLeftCube();

void playLevel(); //play the next level

void handleGameSceneControls(unsigned char key, int x, int y);
void handleMainMenuControls(unsigned char key, int x, int y);
void handleHighscoresSceneControls(unsigned char key, int x, int y);
void handleUsernameSceneControls(unsigned char key, int x, int y);

enum Scene
{
    MAIN_MENU = 0,
    GAME = 1,
    HIGHSCORES = 2,
    USERNAME_SCENE = 3
};
extern Scene currentScene;
void switchScenes(Scene);
void gameScene();
void mainMenuScene();
void highscoresScene();
void usernameScene();

// utils

void drawText(GLfloat x, GLfloat y, std::string text);
void setAlltimeHighscore(std::string username, int score);
std::string getAlltimeHighscoreUsername();
int getAlltimeHighscore();
