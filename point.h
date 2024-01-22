#ifndef POINT_H
#define POINT_H

#include <QGraphicsEllipseItem>
#include <QBrush>

class Point : public QGraphicsEllipseItem
{
public:
    QPoint grid_pos;
    int score;
    Point(int x, int y, int grid_size, int score, int size);
    Point(const Point &point);

    Point& operator=(const Point &point);
};

#endif // POINT_H
