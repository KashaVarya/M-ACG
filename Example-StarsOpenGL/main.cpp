// Звездное небо
#include <GL/glut.h>
#include <vector>
#include <cmath>
using namespace std;

// структура с координатами звезд
struct Star
{
  float x, y, z;
};

vector<Star> starList;

enum { RANGE = 150 };

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (vector<Star>::iterator i = starList.begin(); i != starList.end(); ++i)
    {
        // задаем яркость звезд в зависимости от дальности их нахождения
        const float L = 110 / abs(i->z - (70 + 50));
        // делаем звезды больше по мере их приближения
        glPointSize(1.5f + 1.0f - (50 - i->z) / 550.0f);
        glColor3f(L, L, L);
        glBegin(GL_POINTS);
        glVertex3f(i->x, i->y, i->z);
        glEnd();
    }
    glutSwapBuffers();
}

void timer(int = 0)
{
    for (vector<Star>::iterator i = starList.begin(); i != starList.end(); ++i)
    {
        // регулируем скорость звезд
        i->z += 0.25;
        // отображаем звезды заново, если их уже не видно
        if (i->z > 50)
        {
            i->x = 1.0f * (rand() % (2 * RANGE) - RANGE);
            i->y = 1.0f * (rand() % (2 * RANGE) - RANGE);
            i->z = -500;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1, timer, 0);
}

int main(int argc, char **argv)
{
    // инициализируем массив 1000 звёзд
    for (int i = 0; i < 1000; ++i)
    {
        Star star = { 1.0f * (rand() % (2 * RANGE) - RANGE),
                      1.0f * (rand() % (2 * RANGE) - RANGE),
                      1.0f * (rand() % 500 - 500) };
        starList.push_back(star);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(852, 480);
    glutInitWindowPosition(0, 86);
    glutCreateWindow("Stars");
    glClearColor(0, 0, 0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0, 100);
    glutDisplayFunc(display);
    timer();
    glutMainLoop();
}
