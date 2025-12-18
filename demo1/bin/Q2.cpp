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
 
 QPen pen; //
 pen.setColor(Qt::green); //
 
 while(iFile>>p) //
  scene.addEllipse(p.x(),p.y(),5,5,pen,QBrush(Qt::blue)); //
  
 QGraphicsView* view= new QGraphicsView(&scene);
 CGAL::Qt::GraphicsViewNavigation navigation;
 view->installEventFilter(&navigation);
 view->viewport()->installEventFilter(&navigation);
 view->setRenderHint(QPainter::Antialiasing);
 view->show();
 return  app.exec();
 }
