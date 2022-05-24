#include "game.h"
using namespace std;

Location smallCubeLocation = CENTER;
Animation currentAnimation = NONE;
int iterationsDone = 0;

GLint LUF = 0, LLF = 1, RLF = 2, RUF = 3, LUB = 4, LLB = 5, RLB = 6, RUB = 7;

const float ver[8][3] =
    {
        {-0.2, 0.2, 0.2},   // LUF (Left Upper Front)
        {-0.2, -0.2, 0.2},  // LLF (Left Lower Front)
        {0.2, -0.2, 0.2},   // RLF (Right Lower Front)
        {0.2, 0.2, 0.2},    // RUF
        {-0.2, 0.2, -0.2},  // LUB (Left Upper Back)
        {-0.2, -0.2, -0.2}, // LLB
        {0.2, -0.2, -0.2},  // RLB
        {0.2, 0.2, -0.2},   // RUB
};

const GLfloat color[8][3] =
    {
        {0.0, 0.0, 1.0}, // BLeft
        {1.0, 0.0, 1.0}, // MRight
        {0.0, 1.0, 0.0}, // GUpper
        {1.0, 0.5, 0.0}, // OrangeLower
        {1.0, 0.0, 0.0}, // RFront
        {1.0, 1.0, 0.0}, // YBack
};

GLboolean p1 = false, p2 = false;
GLfloat SC = 0.0;
GLfloat p1_a = 0.0;
GLfloat p2_a = 0.0;
int dir = 1; // rand()%2 +1;

void quad(int clr, int ver1, int ver2, int ver3, int ver4)
{
    glColor3fv(color[clr]);
    glBegin(GL_QUADS);
    glVertex3fv(ver[ver1]);
    glVertex3fv(ver[ver2]);
    glVertex3fv(ver[ver3]);
    glVertex3fv(ver[ver4]);
    glEnd();
}

void cube()
{

    quad(0, LUF, LLF, LLB, LUB); // Draw left faceB
    quad(1, RUF, RLF, RLB, RUB); // Draw right faceM
    quad(2, LUF, RUF, RUB, LUB); // Draw upper faceG
    quad(3, LLF, RLF, RLB, LLB); // Draw lower faceO
    quad(4, LUF, RUF, RLF, LLF); // Draw front faceR
    quad(5, LUB, RUB, RLB, LLB); // Draw back faceY
}

void Center_R()
{ // if center cube is going right (around p1(0.5,0,0))
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(p1_a, 0.0, 1.0, 0.0);
    glTranslatef(-0.5, 0.0, 0.0);
}
void Center_L()
{ // if center cube is going left (around p2(-0.5,0,0))

    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(p2_a, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
}
void Left()
{ // if left cube going to middle (around p2)

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(p2_a, 0.0, 1.0, 0.0);
    glTranslatef(-0.5, 0.0, 0.0);
}
void Right()
{ // if right cube going to middle (around p1)

    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(p1_a, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
}

void advanceLevel()
{
    if (choice == smallCubeLocation)
    {
        currentLevel++;
        highscore = max(highscore, currentLevel);
        if (highscore > alltime_highscore)
            setAlltimeHighscore(USERNAME, highscore);
    }
    else
        currentLevel = 0;
    iterationsDone = 0;
}

void reveal(int v)
{
    if (SC < 1)
    {
        SC += REVEAL_SPEED;
        glLoadIdentity();
        glutPostRedisplay();
        glutTimerFunc(1000 / 60.0, reveal, v);
    }
    else
    {
        glutTimerFunc(1000, slideDown, v);
    }
}
void slideDown(int v)
{
    if (SC > 0)
    {
        SC -= REVEAL_SPEED;
        glLoadIdentity();
        glutTimerFunc(1000 / 60.0, slideDown, v);
    }
    else
    {
        if (choice != UNDEFINED)
            advanceLevel();
        choice = UNDEFINED;
        currentAnimation = NONE;
        WAITING_FOR_INPUT = true;
    }
    glutPostRedisplay();
}

void rotateP1(int v)
{
    if (p1_a < 180)
    {
        p1_a += LEVELS[currentLevel][0];
        glLoadIdentity();
        glutTimerFunc(1000 / 60.0, rotateP1, v);
    }
    else
    {
        p1_a = 0.0;
        dir = rand() % 2 + 1;
        currentAnimation = NONE;
        p1 = false;
        if (smallCubeLocation == CENTER)
            smallCubeLocation = RIGHT;
        else if (smallCubeLocation == RIGHT)
            smallCubeLocation = CENTER;
        iterationsDone++;
        playLevel();
    }
    glutPostRedisplay();
}
void rotateP2(int v)
{
    if (p2_a > -180)
    {
        p2_a -= LEVELS[currentLevel][0];
        glLoadIdentity();
        glutTimerFunc(1000 / 60.0, rotateP2, v);
    }
    else
    {
        p2 = false;
        p2_a = 0, 0;
        dir = rand() % 2 + 1;
        currentAnimation = NONE;
        if (smallCubeLocation == CENTER)
            smallCubeLocation = LEFT;
        else if (smallCubeLocation == LEFT)
            smallCubeLocation = CENTER;
        iterationsDone++;
        playLevel();
    }
    glutPostRedisplay();
}

void drawSmallCube()
{
    glLoadIdentity();
    if (smallCubeLocation == RIGHT)
        glTranslatef(1, 0.0, 0.0);
    if (smallCubeLocation == LEFT)
        glTranslatef(-1, 0.0, 0.0);
    glRotatef(10, 1.0, 1.0, 0.0); // rotate to make the 3d look shine
    glScalef(0.5, 0.5, 0.5);      // make the small cube small

    cube();
}
void drawCenterCube()
{
    glLoadIdentity();
    glRotatef(10, 1.0, 1.0, 0.0);

    if (currentAnimation == Animation::REVEALING && (choice == Location::CENTER || choice == UNDEFINED))
        glTranslatef(0.0, SC, 0.0);
    if (p1)
        Center_R();
    if (p2)
        Center_L();
    cube();
}
void drawRightCube()
{
    glLoadIdentity();
    glRotatef(10, 1.0, 1.0, 0.0);
    if (currentAnimation == Animation::REVEALING && (choice == Location::RIGHT || choice == UNDEFINED))
        glTranslatef(0.0, SC, 0.0);
    glTranslatef(1, 0.0, 0.0);
    if (p1)
        Right();
    cube();
}
void drawLeftCube()
{
    glLoadIdentity();
    glRotatef(10, 1.0, 1.0, 0.0);
    if (currentAnimation == Animation::REVEALING && (choice == Location::LEFT || choice == UNDEFINED))
        glTranslatef(0.0, SC, 0.0);
    glTranslatef(-1, 0.0, 0.0);
    if (p2)
        Left();

    cube();
}

void playLevel()
{
    if (iterationsDone < LEVELS[currentLevel][1])
    {
        currentAnimation = Animation::SPINNING;
        if (dir == 1)
        {
            p1 = true;
            rotateP1(0);
        }
        else
        {
            p2 = true;
            rotateP2(0);
        }
    }
    else
        WAITING_FOR_CHOICE = true;
}

void revealAll()
{
    choice = UNDEFINED;
    currentAnimation = Animation::REVEALING;
    reveal(0);
}

void startLevel(int v)
{
    if (currentAnimation == Animation::REVEALING)
        glutTimerFunc(1000 / 60.0, startLevel, v);
    else playLevel();
}