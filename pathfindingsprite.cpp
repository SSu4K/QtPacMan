#include "pathfindingsprite.h"

PathfindingSprite::PathfindingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y): MovingSprite::MovingSprite(reader, type, map, x, y){
    target = QPoint(x, y);
    home_grid_pos = QPoint(x, y);
}
PathfindingSprite::PathfindingSprite(const PathfindingSprite &sprite): MovingSprite(sprite),
    target(sprite.target), home_grid_pos(sprite.home_grid_pos), pos_memory(sprite.pos_memory), pos_memory_size(sprite.pos_memory_size){}
PathfindingSprite& PathfindingSprite::operator=(const PathfindingSprite &sprite){
    MovingSprite::operator=(sprite);
    target = sprite.target;
    home_grid_pos = sprite.home_grid_pos;
    pos_memory = sprite.pos_memory;
    pos_memory_size = sprite.pos_memory_size;

    return *this;
}
void PathfindingSprite::update_target(QPoint target){
    this->target = target;
}
double PathfindingSprite::evaluate_next_pos(const QPoint &pos)const{
    return 0;
}

int PathfindingSprite::get_next_direction() const{
    int direction = this->direction;
    double eval = INT_MAX;
    for(int i=0;i<4;i++){
        if(!this->check_collision(i)){
            double new_eval = this->evaluate_next_pos(grid_pos + Sprite::directionToVec(i));
            if(new_eval<eval){
                direction = i;
                eval = new_eval;
            }
        }
    }
    return direction;
}
void PathfindingSprite::set_grid_pos(int x, int y){
    pos_memory.push_back(QPoint(x, y));
    if(pos_memory.size()>pos_memory_size){
        pos_memory.erase(pos_memory.begin());
    }
    MovingSprite::set_grid_pos(x, y);
}
