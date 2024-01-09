#ifndef GHOST_H
#define GHOST_H

#include "pathfindingsprite.h"

class Ghost : public PathfindingSprite
{
public:
    //Ghost(SpriteSheetReader &reader ,enum Sprites ghost, Map *map, int x, int y);
    //using PathfindingSprite::PathfindingSprite;
    Ghost(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y, PathfindingStrategy *strategy);
    void keyPressEvent(QKeyEvent *event);
    void update_image();
};

#endif // GHOST_H
