#include <iostream>
#include <fstream>
#include <vector>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QPen>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Segment_2.h>

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 600, 400);

    std::ifstream infile("ex1.txt");
    if (!infile) {
        std::cerr << "Error: Could not open ex1.txt\n";
        return 1;
    }

    double x1, y1, x2, y2;
    std::vector<Segment_2> segments;

    // Read each line segment
    while (infile >> x1 >> y1 >> x2 >> y2) {
        segments.push_back(Segment_2(Point_2(x1, y1), Point_2(x2, y2)));
    }

    infile.close();

    // Add each segment to the Qt scene
    QPen pen(Qt::black);
    pen.setWidth(2);
    scene.setBackgroundBrush(Qt::white);

    for (const auto& seg : segments) {
        scene.addLine(QLineF(seg.source().x(), seg.source().y(),
                             seg.target().x(), seg.target().y()), pen);
    }

    // Setup and display the view
    QGraphicsView* view = new QGraphicsView(&scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setWindowTitle("Line Segments Display - CGAL + Qt");
    view->resize(800, 600);

    CGAL::Qt::GraphicsViewNavigation navigation;
    view->installEventFilter(&navigation);
    view->viewport()->installEventFilter(&navigation);

    view->show();
    return app.exec();
}

