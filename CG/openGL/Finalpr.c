#include<GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>
#include<math.h>

GLfloat r=0.0,g=0.0,b=0.0,a=0.0;


struct Point{
 GLfloat x,y,z;
};

struct Point p[100000];
int cnt=0;

void readInput(){
FILE*fptr=fopen("input.txt","r");
if(fptr){
 while(fscanf(fptr,"%f %f %f",&p[cnt].x,&p[cnt].y,&p[cnt].z)==3){
 cnt++;
 }
 fclose(fptr);
 }
 else{
  printf("input.txt couldn't find\n");
   }
  }
  
void renderfunction(){
 glClearColor(0.0,0.0,0.0,0.0);
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0,0.0,1.0);
 
 glBegin(GL_POLYGON);
 for(int i=0;i<cnt;i++){
 glVertex3f(p[i].x,p[i].y,p[i].z);
 }
 glEnd();
 
 glFlush();
 }
 
 int main(int argc,char**argv){
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA|GLUT_DEPTH);
 glutInitWindowSize(800,800);
 glutInitWindowPosition(1800,100);
 readInput();
 glutCreateWindow("input read");
 glEnable(GL_DEPTH_TEST);
 glutDisplayFunc(renderfunction);
 glutMainLoop();
 return 0;
 }
