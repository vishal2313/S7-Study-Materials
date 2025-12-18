#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

struct Point {
    GLfloat x, y;
};

struct Point p[100000];
int cnt = 0;

void readInput() {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr) {
        while (fscanf(fptr, "%f %f", &p[cnt].x, &p[cnt].y) == 2) {
            cnt++;
        }
        fclose(fptr);
    } else {
        printf("Could not open input.txt\n");
    }
}

void renderFunction() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);  // Black lines
    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < cnt; i++) {
        glVertex2f(p[i].x, p[i].y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 100);

    readInput();

    glutCreateWindow("Line Strip from File");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}

