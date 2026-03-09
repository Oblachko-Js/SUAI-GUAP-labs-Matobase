#include <iostream>
#include <glut.h>

// Угол поворота куба и пирамиды
float angleX = 0.0f;
float angleY = 0.0f;
int prevMouseX, prevMouseY;
bool isRotating = false;

GLfloat light_position[] = { 0.0f, 2.0f, 0.0f, 1.0f }; // Позиция света (выше дома)
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Фоновое освещение
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Рассеянное освещение
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Зеркальное освещение

GLfloat shadow_matrix[16]; // Матрица для проецирования теней

float houseRotationSpeed = 0.5f;  // Скорость вращения дома

void drawHouse() {
    // Основание домика (квадрат)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f); // Коричневый цвет
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glEnd();

    // Стены домика (четыре стены)
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f); // Серый цвет
    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 1.4f, -0.8f);
    glVertex3f(-0.8f, 1.4f, -0.8f);

    glVertex3f(-0.8f, 0.0f, 0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(0.8f, 1.4f, 0.8f);
    glVertex3f(-0.8f, 1.4f, 0.8f);

    glVertex3f(-0.8f, 0.0f, -0.8f);
    glVertex3f(-0.8f, 0.0f, 0.8f);
    glVertex3f(-0.8f, 1.4f, 0.8f);
    glVertex3f(-0.8f, 1.4f, -0.8f);

    glVertex3f(0.8f, 0.0f, -0.8f);
    glVertex3f(0.8f, 0.0f, 0.8f);
    glVertex3f(0.8f, 1.4f, 0.8f);
    glVertex3f(0.8f, 1.4f, -0.8f);
    glEnd();

    // Крыша (пирамида)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.2f, 0.2f); // Красный цвет
    // Боковые грани пирамиды
    glVertex3f(-0.8f, 1.4f, -0.8f);
    glVertex3f(0.8f, 1.4f, -0.8f);
    glVertex3f(0.0f, 2.4f, 0.0f);

    glVertex3f(-0.8f, 1.4f, 0.8f);
    glVertex3f(0.8f, 1.4f, 0.8f);
    glVertex3f(0.0f, 2.4f, 0.0f);

    // Добавляем еще две боковые грани
    glVertex3f(-0.8f, 1.4f, -0.8f);
    glVertex3f(0.0f, 2.4f, 0.0f);
    glVertex3f(-0.8f, 1.4f, 0.8f);

    glVertex3f(0.8f, 1.4f, -0.8f);
    glVertex3f(0.0f, 2.4f, 0.0f);
    glVertex3f(0.8f, 1.4f, 0.8f);
    glEnd();
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Материал дома
    GLfloat house_ambient[] = { 0.5f, 0.35f, 0.05f, 1.0f };
    GLfloat house_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat house_specular[] = { 0.8f, 0.2f, 0.2f, 1.0f };
    GLfloat house_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, house_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, house_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, house_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, house_shininess);
}

void calculateShadowMatrix() {
    // Рассчитываем матрицу проецирования теней
    GLfloat plane[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Плоскость стены
    GLfloat dot = plane[0] * light_position[0] + plane[1] * light_position[1] +
        plane[2] * light_position[2] + plane[3] * light_position[3];

    shadow_matrix[0] = dot - light_position[0] * plane[0];
    shadow_matrix[4] = -light_position[0] * plane[1];
    shadow_matrix[8] = -light_position[0] * plane[2];
    shadow_matrix[12] = -light_position[0] * plane[3];

    shadow_matrix[1] = -light_position[1] * plane[0];
    shadow_matrix[5] = dot - light_position[1] * plane[1];
    shadow_matrix[9] = -light_position[1] * plane[2];
    shadow_matrix[13] = -light_position[1] * plane[3];

    shadow_matrix[2] = -light_position[2] * plane[0];
    shadow_matrix[6] = -light_position[2] * plane[1];
    shadow_matrix[10] = dot - light_position[2] * plane[2];
    shadow_matrix[14] = -light_position[2] * plane[3];

    shadow_matrix[3] = -light_position[3] * plane[0];
    shadow_matrix[7] = -light_position[3] * plane[1];
    shadow_matrix[11] = -light_position[3] * plane[2];
    shadow_matrix[15] = dot - light_position[3] * plane[3];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f); // Перемещаем объект по Z-оси
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    setupLighting(); // Устанавливаем настройки освещения

    // Рисуем стену и тень
    calculateShadowMatrix();
    glPushMatrix();
    glMultMatrixf(shadow_matrix);
    drawHouse();
    glPopMatrix();

    glPushMatrix();  // Сохраняем текущую матрицу модели
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);  // Вращение только для дома
    drawHouse();
    glPopMatrix();  // Восстанавливаем матрицу модели

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

void updateHouse(int value) {
    angleY += houseRotationSpeed; // Угол вращения дома
    if (angleY > 360.0f)
        angleY -= 360.0f;

    glutPostRedisplay();  // Вызываем функцию display() для перерисовки
    glutTimerFunc(10, updateHouse, 0);  // Устанавливаем таймер для обновления
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

    glutTimerFunc(10, updateHouse, 0);  // Устанавливаем таймер для автоматического вращения дома

    glutMainLoop();

    return 0;
}