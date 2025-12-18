#include <iostream>
#include <fstream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Segment_2.h>
#include <CGAL/intersections.h>
#include <QtGui>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <CGAL/Qt/GraphicsViewNavigation.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;

int main(int argc, char** argv) {
    std::ifstream iFile("lines.txt", std::ios::in);
    if (!iFile) {
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    // Read line segments
    std::vector<Segment_2> segments;
    double x1, y1, x2, y2;
    while (iFile >> x1 >> y1 >> x2 >> y2) {
        segments.push_back(Segment_2(Point_2(x1, y1), Point_2(x2, y2)));
    }

    // Qt setup
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 600, 400);

    QPen linePen(Qt::blue);
    linePen.setWidth(2);

    QPen intersectPen(Qt::red);
    QBrush intersectBrush(Qt::red);

    // Draw all line segments
    for (auto& seg : segments) {
        scene.addLine(CGAL::to_double(seg.source().x()),
                      CGAL::to_double(seg.source().y()),
                      CGAL::to_double(seg.target().x()),
                      CGAL::to_double(seg.target().y()),
                      linePen);
    }

    // Check all pairs for intersection
    std::cout << "Checking intersections:\n";
    for (size_t i = 0; i < segments.size(); ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {
            auto result = CGAL::intersection(segments[i], segments[j]);
            if (result) {
                // Intersection found
                std::cout << "Segment " << i + 1 << " and Segment " << j + 1 << ": YES\n";

                if (const Point_2* ip = boost::get<Point_2>(&*result)) {
                    std::cout << "   Intersection Point: ("
                              << CGAL::to_double(ip->x()) << ", "
                              << CGAL::to_double(ip->y()) << ")\n";

                    // Draw intersection point in red
                    scene.addEllipse(CGAL::to_double(ip->x()) - 3,
                                     CGAL::to_double(ip->y()) - 3,
                                     6, 6, intersectPen, intersectBrush);
                } else {
                    std::cout << "   Overlapping segments (infinite intersections)\n";
                }
            } else {
                std::cout << "Segment " << i + 1 << " and Segment " << j + 1 << ": NO\n";
            }
        }
    }

    // View setup
    QGraphicsView* view = new QGraphicsView(&scene);
    CGAL::Qt::GraphicsViewNavigation navigation;
    view->installEventFilter(&navigation);
    view->viewport()->installEventFilter(&navigation);
    view->setRenderHint(QPainter::Antialiasing);
    view->show();

    return app.exec();
}

