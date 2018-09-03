#include "my_paint.h"
#include <QApplication>
#include <GL/gl.h>


My_Paint::My_Paint(){}

void My_Paint::initializeGL()
{
    //Обрати фоновий (очищуючий) колір
    glClearColor(1.0,0.84,0.0,1.0);
    //glClearColor(r,g,b,t); Де, r-червоний колір, g-зелений, b- голубий, t-прозрачність.

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
     //struct MyThread : public QThread {using QThread::msleep;};

     //Очищуємо екран
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     //Встановити проекцію:

     //Задаємо режим матриці
     glMatrixMode(GL_PROJECTION);
     //Завантажуємо матрицю
     glLoadIdentity();
     glOrtho(0.0,600.0,0.0,400.0,-1.0,1.0);

     //Тут малюємо - для зручності в окремій функції
     scene();

     //выводимо на екран
     // swapBuffers();

     //MyThread::msleep(100000);

}

void My_Paint::scene()
{
     //Задаємо колір зображення
     glClearColor(1.0,0.0,0.0,1.0);
    
     //Починаємо відрисовку, аргумент означає відрисовку прямокутника.
     //Кожний виклик glVertex3f задає одну вершину прямокутника
     glBegin(GL_POLYGON);
     glVertex3f(50.0,350.0,0.0); //Координати квадрата
     glVertex3f(250.0,350.0,0.0);
     glVertex3f(250.0,150.0,0.0);
     glVertex3f(50.0,150.0,0.0);
     glEnd();

    //Стрілка вгору
    glColor3f(0.0,0.75,1.0); //Обираємо голубий колір
    glBegin(GL_POLYGON);
    glVertex3f(400.0,275.0,0.0); //Координати трикутника
    glVertex3f(475.0,375.0,0.0);
    glVertex3f(550.0,275.0,0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(435.0,275.0,0.0); //Координати квадрата
    glVertex3f(515.0,275.0,0.0);

    glVertex3f(515.0,175.0,0.0);
    glVertex3f(435.0,175.0,0.0);
    glEnd();

    //Стрілка ліворуч
    glColor3f(0.0,0.75,1.0); //Обираємо голубий колір
    glBegin(GL_POLYGON);
    glVertex3f(350.0,25.0,0.0); //Координати трикутника
    glVertex3f(250.0,100.0,0.0);
    glVertex3f(350.0,175.0,0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(350.0,140.0,0.0); //Координати квадрата
    glVertex3f(525.0,140.0,0.0);
    glVertex3f(525.0,70.0,0.0);
    glVertex3f(350.0,70.0,0.0);
    glEnd();
}
