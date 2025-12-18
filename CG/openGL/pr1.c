#include<GL/freeglut.h>
#include<GL/gl.h>

int main(int argc,char**argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
glutInitWindowSize(800,800);
glutInitWindowPosition(1800,100);
glutCreateWindow("OpenGL");
glutMainLoop();
return 0;
}
