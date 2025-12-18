#include<GL/freeglut.h>
#include<math.h>
     
void CircleDisplay(){
 glClear(GL_COLOR_BUFFER_BIT);
 float radius = 0.5f;     
 int num_segments = 100;  

  glBegin(GL_POLYGON);     
  for (int i = 0; i < num_segments; i++){
      float theta = 2.0f * 3.1415926f * i / num_segments; 
      float x = radius * cos(theta); 
      float y = radius * sin(theta); 
      glVertex2f(x, y);   
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(1800,100);
    glutCreateWindow("Drawing a Circle");
    
    glutDisplayFunc(CircleDisplay);
      
    glutMainLoop();
    return 0; 
  }

