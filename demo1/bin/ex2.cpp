#include <iostream>
#include <fstream>
#include <vector>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <CGAL/Cartesian.h>
#include <CGAL/Segment_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <boost/variant.hpp>

typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    std::ifstream infile("ex2.txt");
    if (!infile) {
        std::cerr << "Error: Could not open ex2.txt\n";
        return 1;
    }

    std::vector<Segment_2> segments;
    double x1, y1, x2, y2;

    while (infile >> x1 >> y1 >> x2 >> y2)
        segments.push_back(Segment_2(Point_2(x1, y1), Point_2(x2, y2)));
    infile.close();

    std::cout << "Intersection Results:\n";

    // Check all pairs and show each in separate window
    for (size_t i = 0; i < segments.size(); ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {

            // New scene per pair
            QGraphicsScene* scene = new QGraphicsScene();
            scene->setBackgroundBrush(Qt::white);
            scene->setSceneRect(0, 0, 400, 300);

            QPen segPen(Qt::black);
            segPen.setWidth(2);

            // Draw both segments
            scene->addLine(QLineF(segments[i].source().x(), segments[i].source().y(),
                                  segments[i].target().x(), segments[i].target().y()), segPen);

            scene->addLine(QLineF(segments[j].source().x(), segments[j].source().y(),
                                  segments[j].target().x(), segments[j].target().y()), segPen);

            // Text info to display below
            QString info = QString("%1 - %2\n").arg(i + 1).arg(j + 1);

            auto result = CGAL::intersection(segments[i], segments[j]);
            std::cout << "Segment " << i + 1 << " & Segment " << j + 1 << ": ";

            QPen interPen(Qt::red);
            interPen.setWidth(5);

            if (result) {
                if (const Point_2* p = boost::get<Point_2>(&*result)) {
                    std::cout << "Yes, Intersection at (" << p->x() << ", " << p->y() << ")\n";

                    info += "Lines Intersect\n";
                    info += QString("Lines intersect at (%.2f,%.2f)").arg(p->x()).arg(p->y());

                    // Draw intersection point
                    scene->addEllipse(p->x() - 3, p->y() - 3, 6, 6,
                                      interPen, QBrush(Qt::red));
                } else {
                    std::cout << "Yes, overlapping segments\n";
                    info += "Lines Overlap (infinite intersection)";
                }
            } else {
                std::cout << "No\n";
                info += "Lines do not intersect";
            }

            // Add text at bottom center
            QGraphicsTextItem* text = scene->addText(info);
            text->setDefaultTextColor(Qt::black);
            text->setPos(20, 250);

            // Create and show a window for this pair
            QGraphicsView* view = new QGraphicsView(scene);
            view->setRenderHint(QPainter::Antialiasing);
            view->resize(400, 300);
            view->setWindowTitle("int_lines");
            view->show();
        }
    }

    return app.exec();
}

