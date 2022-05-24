#include "game.h"
#include <fstream>
using namespace std;
void switchScenes(Scene scene)
{
    switch (scene)
    {
    case MAIN_MENU:
        glutDisplayFunc(mainMenuScene);
        glutKeyboardFunc(handleMainMenuControls);
        break;
    case GAME:
        glutDisplayFunc(gameScene);
        glutKeyboardFunc(handleGameSceneControls);
        break;
    case HIGHSCORES:
        glutDisplayFunc(highscoresScene);
        glutKeyboardFunc(handleHighscoresSceneControls);
        break;
    case USERNAME_SCENE:
        glutDisplayFunc(usernameScene);
        glutKeyboardFunc(handleUsernameSceneControls);
        break;
    default:
        break;
    }
    currentScene = scene;
    glutPostRedisplay();
}

int getTextWidth(string text)
{
    int width = 0;
    for (const char c : text)
        width += glutBitmapWidth(GAME_FONT, (int)c);
    return width;
}

void drawText(GLfloat x, GLfloat y, string text)
{
    glRasterPos2f(x, y);
    for (int i = 0; i < text.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void setAlltimeHighscore(std::string username, int score)
{
    alltime_highscore = score;
    alltime_highscore_username = username;
    ofstream file;
    file.exceptions(ifstream::badbit); // No need to check failbit
    try
    {
        file.open(SAVEFILE);
        file << username << "\n";
        file << score;
    }
    catch (const ifstream::failure &e)
    {
        cout << "Can't save to savefile.";
    }

    file.close();
}

string getAlltimeHighscoreUsername()
{
    string username = "UNKNOWN or doesn't exist yet.";
    ifstream file;
    file.exceptions(ifstream::badbit); // No need to check failbit
    try
    {
        file.open(SAVEFILE);
        getline(file, username);
    }
    catch (const ifstream::failure &e)
    {
        cout << "Can't open savefile, or it doesn't exist.";
    }

    file.close();
    return username;
}
int getAlltimeHighscore()
{
    int score = 0;
    ifstream file;
    file.exceptions(ifstream::badbit); // No need to check failbit
    try
    {
        file.open(SAVEFILE);
        string temp;
        getline(file, temp);
        getline(file, temp);
        score = stoi(temp);
    }
    catch (...)
    {
        cout << "Can't open savefile, or it doesn't exist.";
    }

    file.close();
    return score;
}
