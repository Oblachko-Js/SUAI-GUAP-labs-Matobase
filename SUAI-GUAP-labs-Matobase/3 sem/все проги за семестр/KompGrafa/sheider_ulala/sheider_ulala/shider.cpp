#include <iostream>
#include <glut.h>
#include <ctime>

// Угол поворота куба и пирамиды
float sceneRotationX = 0.0f;
float sceneRotationY = 0.0f;
float houseRotation = 0.0f;
int prevMouseX, prevMouseY;
bool isRotatingScene = false;
bool isRotatingHouse = false;
bool autoRotateHouse = true; // Флаг для включения/выключения автоматического вращения домика

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Положение источника света

// Функция для вращения всей сцены
void rotateScene(int x, int y) {
    int deltaX = x - prevMouseX;
    int deltaY = y - prevMouseY;
    sceneRotationX += static_cast<float>(deltaY) * 0.5f;
    sceneRotationY += static_cast<float>(deltaX) * 0.5f;
    prevMouseX = x;
    prevMouseY = y;
    glutPostRedisplay();
}

// Функция для вращения домика
void rotateHouse() {
    static clock_t lastTime = clock();

    // Вычисляем прошедшее время с последнего обновления
    clock_t currentTime = clock();
    float deltaTime = static_cast<float>(currentTime - lastTime) / CLOCKS_PER_SEC;
    lastTime = currentTime;

    // Угол вращения домика в градусах в секунду
    float rotationSpeed = 30.0f;

    // Обновляем угол вращения домика
    houseRotation += rotationSpeed * deltaTime;
}

// Функция для автоматического вращения домика
void autoRotateHouseFunc(int value) {
    if (autoRotateHouse) {
        rotateHouse();
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, autoRotateHouseFunc, 0); // Вызываем функцию каждые 1/60 секунды (60 кадров в секунду)
    }
}

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

void drawWall() {
    // Стена (прямоугольник) позади домика
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f); // Серый цвет для стены
    glVertex3f(-6.0f, -2.6f, -1.4f);
    glVertex3f(6.0f, -2.6f, -1.4f);
    glVertex3f(6.0f, 1.6f, -1.4f);
    glVertex3f(-6.0f, 1.6f, -1.4f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Положение источника света
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Положение источника света

    // Включение света и расчет теней
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_DEPTH_TEST);

    // Вращаем всю сцену при взаимодействии с мышью
    if (!autoRotateHouse) {
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f); // Перемещаем объект по Z-оси
        glRotatef(sceneRotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(sceneRotationY, 0.0f, 1.0f, 0.0f);
    }

    // Рисуем стену позади домика
    glPushMatrix(); // Сохраняем текущее состояние матрицы модели
    glLoadIdentity(); // Устанавливаем матрицу модели в начальное состояние
    glTranslatef(0.0f, 0.0f, -5.0f); // Перемещаем объект по Z-оси
    drawWall();
    glPopMatrix(); // Восстанавливаем предыдущее состояние матрицы модели

    // Вращаем и рисуем домик
    glPushMatrix(); // Сохраняем текущее состояние матрицы модели
    glTranslatef(0.0f, 0.0f, -5.0f); // Перемещаем объект по Z-оси
    glRotatef(houseRotation, 0.0f, 1.0f, 0.0f);
    drawHouse();
    glPopMatrix(); // Восстанавливаем предыдущее состояние матрицы модели

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, (float)width / (float)height, 0.1f, 100.0f); // Устанавливаем угол обзора 70.0f

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRotatingScene = true;
            prevMouseX = x;
            prevMouseY = y;
        }
        else if (state == GLUT_UP) {
            isRotatingScene = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRotatingHouse = true;
            prevMouseX = x;
            prevMouseY = y;
        }
        else if (state == GLUT_UP) {
            isRotatingHouse = false;
        }
    }
}

void motion(int x, int y) {
    if (isRotatingScene) {
        rotateScene(x, y);
    }
    else if (isRotatingHouse) {
        int deltaX = x - prevMouseX;
        int deltaY = y - prevMouseY;
        houseRotation += static_cast<float>(deltaX) * 0.5f;
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

    // Включаем автоматическое вращение домика
    glutTimerFunc(1000 / 60, autoRotateHouseFunc, 0);

    glutMainLoop();

    return 0;
}
