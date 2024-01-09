#ifndef PACMAN_H
#define PACMAN_H

#include "sprite.h"

class PacMan : public MovingSprite
{
public:
    PacMan(SpriteSheetReader &reader, Map *map);
    void update_image();
    //using MovingSprite::advance;
};

#endif // PACMAN_H
