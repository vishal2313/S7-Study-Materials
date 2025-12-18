#include <iostream>
#include <fstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QBrush>
#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 500, 400); // default background (light gray)

    std::ifstream infile("ex3.txt");
    if (!infile) {
        std::cerr << "Error: Could not open ex3.txt\n";
        return 1;
    }

    double x, y;
    std::vector<Point_2> points;
    while (infile >> x >> y) {
        points.push_back(Point_2(x, y));
    }
    infile.close();

    if (points.size() != 3) {
        std::cerr << "Error: input.txt must contain exactly 3 points\n";
        return 1;
    }

    // Create triangle polygon
    Polygon_2 triangle;
    for (const auto& p : points)
        triangle.push_back(p);

    // Compute absolute area
    double area = std::abs(triangle.area());
    std::cout << "Area of the triangle: " << area << std::endl;

    // Draw triangle
    QPolygonF qpoly;
    for (const auto& p : points)
        qpoly << QPointF(p.x(), p.y());
    qpoly << QPointF(points[0].x(), points[0].y()); // close shape

    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::cyan);
    scene.addPolygon(qpoly, pen, brush);

    // Display area text at bottom-left
    QString areaText = QString("Area = %1").arg(area, 0, 'f', 2);
    QGraphicsTextItem* textItem = scene.addText(areaText, QFont("Arial", 14, QFont::Bold));
    textItem->setDefaultTextColor(Qt::red);

    // Place text at bottom-left of the window
    QRectF rect = scene.sceneRect();
    textItem->setPos(rect.left() + 10, rect.bottom() - 40); // adjust offset if needed

    // Show window
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle("Triangle Area - CGAL + Qt");
    view.resize(500, 400);
    view.show();

    return app.exec();
}

