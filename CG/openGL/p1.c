#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;  // default white

void readInput() {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr) {
        if (fscanf(fptr, "%f %f %f %f", &r, &g, &b, &a) != 4) {
            printf("Invalid format in input.txt. Using default white.\n");
            r = g = b = a = 1.0f;
        }
        fclose(fptr);
    } else {
        printf("Could not open input.txt. Using default white.\n");
    }
}

void renderfunction() {
    glClearColor(r, g, b, a);  // background color from file
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 100);

    readInput();  // read RGBA values

    glutCreateWindow("Background Color from File");
    glutDisplayFunc(renderfunction);
    glutMainLoop();
    return 0;
}

