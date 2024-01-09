#include "pathfindingsprite.h"

void PathfindingStrategy::init(PathfindingSprite *sprite){
    this->sprite = sprite;
}

int PathfindingStrategy::evaluate_next_pos(QPoint pos, QPoint target){
    return abs(pos.x() - target.x()) + abs(pos.y() - target.y());
}

int PathfindingStrategy::get_next_direction(QPoint target){
    int direction = sprite->direction;
    int eval = INT_MAX;
    for(int i=0;i<4;i++){
        if(!sprite->check_collision(i)){
            int new_eval = this->evaluate_next_pos(sprite->grid_pos + Sprite::directionToVec(i), target);
            if(new_eval<eval){
                direction = i;
                eval = new_eval;
            }
        }
    }
    return direction;
}

int AStarStrategy::evaluate_next_pos(QPoint pos, QPoint target){
    return abs(pos.x() - target.x()) + abs(pos.y() - target.y());
}

PathfindingSprite::PathfindingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y, PathfindingStrategy *strategy): MovingSprite::MovingSprite(reader, type, map, x, y){
    this->strategy = strategy;
    strategy->init(this);
    target = QPoint(x, y);
}

PathfindingSprite::~PathfindingSprite(){
    delete strategy;
}

void PathfindingSprite::update_target(QPoint target){
    this->target = target;
}

int PathfindingSprite::get_next_direction(){
    int direction = this->strategy->get_next_direction(target);
    /*
    if(check_collision(direction)){
        return -1;
    }
    */
    return direction;
}
