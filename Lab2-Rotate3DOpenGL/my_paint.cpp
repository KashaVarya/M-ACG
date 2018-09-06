#include "my_paint.h"
#include <QtOpenGL>
#include <GL/gl.h>
#include <iostream>


const GLfloat z1 = 0.2f;
const GLfloat z2 = 0.3f;
const GLfloat vertices_V[7][2] = {
    {0.3f, 0.1f},
    {0.1f, 0.7f},
    {0.2f, 0.7f},
    {0.35f, 0.25f},
    {0.5f, 0.7f},
    {0.6f, 0.7f},
    {0.4f, 0.1f},
};
const GLfloat vertices_K[13][2] = {
    {0.75f, 0.1f},
    {0.75f, 0.7f},
    {0.85f, 0.7f},
    {0.85f, 0.45f},
    {0.9f, 0.45f},
    {1.05f, 0.7f},
    {1.15f, 0.7f},
    {0.975f, 0.4f},
    {1.15f, 0.1f},
    {1.05f, 0.1f},
    {0.9f, 0.35f},
    {0.85f, 0.35f},
    {0.85f, 0.1f},
};

void drawFilledSquare(const GLfloat vertices[][2], int v1, int v2, int v3, int v4, GLfloat z1, GLfloat z2) {
    glVertex3f(vertices[v1][0], vertices[v1][1], z1);
    glVertex3f(vertices[v2][0], vertices[v2][1], z1);
    glVertex3f(vertices[v3][0], vertices[v3][1], z2);
    glVertex3f(vertices[v4][0], vertices[v4][1], z2);
}

void DrawLineStrip(const GLfloat vertices[][2], int n, GLfloat z) {
    // (GL_LINE_STRIP)-лінія з 2х точок
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < n; i++) {
        glVertex3f(vertices[i][0], vertices[i][1], z);
    }
    glVertex3f(vertices[0][0], vertices[0][1], z);
    glEnd();
}

void DrawLineZ(const GLfloat vertices[][2], int n){
    // (GL_LINE_STRIP)-лінія з 2х точок
    for(int i = 0; i < n; i++) {
        glBegin(GL_LINE_STRIP);
        glVertex3f(vertices[i][0], vertices[i][1], z1);
        glVertex3f(vertices[i][0], vertices[i][1], z2);
        glEnd();
    }
}


My_Paint::My_Paint(QWidget *parent) // конструктор
    : QGLWidget(parent) {
    r = 0;
    g = 0;
    b = 0;
    resize(1000, 600);
        xRotation = 0;
        yRotation = 0;
       zRotation = 0;
   scale = 1;
}

