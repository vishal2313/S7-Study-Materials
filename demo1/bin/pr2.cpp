// polygon_triangles.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygonF>
#include <QBrush>
#include <QPen>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Timer.h>

// Face info to mark inside/outside
struct FaceInfo2 {
  int nesting_level;
  bool in_domain() const { return nesting_level % 2 == 1; }
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, 
          CGAL::Default, CGAL::Default, FaceInfo2>                 CDT;
typedef K::Point_2                                                 Point;
typedef CGAL::Polygon_2<K>                                         Polygon_2;
typedef CDT::Face_handle                                           Face_handle;
typedef CDT::Vertex_handle                                         Vertex_handle;

// Marks facets that are inside the polygon domain by BFS
void mark_domains(CDT& ct) {
    for (auto f = ct.all_faces_begin(); f != ct.all_faces_end(); ++f)
        f->info().nesting_level = -1;

    std::list<CDT::Face_handle> queue;
    // Start from infinite faces
    for (auto f = ct.all_faces_begin(); f != ct.all_faces_end(); ++f) {
        if (ct.is_infinite(f)) {
            f->info().nesting_level = 0;
            queue.push_back(f);
        }
    }
    while (!queue.empty()) {
        CDT::Face_handle fh = queue.front();
        queue.pop_front();
        for (int i = 0; i < 3; ++i) {
            CDT::Face_handle neighbor = fh->neighbor(i);
            if (neighbor->info().nesting_level == -1) {
                // if the edge fh - neighbor is constrained, don't cross
                if (!ct.is_constrained(std::make_pair(fh, i))) {
                    neighbor->info().nesting_level = fh->info().nesting_level;
                    queue.push_back(neighbor);
                } else {
                    // crossing a constrained edge -> inside region
                    neighbor->info().nesting_level = fh->info().nesting_level + 1;
                    queue.push_back(neighbor);
                }
            }
        }
    }
}

// Helper to get three triangle points if face is inside domain
bool face_is_inside_and_triangle(CDT::Face_handle f) {
    return f->info().in_domain() && !f->is_infinite();
}

int main(int argc, char** argv) {
    // Read polygon vertices from "polygon.txt"
    std::ifstream infile("polygon.txt");
    if (!infile) {
        std::cerr << "Error: cannot open polygon.txt (format: one vertex per line: x y)\n";
        return 1;
    }

    std::vector<Point> pts;
    double x, y;
    while (infile >> x >> y) {
        pts.emplace_back(x, y);
    }
    if (pts.size() < 3) {
        std::cerr << "Need at least 3 points for a polygon\n";
        return 1;
    }

    // Build CGAL polygon and compute area
    Polygon_2 polygon;
    for (auto &pt : pts) polygon.push_back(pt);

    double area = std::abs(polygon.area()); // signed area -> abs for magnitude
    std::cout << "Polygon area = " << area << "\n";

    // Build constrained Delaunay triangulation with polygon edges as constraints
    CDT cdt;
    std::vector<Vertex_handle> vhandles;
    vhandles.reserve(pts.size());
    for (auto &p: pts) vhandles.push_back(cdt.insert(p));
    // insert constraints between consecutive vertices (and closing edge)
    for (size_t i = 0; i < vhandles.size(); ++i) {
        size_t j = (i + 1) % vhandles.size();
        cdt.insert_constraint(vhandles[i], vhandles[j]);
    }

    // Mark interior faces
    mark_domains(cdt);

    // Prepare Qt application and scene
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    // Random color generator (but deterministic seed so repeatable)
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> col(50, 230);

    // Draw triangles (faces inside domain)
    for (auto fit = cdt.finite_faces_begin(); fit != cdt.finite_faces_end(); ++fit) {
        if (!face_is_inside_and_triangle(fit)) continue;

        QPointF p0( CGAL::to_double(fit->vertex(0)->point().x()),
                    CGAL::to_double(fit->vertex(0)->point().y()) );
        QPointF p1( CGAL::to_double(fit->vertex(1)->point().x()),
                    CGAL::to_double(fit->vertex(1)->point().y()) );
        QPointF p2( CGAL::to_double(fit->vertex(2)->point().x()),
                    CGAL::to_double(fit->vertex(2)->point().y()) );

        QPolygonF tri;
        tri << p0 << p1 << p2;

        QColor color(col(rng), col(rng), col(rng));
        QBrush brush(color);
        QPen pen(Qt::black);
        pen.setWidth(1);

        scene.addPolygon(tri, pen, brush);
    }

    // Optionally draw polygon outline in thick black pen
    QPolygonF outline;
    for (auto &p : pts) outline << QPointF(CGAL::to_double(p.x()), CGAL::to_double(p.y()));
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    scene.addPolygon(outline, outlinePen, QBrush(Qt::NoBrush));

    // Show vertices as small black dots
    for (auto &p : pts) {
        double px = CGAL::to_double(p.x());
        double py = CGAL::to_double(p.y());
        scene.addEllipse(px - 2.5, py - 2.5, 5, 5, QPen(Qt::black), QBrush(Qt::black));
    }

    QGraphicsView* view = new QGraphicsView(&scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->resize(900, 700);
    view->show();

    return app.exec();
}

