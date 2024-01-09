#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "spritesheetreader.h"
#include "map.h"

class Sprite : public QGraphicsPixmapItem
{
protected:
    std::vector<QPixmap> images;
    Map *map;
    int size;
    int grid_size;
    int offset;
    enum Sprites type;
    int age;
    int state;
    int direction;

    QPoint grid_pos;
    QPoint center_pos;
    void snap_to_grid();
    void set_image(int image);

public:
    Sprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y);
    virtual void update_image();
    void set_grid_pos(int x, int y);
    void advance(int phase);
    static QPoint directionToVec(const int direction);

    QPoint get_grid_pos() const;
};

class MovingSprite : public Sprite{
protected:
    double speed;
    int next_direction;
    bool freeze;
    void move(QPoint vec);
    virtual int get_next_direction();

public:
    MovingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y);
    void keyPressEvent(QKeyEvent *event);
    bool check_collision(int direction);
    void advance(int phase);
};

#endif // SPRITE_H
