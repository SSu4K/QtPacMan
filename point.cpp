#include "point.h"

Point::Point(int x, int y, int grid_size, int score, int size)
{
    grid_pos = QPoint(x, y);
    this->score = score;
    setBrush(Qt::white);
    setRect(grid_size*(x+0.5)-size/2, grid_size*(y+0.5)-size/2, size, size);
}

Point::Point(const Point &point) {
    setBrush(point.brush());
    grid_pos = point.grid_pos;
    score = point.score;
    setRect(point.rect());
}


Point& Point::operator=(const Point &point){
    setBrush(point.brush());
    grid_pos = point.grid_pos;
    score = point.score;
    setRect(point.rect());
    return *this;
}
