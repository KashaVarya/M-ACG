#include <QtGui>
#include "mainscene.h"
#include <math.h>
//#include <glext.h>

MainScene::MainScene(QWidget *parent):QGLWidget(parent)
{
    xAxisRotation = yAxisRotation = 0;
}

MainScene::~MainScene()
{
}

void MainScene::initializeGL()
{
    glClearColor(0.4f, 0.36f, 0.88f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MULTISAMPLE);
    generateTextures();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MainScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);

    currentWidth = nWidth;
    currentHeight = nHeight;
}

void MainScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);

    GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };
    GLuint fogfilter= 1;
    GLfloat fogColor[4]= {0.4f, 0.36f, 0.88f, 1.0f};

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, fogMode[fogfilter]);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 1.5f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 100.0f);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    cubeVertexArray[0][0] = 0.0;
    cubeVertexArray[0][1] = 0.0;
    cubeVertexArray[0][2] = 1.0;

    cubeVertexArray[1][0] = 0.0;
    cubeVertexArray[1][1] = 1.0;
    cubeVertexArray[1][2] = 0.5;

    cubeVertexArray[2][0] = 1.0;
    cubeVertexArray[2][1] = 1.0;
    cubeVertexArray[2][2] = 0.5;

    cubeVertexArray[3][0] = 1.0;
    cubeVertexArray[3][1] = 0.0;
    cubeVertexArray[3][2] = 1.0;

    cubeVertexArray[4][0] = 0.0;
    cubeVertexArray[4][1] = 0.0;
    cubeVertexArray[4][2] = 0.0;

    cubeVertexArray[5][0] = 0.0;
    cubeVertexArray[5][1] = 1.0;
    cubeVertexArray[5][2] = 0.5;

    cubeVertexArray[6][0] = 1.0;
    cubeVertexArray[6][1] = 1.0;
    cubeVertexArray[6][2] = 0.5;

    cubeVertexArray[7][0] = 1.0;
    cubeVertexArray[7][1] = 0.0;
    cubeVertexArray[7][2] = 0.0;

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[1][0] = 1.0;
    cubeTextureArray[1][1] = 0.0;

    cubeTextureArray[2][0] = 1.0;
    cubeTextureArray[2][1] = 1.0;

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 3;
    cubeIndexArray[0][2] = 2;
    cubeIndexArray[0][3] = 1;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[1][0] = 1.0;
    cubeTextureArray[1][1] = 0.0;

    cubeTextureArray[5][0] = 1.0;
    cubeTextureArray[5][1] = 1.0;

    cubeTextureArray[4][0] = 0.0;
    cubeTextureArray[4][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 1;
    cubeIndexArray[0][2] = 5;
    cubeIndexArray[0][3] = 4;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
    glBindTexture(GL_TEXTURE_2D, textures[0]);//задняя

    cubeTextureArray[7][0] = 0.0;
    cubeTextureArray[7][1] = 0.0;

    cubeTextureArray[4][0] = 1.0;
    cubeTextureArray[4][1] = 0.0;

    cubeTextureArray[5][0] = 1.0;
    cubeTextureArray[5][1] = 1.0;

    cubeTextureArray[6][0] = 0.0;
    cubeTextureArray[6][1] = 1.0;

    cubeIndexArray[0][0] = 7;
    cubeIndexArray[0][1] = 4;
    cubeIndexArray[0][2] = 5;
    cubeIndexArray[0][3] = 6;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
    glBindTexture(GL_TEXTURE_2D, textures[0]);//правая

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 0.0;

    cubeTextureArray[7][0] = 1.0;
    cubeTextureArray[7][1] = 0.0;

    cubeTextureArray[6][0] = 1.0;
    cubeTextureArray[6][1] = 1.0;

    cubeTextureArray[2][0] = 0.0;
    cubeTextureArray[2][1] = 1.0;

    cubeIndexArray[0][0] = 3;
    cubeIndexArray[0][1] = 7;
    cubeIndexArray[0][2] = 6;
    cubeIndexArray[0][3] = 2;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
    glBindTexture(GL_TEXTURE_2D, textures[0]);//нижняя

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[4][0] = 1.0;
    cubeTextureArray[4][1] = 0.0;

    cubeTextureArray[7][0] = 1.0;
    cubeTextureArray[7][1] = 1.0;

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 4;
    cubeIndexArray[0][2] = 7;
    cubeIndexArray[0][3] = 3;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
}

void MainScene::mousePressEvent(QMouseEvent *event)
{
    pressPosition = event->pos();
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    xAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight);
    yAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth);
    pressPosition = event->pos();
    updateGL();
}

void MainScene::generateTextures()
{
    glGenTextures(1, textures);
    QImage texture1;
    texture1.load(":/img.jpg");
    texture1 = QGLWidget::convertToGLFormat(texture1);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture1.width(), (GLsizei)texture1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}
