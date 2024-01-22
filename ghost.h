#ifndef GHOST_H
#define GHOST_H

#include "pathfindingsprite.h"

class Ghost : public PathfindingSprite
{
protected:
    double distance_weight;
    double exploration_weight;
    double evaluate_next_pos(const QPoint &pos) const;
    int state_age;
public:
    enum GhostState{ALIVE=0, EDIBLE=1, DEAD=3};
    Ghost(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y, double distance_weight, double exploration_weight);
    Ghost(const Ghost &ghost);
    Ghost& operator=(const Ghost &ghost);
    void update_image();
    void update_target(QPoint target);
    void set_state(enum GhostState state);
    void advance(int phase);
};

#endif // GHOST_H
