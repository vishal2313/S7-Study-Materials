#include<GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>

struct Point{
   GLfloat x,y;
};

struct Point p[100000];
int cnt=0;

void readInput(){
 FILE* fptr=fopen("input.txt","r");
 if(fptr){
  while(fscanf(fptr,"%f %f",&(p[cnt].x),&(p[cnt].y))!=EOF){
   cnt++;
  }
   fclose(fptr);
  }
}
  
void renderfunction(){
int i=0;
glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,1.0,0.0);
glPointSize(3);

glBegin(GL_POINTS);
while(i<cnt){
 glVertex2f(p[i].x,p[i].y);
 i++;
 }
 
 glEnd();
 glFlush();
 }
  
int main(int argc,char**argv){
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE);
 glutInitWindowSize(800,800);
 glutInitWindowPosition(1800,100);
 
 readInput();
 glutCreateWindow("readInput");
 glutDisplayFunc(renderfunction);
 glutMainLoop();
 return 0;
 }
 

 
