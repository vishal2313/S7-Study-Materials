#include<GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>

 GLfloat r=0.0,g=0.0,b=0.0,a=0.0;

void render function(){
int i=0;
glClearColor(r,g,b,a);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,1.0,0.0);
glPointSize(5);
glFlush();
}

void mykeyboard function(unsingned char key,int x,int y){
 switch(key){
  case 'r':
  r=1.0,g=0.0,b=0.0,a=1.0;
  glClearColor(r,g,b,a);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  break;
  case 'g':
  r=0.0,g=0.0,b=1.0,a=1.0;
  glClearColor(r,g,b,a);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  break;
  case 'y':
  r=1.0,g=1.0,b=0.0,a=1.0;
  glClearColor(r,g,b,a);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  break;
  default:break;
  };
}  

int main(int argc,char**argv){
glutInit(&argc,argv);
glutInitDisplayMode(GL_COLOR_BUFFER_BIT);
glutInitWindowSize(800,800);
glutInitWindowPosition(1800,100);

glutCreateWindow("Window Color Change");

glutDisplayFunc(render function);
glutKeyboardFunc(myKeyboard function);

glutMainLoop();
return 0;
}

