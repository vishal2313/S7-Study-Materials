#include<iostream>
#include<fstream>
#include<QtGui>
#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<CGAL/Qt/GraphicsViewNavigation.h>
#include<CGAL/Cartesian.h>
#include<CGAL/Point_2.h>

typedef CGAL::Cartesian<double>K;
typedef K::Point_2 Point_2;

int main(int argc,char**argv){

QApplication app(argc,argv);
QGraphicsScene scene;
scene.setSceneRect(0,0,500,300);

//polygon1
std::ifstream iFile("input.txt",std::ios::in);
Point_2 p1;
QPolygonF polygon1;
QPen pen1(Qt::red);

while(iFile>>p1)
 polygon1<<QPointF(p1.x(),p1.y());

scene.addPolygon(polygon1,pen1);

//polygon2
std::ifstream iFile2("input2.txt",std::ios::in);
Point_2 p2;
QPolygonF polygon2;

QPen pen2(Qt::green);
while(iFile2>>p2)
 polygon2<<QPointF(p2.x(),p2.y());
 
scene.addPolygon(polygon2,pen2);

QGraphicsView* view=new QGraphicsView(&scene);
CGAL::Qt::GraphicsViewNavigation navigation;
view->installEventFilter(&navigation);
view->viewport()->installEventFilter(&navigation);
view->setRenderHint(QPainter::Antialiasing);
view->show();
return app.exec();
}








