#include<iostream>
#include<fstream>
#include<QtGui>
#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<CGAL/Qt/GraphicsViewNavigation.h>
#include<QRectF>
#include<QLineF>
#include<boost/format.hpp>
#include<QBrush>
#include<QPen>
#include<CGAL/Point_2.h>

typedef CGAL::Cartesian<double>K;
typedef K:: Point_2 Point_2;

int main(int argc,char*argv){

Point_2 p;
std::ifstream iFile("input.txt",std::ios::in);

QApplication app(argc,argv);
QGraphicsScene scene;
scene.setSceneRect(0,0,100,100);

//scene.addRect(QRectF(0,0,100,100));
//scene.addLine(QLineF(0,100,100,0));
//scene.addLine(QLineF(0,0,100,100));

//scene.addEllipse(100,100,120,180);

Qpen pen;
pen.setColor(Qt::red);

QBrush brush;
brush.setColor(Qt::blue);

while(iFile>>p)
 scene.addEllipse(p.x(),p.y(),5,5,pen,brush);

QGraphicsView* view = new GraphicsView(&scene);
CGAL::Qt::QGrahicsViewNavigation navigation;
view->installEventFilter (&navigation);
view->viewport()->installEventFilter (&navigation);
view->setRenderHint(QPainter::Antialiasing):
view->show();
return app.exec();
}



