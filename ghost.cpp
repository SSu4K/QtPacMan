#include "ghost.h"

Ghost::Ghost(SpriteSheetReader &reader ,enum Sprites ghost, Map *map, int x, int y, PathfindingStrategy *strategy) : PathfindingSprite(reader, ghost, map, x, y, strategy)
{
    speed = 1;
}

void Ghost::keyPressEvent(QKeyEvent *event){
    MovingSprite::keyPressEvent(event);
    switch(event->key()){
    case Qt::Key_0:
        state = 0;
        break;
    case Qt::Key_1:
        state = 1;
        break;
    case Qt::Key_2:
        state = 2;
        break;
    case Qt::Key_3:
        state = 3;
        break;


    }
}

void Ghost::update_image() {
    switch(state){
       default:
        set_image(direction*2 + (age/5)%2);
        break;
       case 1:
        set_image(8 + (age/5)%2);

        break;
       case 2:
        set_image(8 + (age/5)%4);
        break;

       case 3:
        set_image(direction + 12);
        break;

    }

}
