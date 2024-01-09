#ifndef PATHFINDINGSPRITE_H
#define PATHFINDINGSPRITE_H

#include "sprite.h"

class PathfindingSprite;

class PathfindingStrategy{
  protected:
    PathfindingSprite *sprite;
    int evaluate_next_pos(QPoint pos, QPoint target);
  public:
    PathfindingStrategy() = default;
    ~PathfindingStrategy() = default;
    void init(PathfindingSprite *sprite);
    int get_next_direction(QPoint target);
};

class AStarStrategy: public PathfindingStrategy{
  public:
    using PathfindingStrategy::PathfindingStrategy;
    int evaluate_next_pos(QPoint pos, QPoint target);
};

class PathfindingSprite : public MovingSprite
{
protected:
    PathfindingStrategy *strategy;
    QPoint target;
    int get_next_direction();
public:
    PathfindingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y, PathfindingStrategy *strategy);
    ~PathfindingSprite();
    void update_target(QPoint target);

    friend class PathfindingStrategy;
};

#endif // PATHFINDINGSPRITE_H
