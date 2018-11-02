#ifndef OBJECTGL_H
#define OBJECTGL_H

#include <QGLWidget>
#include <QMouseEvent>

class ObjectOpenGL:public QGLWidget
{
    Q_OBJECT
public:
            ObjectOpenGL(QWidget *parent = 0);  //Конструктор
            ~ObjectOpenGL();                    //Деструктор

public slots:
    void     FrontView(void);       //Стандартний вид: front view
    void     RearView(void);        //Стандартний вид: read view
    void     LeftView(void);        //Стандартний вид: left view
    void     RightView(void);       //Стандартний вид: right view
    void     TopView(void);         //Стандартний вид: top view
    void     BottomView(void);      //Стандартний вид: bottom view
    void     IsometricView(void);   //Стандартний вид: isometric view


    void     SetXRotation(int angle); //Оновити обертання навколо Х
    void     SetYRotation(int angle); //Оновити обертання навколо Y
    void     SetZRotation(int angle); //Оновити обертання навколо Z

protected:
     void    initializeGL();         //Ініціалізація параметрів OpenGL
     void    paintGL();            //Перемалювання сцени

     //Зміна розмірів відкритої GL сцени
     void    resizeGL(int width, int height);

     //Викликається при натисканні миші
     void    mouseMoveEvent(QMouseEvent *event);

     //Викликається при переміщенні миші
     void    mousePressEvent(QMouseEvent *event);

     //Викликається при прокручуванні колеса миші
     void    wheelEvent(QWheelEvent *event);

signals: //Сигнали для нових орієнтацій
     void    xRotationChanged(int angle);
     void    yRotationChanged(int angle);
     void    zRotationChanged(int angle);


private:
     void    Draw_Frame();       //Малювання ортонормального фрейму
     void    NormalizeAngle(int *angle); //Нормований кут між 0 і 360х16

     QColor    BackGround_Color;  //Колір фону
     QColor    Axis_X_Color;      //X осьовий колір
     QColor    Axis_Y_Color;      //Y осьовий колір
     QColor    Axis_Z_Color;      //Z осьовий колір
     QColor    Points_Color;      //Колір точок

     QSize     WindowSize;        //Розмір (у пікселях)вікна OpenGL
     QPoint    LastPos;           //Остання позиція миші (у пікселях)
     GLfloat   dx;          //Переміщення по осі Х (для відображення)
     GLfloat   dy;          //Переміщення по осі Y (для відображення)
     GLfloat   Zoom;        //Маштаб об'єкта

     int       xRot;        //Обертання навколо Х
     int       yRot;        //Обертання навколо Y
     int       zRot;        //Обертання навколо Z

};

#endif // OBJECTGL_H
