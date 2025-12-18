#include<iostream>
#include<fstream>
#include<QtGui>
#include<QApplication>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<CGAL/Qt/GraphicsViewNavigation.h>

int main(int argc,char**argv){
 QApplication app(argc,argv);
 QGraphicsScene scene;
 scene.setSceneRect(0,0,300,300);
 
 QPen pen;
 pen.setColor(QColor(255,165,0));
 pen.setWidth(2);
 
 scene.addLine(QLineF(20,30,250,200),pen);
 scene.addLine(QLineF(30,30,260,200),pen); // this is for making a parallel line
 
 QGraphicsView* view = new QGraphicsView(&scene);
 CGAL::Qt::GraphicsViewNavigation navigation;
 view->installEventFilter(&navigation);
 view->viewport()->installEventFilter(&navigation);
 view->setRenderHint(QPainter::Antialiasing);
 view->show();
 return app.exec();
 }

