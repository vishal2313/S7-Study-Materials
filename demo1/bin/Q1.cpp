#include<iostream>
#include<QtGui>
#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<CGAL/Qt/GraphicsViewNavigation.h>

int main(int argc, char**argv){
 QApplication app(argc,argv);
 QGraphicsScene scene;
 
 scene.setSceneRect(0,0,500,300);
 
 //add a point in the scene
 scene.addEllipse(100,100,180,120);
 
 QGraphicsView* view= new QGraphicsView(&scene);
 CGAL::Qt::GraphicsViewNavigation navigation;
 view->installEventFilter(&navigation);
 view->viewport()->installEventFilter(&navigation);
 view->setRenderHint(QPainter::Antialiasing);
 view->show();
 return  app.exec();
 }
