#include "my_paint.h"
#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <complex>
#include <vector>
#include <math.h>

#define PI 3.141592653f
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef double                 T_coord;
typedef std::complex<T_coord>  T_point;
typedef std::vector<T_point>   T_figure;

GLuint	texture;
int light_sample = 1;

void DrawPolygon(int n){
    T_point center(0.0, 0.0);
    T_point vertex(0.0, 1.0);
    T_figure pyramid;
    pyramid.push_back(vertex);

    // Розраховуємо координати многокутника
    T_point  radius_next = vertex - center;
    for(int i = 0; i < n - 1; ++i)
    {
        radius_next *= std::polar(1.0, acos(-1.0) * 2 / n );
        T_point vertex_next = center + radius_next;
        pyramid.push_back(vertex_next);
    }

    // Малюємо основу - многокутник
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i = 0; i < n; i++) {
        glTexCoord2f((1-pyramid[i].real())/2, (1+pyramid[i].imag())/2);
        glVertex3f(pyramid[i].real(), -1.0f, pyramid[i].imag());
    }
    glEnd();

    // Малюємо грані піраміди - трикутники
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int i = 0; i < n - 1; i++) {
        glVertex3f( pyramid[i].real(), -1.0f, pyramid[i].imag());
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glVertex3f( pyramid[i+1].real(), -1.0f, pyramid[i+1].imag());
        glColor3f(0.0f+i*1.0f/n, 0.0f+i*1.0f/n, 1.0f);
    }
    glVertex3f( pyramid[n-1].real(), -1.0f, pyramid[n-1].imag());
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( pyramid[0].real(), -1.0f, pyramid[0].imag());
    glEnd();
}

void LoadTextures() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("sea.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void light(void) {
    // властивости материалу
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    // встановлення джерела світла
    if (light_sample == 1) {
        // направлене джерело світла
        GLfloat light0_diffuse[] = {1.5f, 1.5f, 1.5f};
        GLfloat light0_direction[] = {0.0, 0.0, 1.0, 0.0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    }
    if (light_sample == 2) {
        // точкове джерело світла
        // спадання інтенсивності з відстанню відключено (за замовчуванням)
        GLfloat light1_diffuse[] = {1.5f, 1.5f, 1.5f};
        GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    }
    if (light_sample == 3) {
        // точкове джерело світла
        // спадання інтенсивності з відстанню задано функциею f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
        GLfloat light2_diffuse[] = {1.5f, 1.5f, 1.5f};
        GLfloat light2_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.7f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.7f);
    }
    if (light_sample == 4) {
        // прожектор
        // спадання інтенсивності з відстанню відключено (за замовчуванням)
        // половина кута при вершині 30 градусів
        // напрямок на центр поверхні
        GLfloat light3_diffuse[] = {1.5f, 1.5f, 1.5f};
        GLfloat light3_position[] = {0.0, 0.0, 1.0, 1.0};
        GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
        glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
    }
    if (light_sample == 5) {
        // прожектор
        // спадання інтенсивності з відстанню відключено (за замовчуванням)
        // половина кута при вершині 30 градусів
        // напрям на центр поверхні
        // включений розрахунок зменшення інтенсивності для прожектора
        GLfloat light4_diffuse[] = {1.5f, 1.5f, 1.5f};
        GLfloat light4_position[] = {0.0, 0.0, 1.0, 1.0};
        GLfloat light4_spot_direction[] = {0.0, 0.0, -1.0};
        glEnable(GL_LIGHT4);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
        glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
        glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);
        glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
    }
    if (light_sample == 6) {
        // декілька джерел світла
        GLfloat light5_diffuse[] = {1.0, 0.0, 0.0};
        GLfloat light5_position[] = {0.5f * cos(0.0f), 0.5f * sin(0.0f), 1.0, 1.0};
        glEnable(GL_LIGHT5);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
        glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
        glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.8f);
        GLfloat light6_diffuse[] = {0.0, 1.0, 0.0};
        GLfloat light6_position[] = {0.5f * cos(2.0f * PI / 3.0f), 0.5f * sin(2.0f * PI / 3.0f), 1.0, 1.0};
        glEnable(GL_LIGHT6);
        glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
        glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
        glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.8f);
        GLfloat light7_diffuse[] = {0.0, 0.0, 1.0};
        GLfloat light7_position[] = {0.5f * cos(4.0f * PI / 3), 0.5f * sin(4 * PI / 3), 1.0, 1.0};
        glEnable(GL_LIGHT7);
        glLightfv(GL_LIGHT7, GL_DIFFUSE, light7_diffuse);
        glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
        glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.8f);
    }

    glNormal3f(1.0, -1.0, -1.0);
    DrawPolygon(24);

    // відключення джерел світла
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
}

My_Paint::My_Paint(QWidget *parent) // конструктор
    : QGLWidget(parent) {
    resize(1000, 600);
    //resize(1000, 600);
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
    scale = 1;
}

void My_Paint::initializeGL() {
    LoadTextures();			// Загрузка текстур
    glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры

    // розрахунок освітлення
    glEnable(GL_LIGHTING);
    // двухсторонній розрахунок освітлення
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    // автоматичне приведення нормалей до
    // одиничної довжини
    glEnable(GL_NORMALIZE);

    qglClearColor(QColor(245, 245, 208)); // заполняем фон
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей - будут ли видны противоположные грани
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glPolygonMode(GL_BACK, GL_FRONT_FACE); // фигуры будут закрашены с обеих сторон

    // Дозволяємо очищення буфера глибини
    glClearDepth (1.0); // Дозволяємо очищення буфера глибини
    // Тип тесту глибини
    glDepthFunc (GL_LEQUAL);
    // Поліпшення в обчисленні перспективи
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    // Дозволяємо змішування
    glEnable (GL_BLEND);
    // Вказуємо спосіб змішування
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepth(1.0);                   // Set background depth to farthest
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
}

void My_Paint::resizeGL(int nWidth, int nHeight) {
    glViewport(0, 0, nHeight, nWidth); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
}

void My_Paint::paintGL() {
    resizeGL(800, 1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу

    glScalef(0.5, 0.5, 0.5);        // масштабирование
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z

    light();
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

void My_Paint::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_1) light_sample = 1;
    if (event->key() == Qt::Key_2) light_sample = 2;
    if (event->key() == Qt::Key_3) light_sample = 3;
    if (event->key() == Qt::Key_4) light_sample = 4;
    if (event->key() == Qt::Key_5) light_sample = 5;
    if (event->key() == Qt::Key_6) light_sample = 6;

    updateGL(); // обновляем изображение
}
