#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

struct Point {
    GLfloat x, y;
};

struct Point p[1000];
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

    glColor3f(0.0, 0.0, 0.0);  // Black color
    glLineWidth(2.0);

    // Draw polygon edges
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < cnt; i++) {
        glVertex2f(p[i].x, p[i].y);
    }
    glEnd();

    // Draw diagonals (all pairs of non-adjacent vertices)
    glBegin(GL_LINES);
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            // skip adjacent vertices and the edge between last and first
            if (j == i + 1 || (i == 0 && j == cnt - 1)) continue;
            glVertex2f(p[i].x, p[i].y);
            glVertex2f(p[j].x, p[j].y);
        }
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

    glutCreateWindow("Convex Polygon with Diagonals");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}

