#include "game.h"

bool WAITING_FOR_INPUT = true;
bool WAITING_FOR_CHOICE = false;
Location choice = UNDEFINED;

void handleGameSceneControls(unsigned char key, int x, int y)
{
    if (WAITING_FOR_INPUT && !currentAnimation)
    {
        switch (key)
        {
        case '~': // cheat
            currentAnimation = Animation::REVEALING;
            reveal(0);
            break;
        case '1':
            if (WAITING_FOR_CHOICE)
            {
                WAITING_FOR_CHOICE = false;
                currentAnimation = Animation::REVEALING;
                choice = Location::LEFT;
                reveal(0);
                iterationsDone = 0;
            }
            break;
        case '2':
            if (WAITING_FOR_CHOICE)
            {
                WAITING_FOR_CHOICE = false;
                currentAnimation = Animation::REVEALING;
                choice = Location::CENTER;

                reveal(0);
            }
            break;
        case '3':
            if (WAITING_FOR_CHOICE)
            {
                WAITING_FOR_CHOICE = false;
                currentAnimation = Animation::REVEALING;
                choice = Location::RIGHT;
                reveal(0);
            }
            break;
        case 'm':
            switchScenes(MAIN_MENU);
            break;
        case 'p':
            if (!WAITING_FOR_CHOICE) {
                currentAnimation = Animation::REVEALING;
                choice = UNDEFINED;
                revealAll();
                startLevel(0);
            }
            break;
        default:
            break;
            glutPostRedisplay(); // Re-execte drawing, having rotated
        }
    }
}

void handleMainMenuControls(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        switchScenes(Scene::GAME);
        break;
    case 'h':
        switchScenes(Scene::HIGHSCORES);
        break;
    case 'q':
        glutDestroyWindow(WINDOW_ID);
        exit(0);
        break;
    case 'u':
        switchScenes(USERNAME_SCENE);
        break;
    default:
        break;
    }
}

void handleHighscoresSceneControls(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'm':
        switchScenes(Scene::MAIN_MENU);
        break;
    default:
        switchScenes(Scene::MAIN_MENU);
        break;
    }
}

void handleUsernameSceneControls(unsigned char key, int x, int y)
{
    int length = USERNAME.length();
    if (key == ENTER_KEY && length)
        return switchScenes(Scene::MAIN_MENU);
    if (key == 8 && length)
        USERNAME = USERNAME.substr(0, length - 1);
    if ((key >= 48 && key <= 57) || (key >= 97 && key <= 122) || (key >= 65 && key <= 90) || (key == 32 && length))
        USERNAME += key;
    glutPostRedisplay();
}