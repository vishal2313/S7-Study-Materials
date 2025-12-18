#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

struct Point {
    GLfloat x, y, z;
};

struct Point p[1000];
int cnt = 0;

void readInput() {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr) {
        while (fscanf(fptr, "%f %f %f", &p[cnt].x, &p[cnt].y, &p[cnt].z) == 3) {
            cnt++;
        }
        fclose(fptr);
    } else {
        printf("Could not open input.txt\n");
    }
}

void renderFunction() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);  // Red color

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < cnt; i++) {
        glVertex3f(p[i].x, p[i].y, p[i].z);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 100);

    readInput();

    glutCreateWindow("Rectangular Strip");
    glEnable(GL_DEPTH_TEST);   // Enable Z-buffer
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}

