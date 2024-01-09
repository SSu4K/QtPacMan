#include "sprite.h"

void Sprite::set_image(int image){
    if(image>=0 && (size_t)image < images.size()){
        setPixmap(images[image]);
    }
}

void Sprite::update_image(){
    set_image(0);
}
Sprite::Sprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y): images(reader.get_spritemap(type)), map(map), size(reader.get_size()), grid_size(map->grid_size), offset((grid_size-size)/2), type(type), age(0), state(0), direction(0) {
    set_grid_pos(x, y);
}
void Sprite::set_grid_pos(int x, int y){
    grid_pos.setX(x);
    grid_pos.setY(y);
    setPos(x*grid_size+offset, y*grid_size+offset);
    center_pos.setX((x+0.5)*grid_size);
    center_pos.setY((y+0.5)*grid_size);
}
void Sprite::snap_to_grid(){
    if(grid_pos.x()<-1){
        grid_pos.setX(map->width);
    }

    if(grid_pos.y()<-1){
        grid_pos.setY(map->height);
    }

    if(grid_pos.x()>map->width){
        grid_pos.setX(-1);
    }
    if(grid_pos.y()>map->height){
        grid_pos.setY(-1);
    }

    set_grid_pos(grid_pos.x(), grid_pos.y());
}
void Sprite::advance(int phase){
    if(phase){
        age++;
        this->update_image();
    }
}

QPoint Sprite::directionToVec(const int direction){
    switch(direction){
        default:
            return QPoint(0, 0);
        case 0:
            return QPoint(1, 0);
    case 1:
        return QPoint(-1, 0);
    case 2:
        return QPoint(0, -1);
    case 3:
        return QPoint(0, 1);

    }

}

QPoint Sprite::get_grid_pos() const{
    return grid_pos;
}

void MovingSprite::move(QPoint vec){
    if(!freeze){
        setPos(pos()+vec);
        center_pos += vec;
    }

}

MovingSprite::MovingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y): Sprite::Sprite(reader, type, map, x, y), speed(0), next_direction(0), freeze(false) {
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    direction = 0;
}

void MovingSprite::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_D:
        next_direction = 0;
        break;
    case Qt::Key_A:
        next_direction = 1;
        break;
    case Qt::Key_W:
        next_direction = 2;
        break;
    case Qt::Key_S:
        next_direction = 3;
        break;


    }
}

bool MovingSprite::check_collision(int direction){
    QPoint next_grid_pos = grid_pos + Sprite::directionToVec(direction);
    int next_grid_x = next_grid_pos.x();
    int next_grid_y = next_grid_pos.y();
    if(next_grid_x < 0 || next_grid_y < 0 || next_grid_x >= map->width || next_grid_y >= map->height){
        return false;
    }
    if(map->walls[next_grid_x][next_grid_y]!=0){
        return true;
    }
    return false;
}

int MovingSprite::get_next_direction(){
    if(check_collision(this->next_direction)){
        return -1;
    }
    else{
        return next_direction;
    }
}

void MovingSprite::advance(int phase){
    Sprite::advance(phase);
    if(phase){
        if(freeze || (abs((grid_pos.x()+0.5)*grid_size - center_pos.x()) >= grid_size || abs((grid_pos.y()+0.5)*grid_size - center_pos.y()) >= grid_size)){
            grid_pos.setX((x()-offset)/grid_size);
            grid_pos.setY((y()-offset)/grid_size);
            snap_to_grid();

            int next_direction = this->get_next_direction();

            if(next_direction == -1){
                this->next_direction = direction;
                 if(check_collision(direction)){
                     freeze = true;
                 }
            }
            else{
                direction = next_direction;
                freeze = false;
            }
        }
        move(Sprite::directionToVec(direction)*this->speed);
    }
}
