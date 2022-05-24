#include "game.h"
using namespace std;

int WINDOW_ID;
Scene currentScene = USERNAME_SCENE;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    WINDOW_ID = glutCreateWindow("Trace the Cube");
    switchScenes(Scene::USERNAME_SCENE);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
