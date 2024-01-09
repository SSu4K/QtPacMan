#include "pacman.h"

PacMan::PacMan(SpriteSheetReader &reader, Map *map) : MovingSprite(reader, Sprites::PacMan, map, 0, 0)
{
    speed = 2;
    set_grid_pos(1, 1);
}

void PacMan::update_image() {
    set_image(2*direction + (age/5)%2);

}