void My_Paint::initializeGL() {

    qglClearColor(Qt::white); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон




//    //Задаємо колір фону в OpenGL вікні
//    qglClearColor(QColor(245, 245, 208));
//    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
//    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
//    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
//    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
//    // Дозволяємо очищення буфера глибини
//    glClearDepth (1.0); // Дозволяємо очищення буфера глибини
//    // Тип тесту глибини
//    glDepthFunc (GL_LEQUAL);
//    // Поліпшення в обчисленні перспективи
//    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    // Дозволяємо змішування
//    glEnable (GL_BLEND);
//    // Вказуємо спосіб змішування
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//void My_Paint::initializeGL(QColor rgb) {
//    qglClearColor(rgb); // Вибираємо колірну палітру типу RGB
//}

void My_Paint::resizeGL(int nWidth, int nHeight) {
    glViewport(0, 0, nHeight, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы


//    // Встановлюємо точку огляду.
//    glViewport(0, 0, nWidth, nHeight);
//    // Встановлюємо режим матриці.
//    glMatrixMode(GL_PROJECTION);
//    // Завантажуємо матрицю
//    glLoadIdentity();
}

void My_Paint::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих линий
    // ось x
    glBegin(GL_LINES); // построение линии
        glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
        glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
        // ось y
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        // ось z
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void My_Paint::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу


    glScalef(scale, scale, scale);        // масштабирование
     glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
     glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
     glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z

     drawAxis();


    QColor halfGreen(0, 128, 0, 255); // устанавливаем цвет квадрата
    qglColor(halfGreen); // задаем цвет
    glBegin(GL_QUADS); // говорим, что рисовать будем прямоугольник
    // задаем вершины многоугольника
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

        // створюємо букву V квадратними полігонами
        glBegin(GL_QUADS);
        qglColor(QColor(247, 104, 151));
        // V – передня частина
        drawFilledSquare(vertices_V, 0, 1, 2, 6, z1, z1);
        drawFilledSquare(vertices_V, 3, 4, 5, 6, z1, z1);
        // V – задня частина
        drawFilledSquare(vertices_V, 0, 1, 2, 6, z2, z2);
        drawFilledSquare(vertices_V, 3, 4, 5, 6, z2, z2);
        // V - бокові частини
        drawFilledSquare(vertices_V, 0, 1, 1, 0, z1, z2);
        drawFilledSquare(vertices_V, 1, 2, 2, 1, z1, z2);
        drawFilledSquare(vertices_V, 2, 3, 3, 2, z1, z2);
        drawFilledSquare(vertices_V, 3, 4, 4, 3, z1, z2);
        drawFilledSquare(vertices_V, 4, 5, 5, 4, z1, z2);
        drawFilledSquare(vertices_V, 5, 6, 6, 5, z1, z2);
        drawFilledSquare(vertices_V, 6, 0, 0, 6, z1, z2);
        glEnd();
        // координати меж літери V
        glLineWidth(2.0);
        qglColor(QColor(180, 8, 65));
        DrawLineStrip(vertices_V, 7, z1);
        DrawLineStrip(vertices_V, 7, z2);
        DrawLineZ(vertices_V, 7);

        // створюємо букву K квадратними полігонами
        glBegin(GL_QUADS);
        qglColor(QColor(247, 104, 151));
        // K – передня частина
        drawFilledSquare(vertices_K, 0, 1, 2, 12, z1, z1);
        drawFilledSquare(vertices_K, 3, 4, 10, 11, z1, z1);
        drawFilledSquare(vertices_K, 4, 5, 6, 7, z1, z1);
        drawFilledSquare(vertices_K, 7, 8, 9, 10, z1, z1);
        drawFilledSquare(vertices_K, 4, 7, 10, 4, z1, z1);
        // K – задня частина
        drawFilledSquare(vertices_K, 0, 1, 2, 12, z2, z2);
        drawFilledSquare(vertices_K, 3, 4, 10, 11, z2, z2);
        drawFilledSquare(vertices_K, 4, 5, 6, 7, z2, z2);
        drawFilledSquare(vertices_K, 7, 8, 9, 10, z2, z2);
        drawFilledSquare(vertices_K, 4, 7, 10, 4, z2, z2);
        // K - бокові частини
        for(int i = 0; i < 12; i++) {
            drawFilledSquare(vertices_K, i, i+1, i+1, i, z1, z2);
        }
        drawFilledSquare(vertices_K, 12, 0, 0, 12, z1, z2);
        glEnd();
        // координати меж літери K
        glLineWidth(2.0);
        qglColor(QColor(180, 8, 65));
        DrawLineStrip(vertices_K, 13, z1);
        DrawLineStrip(vertices_K, 13, z2);
        DrawLineZ(vertices_K, 13);



//    // Очистити екран і буфер глибини
//    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glViewport(0, 0, 1000, 600);
//    //Задаємо режим матриці
//    glMatrixMode(GL_MODELVIEW);
//    //Завантажуємо матрицю
//    glLoadIdentity();
//    //Тут малюємо - для зручності в окремій функції
//    scene();
//    //выводимо на екран
//    //swapBuffers();
}







void My_Paint::scene() {


//    glTranslatef(0.0, 0.0, 0.0);

//glRotatef(angle, 0.0, 1.0, 0.0f); // функція обертання
/*    glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
    glLoadIdentity(); */          // загружает единичную матрицу моделирования

    glScalef(scale, scale, scale);        // масштабирование
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z

    //glMatrixMode(GL_PROJECTION);


//    // створюємо букву V квадратними полігонами
//    glBegin(GL_QUADS);
//    qglColor(QColor(247, 104, 151));
//    // V – передня частина
//    drawFilledSquare(vertices_V, 0, 1, 2, 6, z1, z1);
//    drawFilledSquare(vertices_V, 3, 4, 5, 6, z1, z1);
//    // V – задня частина
//    drawFilledSquare(vertices_V, 0, 1, 2, 6, z2, z2);
//    drawFilledSquare(vertices_V, 3, 4, 5, 6, z2, z2);
//    // V - бокові частини
//    drawFilledSquare(vertices_V, 0, 1, 1, 0, z1, z2);
//    drawFilledSquare(vertices_V, 1, 2, 2, 1, z1, z2);
//    drawFilledSquare(vertices_V, 2, 3, 3, 2, z1, z2);
//    drawFilledSquare(vertices_V, 3, 4, 4, 3, z1, z2);
//    drawFilledSquare(vertices_V, 4, 5, 5, 4, z1, z2);
//    drawFilledSquare(vertices_V, 5, 6, 6, 5, z1, z2);
//    drawFilledSquare(vertices_V, 6, 0, 0, 6, z1, z2);
//    glEnd();
//    // координати меж літери V
//    glLineWidth(2.0);
//    qglColor(QColor(180, 8, 65));
//    DrawLineStrip(vertices_V, 7, z1);
//    DrawLineStrip(vertices_V, 7, z2);
//    DrawLineZ(vertices_V, 7);

//    // створюємо букву K квадратними полігонами
//    glBegin(GL_QUADS);
//    qglColor(QColor(247, 104, 151));
//    // K – передня частина
//    drawFilledSquare(vertices_K, 0, 1, 2, 12, z1, z1);
//    drawFilledSquare(vertices_K, 3, 4, 10, 11, z1, z1);
//    drawFilledSquare(vertices_K, 4, 5, 6, 7, z1, z1);
//    drawFilledSquare(vertices_K, 7, 8, 9, 10, z1, z1);
//    drawFilledSquare(vertices_K, 4, 7, 10, 4, z1, z1);
//    // K – задня частина
//    drawFilledSquare(vertices_K, 0, 1, 2, 12, z2, z2);
//    drawFilledSquare(vertices_K, 3, 4, 10, 11, z2, z2);
//    drawFilledSquare(vertices_K, 4, 5, 6, 7, z2, z2);
//    drawFilledSquare(vertices_K, 7, 8, 9, 10, z2, z2);
//    drawFilledSquare(vertices_K, 4, 7, 10, 4, z2, z2);
//    // K - бокові частини
//    for(int i = 0; i < 12; i++) {
//        drawFilledSquare(vertices_K, i, i+1, i+1, i, z1, z2);
//    }
//    drawFilledSquare(vertices_K, 12, 0, 0, 12, z1, z2);
//    glEnd();
//    // координати меж літери K
//    glLineWidth(2.0);
//    qglColor(QColor(180, 8, 65));
//    DrawLineStrip(vertices_K, 13, z1);
//    DrawLineStrip(vertices_K, 13, z2);
//    DrawLineZ(vertices_K, 13);
}

void My_Paint::mousePressEvent(QMouseEvent* event) {
    // запоминаем координату нажатия мыши
    mousePos = event->pos();
}

void My_Paint::mouseMoveEvent(QMouseEvent* event) {
    xRotation += 180/scale*(GLfloat)(event->y()-mousePos.y())/height(); // вычисляем углы поворота
    zRotation += 180/scale*(GLfloat)(event->x()-mousePos.x())/width();

    mousePos = event->pos();

    updateGL(); // обновляем изображение
}

void My_Paint::mouseReleaseEvent(QMouseEvent *event)
{
}

void My_Paint::wheelEvent(QWheelEvent* event) // вращение колёсика мыши
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе -- делим на 1.1
    if ((event->delta())>0) scale*=1.1;
    else if ((event->delta())<0) scale/=1.1;

    updateGL();
}

void My_Paint::keyPressEvent(QKeyEvent*) {
    angle -= 0.15f; // кут і напрямок повороту
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистити екран і буфер глибини

    paintGL();
}
