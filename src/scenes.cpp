#include "game.h"
using namespace std;

void common()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2, 2); // Clipping vol.  Defualt z: 0, 1 (i.e. from z=0 to z=-1)
    glMatrixMode(GL_MODELVIEW);
}

int currentLevel = 0;
int highscore = 0;
int alltime_highscore = 0;
string alltime_highscore_username = getAlltimeHighscoreUsername();

void drawGameSceneBottomMenu()
{
    glLoadIdentity();
    glColor3f(1, 1, 1);
    string level = "Level: " + to_string(currentLevel);
    drawText(-1.9, 1.8, level);
    drawText(-1.9, -1.3, "(m) - Back to main menu");
    drawText(-1.9, -1.5, "(p) - Play next level ");
    drawText(-1.9, -1.7, "Highscore: " + to_string(highscore));

    if (USERNAME == alltime_highscore_username)
        drawText(-1.9, -1.9, "Alltime Highscore: " + to_string(highscore) + " (by you)");
    else drawText(-1.9, -1.9, "Alltime Highscore: " + to_string(getAlltimeHighscore()) + " (by " + alltime_highscore_username + ")");

    if (WAITING_FOR_CHOICE)
    {
        drawText(0.8, -1.3, "(1) - Choose left");
        drawText(0.8, -1.5, "(2) - Choose center");
        drawText(0.8, -1.7, "(3) - Choose right");
    }
}

void gameScene()
{
    common();
    drawGameSceneBottomMenu();

    if (currentAnimation == Animation::REVEALING && (choice == smallCubeLocation || choice == UNDEFINED))
        drawSmallCube();

    // center cube
    drawCenterCube();

    // right cube
    drawRightCube();

    // left cube
    drawLeftCube();

    glutSwapBuffers();
}

void mainMenuScene()
{
    common();

    glColor3f(1, 1, 1);

    drawText(0, 1, "Start game\t(p)");
    drawText(0, .5, "View highscore\t(h)");
    drawText(0, 0, "Set your username\t(u)");
    drawText(0, -0.5, "Quit\t(q)");

    glutSwapBuffers();
}

void highscoresScene()
{
    common();
    drawText(0, 1, "This legendary player was able to reach level " + to_string(getAlltimeHighscore()) + "!");
    drawText(0, .5, getAlltimeHighscoreUsername());
    drawText(0, 0, "Press anykey to go back.");

    glutSwapBuffers();
}

string USERNAME = "";
void usernameScene()
{
    common();
    drawText(0, 1.5, "Enter your name!");
    if (USERNAME.length())
        drawText(0, 0, USERNAME);
    drawText(0, -1.5, "Press enter when you're finished.");

    glutSwapBuffers();
}