#include "my_paint.h"
#include <QtOpenGL>
#include <GL/gl.h>


My_Paint::My_Paint(){}

void My_Paint::initializeGL()
{
    //Обрати фоновий (очищуючий) колір
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClearColor(r,g,b,t); Де, r-червоний колір, g-зелений, b-голубий, t-прозрачність.
    //Задаємо режим обробки полігонів - передню та задню частини,
    //полігони повністю зафарбовані
    //(можна просто відображувати обрамлення)
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void My_Paint::resizeGL(int nWidth, int nHeight)
{
    //Встановлюємо точку огляду. Останні два параметра однакові -
    // щоб не порушувати пропорції у широких экранів
    glViewport(0, 0, nWidth, nHeight);
    //Встановлюємо режим матриці
    glMatrixMode(GL_PROJECTION);
    //Завантажуємо матрицю
    glLoadIdentity();
}

void My_Paint::paintGL()
{
    this->resize(600, 400);
    //Очищуємо екран
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Встановити проекцію:
    glViewport(0, 0, 600, 400);
    //Задаємо режим матриці
    glMatrixMode(GL_PROJECTION);
    //Завантажуємо матрицю
    glLoadIdentity();
    // L, R, B. T, Near, Far
    glOrtho(0.0,600.0,400.0,0.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW); // return to the model matrix
    glLoadIdentity();
    //Тут малюємо - для зручності в окремій функції
    scene();
    //выводимо на екран
    swapBuffers();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.14f;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}

void drawFilledRectange(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z=0.0){
    //Починаємо відрисовку, аргумент означає відрисовку прямокутника.
    //Кожний виклик glVertex3f задає одну вершину прямокутника
    glBegin(GL_POLYGON);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
    glEnd();
}

void My_Paint::scene()
{
    // Малюємо небо
    //Задаємо колір зображення
    qglColor(QColor(0x39, 0x2d, 0xe1));
    drawFilledRectange(0.0, 0.0, 600.0, 80.0);

    qglColor(QColor(0x46, 0x3b, 0xd2));
    drawFilledRectange(0.0, 80.0, 600.0, 160.0);

    qglColor(QColor(0x53, 0x4b, 0xbc));
    drawFilledRectange(0.0, 160.0, 600.0, 240.0);

    qglColor(QColor(0x56, 0x51, 0x9d));
    drawFilledRectange(0.0, 240.0, 600.0, 320.0);

    qglColor(QColor(0x56, 0x53, 0x82));
    drawFilledRectange(0.0, 320.0, 600.0, 400.0);

    //Зіроньки
    qglColor(QColor(0xf0, 0xf3, 0x0f));
    drawFilledRectange(50.0, 50.0, 70.0, 70.0);
    drawFilledRectange(330.0, 20.0, 350.0, 40.0);
    drawFilledRectange(520.0, 60.0, 540.0, 80.0);
    drawFilledRectange(500.0, 80.0, 520.0, 100.0);

    // Основа будиночка
    qglColor(QColor(0xd4, 0x30, 0x89));
    drawFilledRectange(110.0, 200.0, 490.0, 360.0);

    // Основне вікно та двері
    qglColor(QColor(0xe3, 0xd3, 0x1b));
    drawFilledRectange(150.0, 240.0, 190.0, 280.0);
    drawFilledRectange(220.0, 270.0, 280.0, 360.0);

    // Вікно у душовій
    qglColor(QColor(0xe0, 0x9b, 0x15));
    drawFilledRectange(360.0, 230.0, 450.0, 270.0);

    // Дах
    qglColor(QColor(0x7e, 0x61, 0x07));
    glBegin(GL_POLYGON);
    glVertex3f(70.0,200.0,0.0);
    glVertex3f(190.0,60.0,0.0);
    glVertex3f(550.0,200.0,0.0);
    glEnd();

    // Гірлянда на даху
    qglColor(QColor(0xa6, 0x13, 0x8f));
    drawFilledCircle(135, 155, 15);

    qglColor(QColor(0xc9, 0x5a, 0xae));
    drawFilledCircle(175, 145, 15);

    qglColor(QColor(0xa0, 0x2a, 0x8e));
    drawFilledCircle(215, 135, 15);

    qglColor(QColor(0xdb, 0x3a, 0xc2));
    drawFilledCircle(255, 115, 15);

}
