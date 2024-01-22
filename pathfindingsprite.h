#ifndef PATHFINDINGSPRITE_H
#define PATHFINDINGSPRITE_H

#include "sprite.h"

class PathfindingSprite : public MovingSprite
{
protected:
    virtual double evaluate_next_pos(const QPoint &pos) const;
    int get_next_direction() const;
public:
    QPoint target;
    QPoint home_grid_pos;
    std::vector<QPoint> pos_memory;
    size_t pos_memory_size;
    PathfindingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y);
    PathfindingSprite(const PathfindingSprite&);
    PathfindingSprite& operator=(const PathfindingSprite &);
    void update_target(QPoint target);
    void set_grid_pos(int x, int y);
};

#endif // PATHFINDINGSPRITE_H
