#ifndef MAP_H
#define MAP_H

#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <fstream>
#include <QFile>

class Map : public QGraphicsPixmapItem
{
public:
    int width;
    int height;
    int grid_size;
    int **walls;
    Map(int width, int height, int grid_size, QString path);
    ~Map();

    QPoint normalize_point(const QPoint &point);
    bool is_in_bound(const QPoint &point);
    void randomFill(double propability);
    void load_layout(QString path);
    bool is_crossing(int x, int y);
};

#endif // MAP_H
