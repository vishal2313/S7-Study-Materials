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

typedef CGAL::Cartesian<double>K; //
typedef K::Point_2 Point_2; //



int main(int argc, char**argv){

Point_2 p; //
std::ifstream iFile("input.txt",std::ios::in); //

 QApplication app(argc,argv);
 QGraphicsScene scene;
 
 scene.setSceneRect(0,0,500,300);
 
 //QPen pen; //
// pen.setColor(Qt::green); //
 
 int i=0;
 while(iFile>>p) {//
 QPen pen;
 if(i%2==0)
 pen.setColor(Qt::green);
 else
 pen.setColor(Qt::blue);
 
 scene.addEllipse(p.x(),p.y(),20,20,pen,QBrush(pen.color())); //
 i++;}
  
 //add a point in the scene
 //scene.addEllipse(100,100,180,120);
 
 QGraphicsView* view= new QGraphicsView(&scene);
 CGAL::Qt::GraphicsViewNavigation navigation;
 view->installEventFilter(&navigation);
 view->viewport()->installEventFilter(&navigation);
 view->setRenderHint(QPainter::Antialiasing);
 view->show();
 return  app.exec();
 }
