#include <GL/glut.h>
#include <math.h>

float x_pos = 0.0f, y_pos = 0.0f; 
float x_speed = 0.02f, y_speed = 0.015f; 
float radius = 0.3f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x_pos + radius * cos(angle), y_pos + radius * sin(angle));
    }
    glEnd();
    glutSwapBuffers();
}

void update(int value) {
    x_pos += x_speed;
    y_pos += y_speed;

    if (x_pos + radius > 1.0f || x_pos - radius < -1.0f) x_speed = -x_speed;
    if (y_pos + radius > 1.0f || y_pos - radius < -1.0f) y_speed = -y_speed;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(1800, 100);
    glutCreateWindow("Bouncing Ball Animation");

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

