#ifndef MY_PAINT_H
#define MY_PAINT_H

#include <QtGui>
#include <QGLWidget>

class My_Paint : public QGLWidget
{
private:
    int r;
    int g;
    int b;
    GLfloat angle = 0;// Кут повороту літер
    int xRotation,
    yRotation,
    zRotation,
    scale; // переменные поворота и масштаба
    QPoint mousePos; // переменная для запоминания позиции нажатия мышки
        void drawAxis();

public:
    My_Paint(QWidget *parent = 0);

protected:
    void initializeGL();
    //void initializeGL(QColor rgb);
    void paintGL();
    void resizeGL(int w, int h);
    void scene();
    void mousePressEvent(QMouseEvent*);   // нажатие на клавишу мыши
    void mouseMoveEvent(QMouseEvent*);    // перемещение мыши
    void mouseReleaseEvent(QMouseEvent*); // отжатие клавиши мыши
    void wheelEvent(QWheelEvent *);          // вращение колесика
    void keyPressEvent(QKeyEvent*e);

};

#endif // MY_PAINT_H
