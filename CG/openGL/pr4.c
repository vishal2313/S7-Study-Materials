#include <GL/freeglut.h>
#include <math.h>

void CircleDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);   // clear window

    float radius = 0.5f;     // circle radius
    int num_segments = 100;  // number of points

    // Step 1: Filled circle (orange)
    glColor3f(1.0, 0.5, 0.0); // orange (R=1, G=0.5, B=0)
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Step 2: Circle boundary (green)
    glColor3f(0.0, 1.0, 0.0); // green
    glLineWidth(3.0);         // make boundary thicker
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle with Orange Fill and Green Border");

    glClearColor(1.0, 1.0, 1.0, 1.0); // background = white
    glutDisplayFunc(CircleDisplay);

    glutMainLoop();
    return 0;
}

