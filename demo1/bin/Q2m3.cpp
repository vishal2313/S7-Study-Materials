#include<iostream>
#include<fstream> //
#include<QtGui>
#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<CGAL/Qt/GraphicsViewNavigation.h>
#include<QPen> //
#include<CGAL/Cartesian.h> //
#include<CGAL/Point_2.h> //
#include <cstdlib>//
#include <ctime>//

typedef CGAL::Cartesian<double>K; //
typedef K::Point_2 Point_2; //



int main(int argc, char**argv){

Point_2 p; //
std::ifstream iFile("input.txt",std::ios::in); //

 QApplication app(argc,argv);
 QGraphicsScene scene;
 
 scene.setSceneRect(0,0,500,300);
 
// QPen pen; //
 //pen.setColor(Qt::green); //
 
 int i=0;
 while(iFile>>p) {//
 //QColor color=(i%2==0) ? Qt::blue : Qt::red;
 double size=10+(i%4)*3;
 //QPen pen(Qt::white);
 //QBrush brush (Qt::red);
 
 int r=rand()%256;  
 int g=rand()%256;
 int b=rand()%256;
 QColor color (r,g,b); // this is for different color each
 
 QPen pen(color);
 QBrush brush(color);
 
 scene.addEllipse(p.x(),p.y(),size,size,pen,brush); //
 i++;}
  
 //add a point in the scene
 //scene.addEllipse(100,100,180,120);
 
 QGraphicsView* view= new QGraphicsView(&scene);
 CGAL::Qt::GraphicsViewNavigation navigation;
 view->installEventFilter(&navigation);
 view->viewport()->installEventFilter(&navigation);
 view->setRenderHint(QPainter::Antialiasing);
 view->resize(800, 600); //for resizing window
 view->setBackgroundBrush(Qt::black); // window color
 view->show();
 return  app.exec();
 }
