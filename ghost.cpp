#include "ghost.h"

#define ALIVE_WAIT 20
#define EDIBLE_TIME 200
#define BLINKING_TIME 50

Ghost::Ghost(SpriteSheetReader &reader ,enum Sprites ghost, Map *map, int x, int y, double distance_weight, double exploration_weight) : PathfindingSprite(reader, ghost, map, x, y)
{
    speed = 1;
    wall_force = 1;
    pos_memory_size = (map->width+map->height);
    this->distance_weight = distance_weight;
    this->exploration_weight = exploration_weight;
}
Ghost::Ghost(const Ghost &ghost): PathfindingSprite(ghost), distance_weight(ghost.distance_weight), exploration_weight(ghost.exploration_weight){}

Ghost& Ghost::operator=(const Ghost &ghost){
    PathfindingSprite::operator=(ghost);
    distance_weight = ghost.distance_weight;
    exploration_weight = ghost.exploration_weight;
    return *this;
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

void Ghost::update_target(QPoint target){
    if(state==3){
        PathfindingSprite::update_target(home_grid_pos);
    }
    else{
        PathfindingSprite::update_target(target);
    }
}

int lev_dist(const QPoint &a, const QPoint &b){
    return abs(a.x() - b.x()) + abs(a.y() - b.y());
}

double Ghost::evaluate_next_pos(const QPoint &pos) const{
    double exploration = 0;
    for(int i=pos_memory.size()-1; i>=0;i--){
        if(pos_memory[i]==pos){
            exploration = (double)(i+1)/double(pos_memory_size);
            break;
        }
    }
    double distance = (double)lev_dist(pos, target)/(double)(map->width+map->height);

    if((state == 1 || state == 2)&& distance_weight>0){
        distance *= (-1);
    }
    if(state==DEAD){
        QRandomGenerator gen;
        return (20+gen.bounded(8))*distance + gen.bounded(2)*exploration;
    }
    return distance_weight*distance + exploration_weight*exploration;
}
void Ghost::set_state(enum GhostState state){
        state_age = age;
        this->state = state;


    if(state==ALIVE){
        speed = 1.2;
    }
    if(state==EDIBLE){
        speed = 1;
    }
    if(state== DEAD){
        speed = 2.5;
    }

}

void Ghost::advance(int phase){
    if(phase ==1){
        if((state == 1 || state == 2)&&age-state_age>EDIBLE_TIME){
            set_state(ALIVE);
        }
        if((state == 1)&&age-state_age>EDIBLE_TIME-BLINKING_TIME){
           state = 2;
        }
        if(state == 3 && grid_pos==home_grid_pos){
            set_state(ALIVE);
        }
        PathfindingSprite::advance(phase);
    }
}
