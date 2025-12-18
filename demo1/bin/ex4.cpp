#include <iostream>
#include <fstream>
#include <vector>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 600, 400);  // Adjust window size

    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    double x, y;
    std::vector<Point_2> points;
    while (infile >> x >> y) {
        points.push_back(Point_2(x, y));
    }
    infile.close();

    if (points.size() < 3) {
        std::cerr << "Error: Need at least 3 points for a polygon\n";
        return 1;
    }

    // Create polygon using CGAL
    Polygon_2 polygon;
    for (const auto& p : points)
        polygon.push_back(p);

    // Compute area
    double area = std::abs(polygon.area());
    std::cout << "Area of the polygon: " << area << std::endl;

    // Convert to QPolygonF for display
    QPolygonF qpoly;
    for (const auto& p : points)
        qpoly << QPointF(p.x(), p.y());
    qpoly << QPointF(points[0].x(), points[0].y());  // close polygon

    // Draw polygon
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(QColor(200, 220, 255));  // light blue fill
    scene.addPolygon(qpoly, pen, brush);

    // Display area text at bottom-left
    QString areaText = QString("area = %1").arg(area, 0, 'f', 2);
    QGraphicsTextItem* areaItem = scene.addText(areaText, QFont("Arial", 12, QFont::Bold));
    areaItem->setDefaultTextColor(Qt::black);
    areaItem->setPos(10, 370);  // bottom left

    // Window setup
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle("Polygon Area");
    view.resize(600, 400);
    view.show();

    return app.exec();
}

