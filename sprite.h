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
    double size;
    int grid_size;
    //enum Sprites type;
    int age;
    int state;
    int direction;

    QPoint grid_pos;
    QPointF center_pos;
    void snap_to_grid();
    void set_image(int image);

public:
    Sprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y);
    Sprite(const Sprite &);
    Sprite& operator=(const Sprite &);
    virtual void update_image();
    virtual void set_grid_pos(int x, int y);
    void advance(int phase);
    static QPoint directionToVec(const int direction);
    static QPointF directionToVecF(const int direction);


    QPoint get_grid_pos() const;
    int get_direction() const;
    int get_state() const;
};

class MovingSprite : public Sprite{
protected:
    double speed;
    int next_direction;
    int wall_force;
    bool freeze;
    void move(QPointF vec);
    virtual int get_next_direction() const;

public:
    MovingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y);
    MovingSprite(const MovingSprite &sprite);
    MovingSprite& operator=(const MovingSprite &);
    void keyPressEvent(QKeyEvent *event);
    bool check_collision(int direction) const;
    void advance(int phase);
};

#endif // SPRITE_H
