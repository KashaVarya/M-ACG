#include "objectgl.h"

ObjectOpenGL::ObjectOpenGL(QWidget *parent) :
        QGLWidget(parent)
{
BackGround_Color=QColor::fromRgb(50 ,50 ,100);
    Axis_X_Color=QColor::fromRgb(255,0  ,0  ,255);
    Axis_Y_Color=QColor::fromRgb(0  ,255,0  ,255);
    Axis_Z_Color=QColor::fromRgb(0  , 0 ,255,255);
    Points_Color=QColor::fromRgb(0  ,0  ,0  ,255);
IsometricView();
}
ObjectOpenGL::~ObjectOpenGL()
{
    makeCurrent();
}
void ObjectOpenGL::initializeGL()
{
    qglClearColor(BackGround_Color);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glEnable(GL_NORMALIZE);
}
void ObjectOpenGL::paintGL(  )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    GLfloat LightAmbient[]={0.4f,0.4f,0.4f,1.0f};
    GLfloat LightDiffuse[]={0.8f,0.8f,0.8f,1.0f};
    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse);
    int LightPos[4]={0,0,10,1};
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glScalef(1,-1,1);
    Draw_Frame();
    glPushMatrix();
    glScalef(Zoom,Zoom,Zoom);  // створення крапок
       glPointSize(4.0);
    for (double x=-0.25;x<=0.25;x+=0.05)
    {
        for (double y=-0.25;y<=0.25;y+=0.05)
        {
            for (double z=-0.25;z<=0.25;z+=0.05)
            {
                glBegin(GL_POINTS);
                qglColor(Points_Color);
                glVertex3d( x, y ,z);
                glEnd();
            }
        }
    }
    glPopMatrix();

    glViewport(0, 0,WindowSize.width(), WindowSize.height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat Ratio=(GLfloat)WindowSize.width()/(GLfloat)WindowSize.height();
    glOrtho((-0.5+dx)*Ratio,
            ( 0.5+dx)*Ratio ,
            +0.5+dy,
            -0.5+dy,
            -1500.0, 1500.0);
    glMatrixMode(GL_MODELVIEW);
}

void ObjectOpenGL::Draw_Frame()
{
    glDisable(GL_LIGHTING);
    glLineWidth(10.0);
    glBegin(GL_LINES);
    qglColor(Axis_X_Color);
    glVertex3d(0,0,0);
    glVertex3d(0.25, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    qglColor(Axis_Y_Color);
    glVertex3d(0,0,0);
    glVertex3d(0, 0.25, 0);
    glEnd();
    glBegin(GL_LINES);
    qglColor(Axis_Z_Color);
    glVertex3d(0,0,0);
    glVertex3d(0, 0, 0.25);
    glEnd();
    glEnable(GL_LIGHTING);
}
void ObjectOpenGL::FrontView()
{
    SetXRotation(0);
    SetYRotation(0);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::RearView()
{
    SetXRotation(0);
    SetYRotation(180*16);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::LeftView()
{
    SetXRotation(0);
    SetYRotation(90*16);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::RightView()
{
    SetXRotation(0);
    SetYRotation(-90*16);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::TopView()
{
    SetXRotation(-90*16);
    SetYRotation(0);
    SetZRotation(0);
    Zoom=1;
   dx=dy=0;
}

void ObjectOpenGL::BottomView()
{
    SetXRotation(90*16);
    SetYRotation(0);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::IsometricView()
{
    SetXRotation(-45*16);
    SetYRotation(-45*16);
    SetZRotation(0);
    Zoom=1;
    dx=dy=0;
}

void ObjectOpenGL::resizeGL(int width, int height)
{
    WindowSize=QSize(width,height);
}

void ObjectOpenGL::NormalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle >= 360 * 16)
        *angle -= 360 * 16;
}

void ObjectOpenGL::SetXRotation(int angle)
{
    NormalizeAngle(&angle);
    if (angle != xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void ObjectOpenGL::SetYRotation(int angle)
{
    NormalizeAngle(&angle);
    if (angle != yRot)
    {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void ObjectOpenGL::SetZRotation(int angle)
{
    NormalizeAngle(&angle);
    if (angle != zRot)
    {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void ObjectOpenGL::mousePressEvent(QMouseEvent *event){
    if(event->buttons()==Qt::RightButton)
        LastPos = event->pos();
    if(event->buttons()==Qt::LeftButton)
        LastPos = event->pos();
}

void ObjectOpenGL::wheelEvent(QWheelEvent *event)
{
    if(event->delta()<0)
        Zoom/= 1-(event->delta()/120.0)/10.0;
    if(event->delta()>0)
        Zoom*= 1+(event->delta()/120.0)/10.0;
}

void ObjectOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        dx+= -(event->x() - LastPos.x() )/(double)WindowSize.width();
        dy+= -(event->y() - LastPos.y())/(double)WindowSize.height();
        LastPos = event->pos();
    }

    if(event->buttons()==Qt::RightButton)
    {
        int dx_mouse = event->x() - LastPos.x();
        int dy_mouse = event->y() - LastPos.y();
        SetXRotation(xRot - 4 * dy_mouse);
        SetYRotation(yRot + 4 * dx_mouse);
        LastPos = event->pos();
    }
}
