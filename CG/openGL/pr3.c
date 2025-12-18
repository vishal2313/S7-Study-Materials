#include<GL/freeglut.h>
#include<GL/gl.h>

void polydisp(){

glClearColor(1.0,0.5,0.5,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.5,1.0,1.0);

glBegin(GL_POLYGON);
 glVertex2f(0.5,0.5);
 glVertex2f(0.5,-0.5);
 glVertex2f(-0.5,0.5);
 glVertex2f(-0.5,-0.5);
glEnd();
glFlush();
}

int main(int argc,char**argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
glutInitWindowSize(800,800);
glutInitWindowPosition(1800,100);
glutCreateWindow("OpenGL3");

glutDisplayFunc(polydisp);

glutMainLoop();
return 0;
}

