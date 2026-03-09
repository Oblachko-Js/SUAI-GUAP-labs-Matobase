#include <iostream>
#include <glut.h>

// Угол поворота куба и пирамиды
float angleX = 0.0f;
float angleY = 0.0f;
int prevMouseX, prevMouseY;
bool isRotating = false;

void drawHouse() {
    // Основание домика (квадрат)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f); // Коричневый цвет
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    // Стены домика (четыре стены)
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f); // Серый цвет
    glVertex3f(-0.8f, -1.0f, -0.8f);
    glVertex3f(0.8f, -1.0f, -0.8f);
    glVertex3f(0.8f, 0.6f, -0.8f);
    glVertex3f(-0.8f, 0.6f, -0.8f);

    glVertex3f(-0.8f, -1.0f, 0.8f);
    glVertex3f(0.8f, -1.0f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(-0.8f, 0.6f, 0.8f);

    glVertex3f(-0.8f, -1.0f, -0.8f);
    glVertex3f(-0.8f, -1.0f, 0.8f);
    glVertex3f(-0.8f, 0.6f, 0.8f);
    glVertex3f(-0.8f, 0.6f, -0.8f);

    glVertex3f(0.8f, -1.0f, -0.8f);
    glVertex3f(0.8f, -1.0f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(0.8f, 0.6f, -0.8f);
    glEnd();

    // Крыша (пирамида)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.2f, 0.2f); // Красный цвет
    // Боковые грани пирамиды
    glVertex3f(-0.8f, 0.6f, -0.8f);
    glVertex3f(0.8f, 0.6f, -0.8f);
    glVertex3f(0.0f, 1.6f, 0.0f);

    glVertex3f(-0.8f, 0.6f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(0.0f, 1.6f, 0.0f);

    // Добавляем еще две боковые грани
    glVertex3f(-0.8f, 0.6f, -0.8f);
    glVertex3f(0.0f, 1.6f, 0.0f);
    glVertex3f(-0.8f, 0.6f, 0.8f);

    glVertex3f(0.8f, 0.6f, -0.8f);
    glVertex3f(0.0f, 1.6f, 0.0f);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f); // Перемещаем объект по Z-оси
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawHouse();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRotating = true;
            prevMouseX = x;
            prevMouseY = y;
        }
        else if (state == GLUT_UP) {
            isRotating = false;
        }
    }
}

void motion(int x, int y) {
    if (isRotating) {
        int deltaX = x - prevMouseX;
        int deltaY = y - prevMouseY;
        angleX += static_cast<float>(deltaY) * 0.5f;
        angleY += static_cast<float>(deltaX) * 0.5f;
        prevMouseX = x;
        prevMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D House");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
