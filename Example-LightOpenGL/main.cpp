#include <GL/glut.h>
#include <math.h>
#define PI 3.141592653f
int light_sample = 1;

// ініціалізація
void init (void) {
    // кольор фону
    glClearColor (0.3f, 0.3f, 0.3f, 0.0);
    // розрахунок освітлення
    glEnable(GL_LIGHTING);
    // двухсторонній розрахунок освітлення
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    // автоматичне приведення нормалей до
    // одиничної довжини
    glEnable(GL_NORMALIZE);
}

void reshape(int width, int height) {
    // двувимірне вікно виводу
    glViewport(0, 0, width, height);
    // ортогональна проекція
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1, 1);
    // модельна матриця одинична
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void) {
    // очищаемо буфер кадра та глубини
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // властивости материалу
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    // встановлення джерела світла
    if (light_sample == 1) {
        // направлене джерело світла
        GLfloat light0_diffuse[] = {0.4f, 0.7f, 0.2f};
        GLfloat light0_direction[] = {0.0, 0.0, 1.0, 0.0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    }
    if (light_sample == 2) {
        // точкове джерело світла
        // спадання інтенсивності з відстанню відключено (за замовчуванням)
        GLfloat light1_diffuse[] = {0.4f, 0.7f, 0.2f};
        GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    }
    if (light_sample == 3) {
        // точкове джерело світла
        // спадання інтенсивності з відстанню задано функциею f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
        GLfloat light2_diffuse[] = {0.4f, 0.7f, 0.2f};
        GLfloat light2_position[] = {0.0, 0.0, 1.0, 1.0};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4f);
    }
    if (light_sample == 4) {
        // прожектор
        // спадання інтенсивності з відстанню відключено (за замовчуванням)
        // половина кута при вершині 30 градусів
        // напрямок на центр поверхні
        GLfloat light3_diffuse[] = {0.4f, 0.7f, 0.2f};
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
        GLfloat light4_diffuse[] = {0.4f, 0.7f, 0.2f};
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
    // поверхня
    GLfloat x, y;
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    for (x = -1.0; x < 1.0f; x += 0.005) {
        for (y = -1.0; y < 1.0f; y += 0.005) {
            glVertex3f(x, y, 0.0);
            glVertex3f(x, y + 0.005f, 0.0);
            glVertex3f(x + 0.005f, y + 0.005f, 0.0);
            glVertex3f(x + 0.005f, y, 0.0);
        }
    }
    glEnd();
    // відключення джерел світла
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
    // елемент подвійної буферизації
    glutSwapBuffers();
}
void keyboard_function(unsigned char key, int x, int y) {
    if (key == '1') light_sample = 1;
    if (key == '2') light_sample = 2;
    if (key == '3') light_sample = 3;
    if (key == '4') light_sample = 4;
    if (key == '5') light_sample = 5;
    if (key == '6') light_sample = 6;
    glutPostRedisplay();
}
int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (500, 500);
    glutCreateWindow ("An example of installing light sources in OpenGL");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard_function);
    glutMainLoop ();
}
