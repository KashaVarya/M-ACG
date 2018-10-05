#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glx.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <iostream>
#include <GL/glcorearb.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void LoadTextures()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("egypt.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);

    glColor3f (0.3f, 0.3f, 0.6f);
    glTexCoord2f(0.0,0.0);
    glVertex2f(-3.0, -3.0);

    glColor3f (0.0f, 0.9f, 1.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(-3.0, 3.0);

    glColor3f (1.0, 1.0, 0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(3.0, 3.0);

    glColor3f (0.0, 0.9f, 1.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(3.0, -3.0);

    glEnd();

    glFlush();
}

void Initialize()
{
    LoadTextures();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0,3.0,-3.0,3.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Square_egypt_hieroglyphs");
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Initialize();
    glutDisplayFunc(Draw);
    glutMainLoop();
}
