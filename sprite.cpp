#include "sprite.h"

void Sprite::set_image(int image){
    if(image>=0 && (size_t)image < images.size()){
        setPixmap(images[image]);
    }
}

void Sprite::update_image(){
    set_image(0);
}
Sprite::Sprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y): images(reader.get_spritemap(type)), map(map), size(reader.get_size()), grid_size(map->grid_size), age(0), state(0), direction(0) {
    grid_pos = QPoint(x, y);
}
Sprite::Sprite(const Sprite &sprite): QGraphicsPixmapItem(), images(sprite.images), map(sprite.map), size(sprite.size), grid_size(sprite.grid_size),
    age(sprite.age), state(sprite.state), direction(sprite.direction), grid_pos(sprite.grid_pos), center_pos(sprite.center_pos){}
Sprite& Sprite::operator=(const Sprite &sprite){
    images = sprite.images;
    map = sprite.map;
    size = sprite.size;
    grid_size = sprite.grid_size;
    age = sprite.age;
    state = sprite.state;
    direction = sprite.direction;
    grid_pos = sprite.grid_pos;
    center_pos = sprite.center_pos;
    return *this;
}
void Sprite::set_grid_pos(int x, int y){
    grid_pos = map->normalize_point(QPoint(x, y));
    center_pos = QPointF(x+0.5, y+0.5) * grid_size;
    setPos(center_pos-QPointF(size/2.0, size/2.0));
}
void Sprite::snap_to_grid(){

    this->set_grid_pos(grid_pos.x(), grid_pos.y());
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


QPointF Sprite::directionToVecF(const int direction){
    return QPointF(Sprite::directionToVec(direction));
}

QPoint Sprite::get_grid_pos() const{
    return grid_pos;
}
int Sprite::get_direction() const{
    return direction;
}

int Sprite::get_state() const{
    return state;
}
MovingSprite::MovingSprite(SpriteSheetReader &reader ,enum Sprites type, Map *map, int x, int y): Sprite::Sprite(reader, type, map, x, y), speed(0), next_direction(0), wall_force(0), freeze(false) {
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    direction = 0;
}

MovingSprite::MovingSprite(const MovingSprite &sprite): Sprite(sprite),
    speed(sprite.speed), next_direction(sprite.next_direction), freeze(sprite.freeze), wall_force(sprite.wall_force){}
MovingSprite& MovingSprite::operator=(const MovingSprite &sprite){
    Sprite::operator=(sprite);
    speed = sprite.speed;
    freeze = sprite.freeze;
    next_direction = sprite.next_direction;
    wall_force = sprite.wall_force;
    return *this;
}
void MovingSprite::move(QPointF vec){
    if(!freeze){
        center_pos += vec;
        setPos(center_pos - QPoint(size/2, size/2));
    }

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

bool MovingSprite::check_collision(int direction) const{
    QPoint next_grid_pos = grid_pos + Sprite::directionToVec(direction);
    int next_grid_x = next_grid_pos.x();
    int next_grid_y = next_grid_pos.y();
    if(next_grid_x < 0 || next_grid_y < 0 || next_grid_x >= map->width || next_grid_y >= map->height){
        return false;
    }
    if(map->walls[next_grid_x][next_grid_y]>this->wall_force){
        return true;
    }
    return false;
}

int MovingSprite::get_next_direction() const{
    if(this->check_collision(this->next_direction)){
        return -1;
    }
    else{
        return next_direction;
    }
}

void MovingSprite::advance(int phase){
    Sprite::advance(phase);
    if(phase){

        QPoint grid_center = grid_pos*grid_size + QPoint(grid_size/2, grid_size/2);
        if(freeze || abs(center_pos.x() - grid_center.x()) >= grid_size || abs(center_pos.y() - grid_center.y()) >= grid_size){
            if(!freeze){
                grid_pos += Sprite::directionToVec(direction);
                snap_to_grid();
            }

            int next_direction = -1;;
            if(map->is_in_bound(grid_pos)){
                next_direction = this->get_next_direction();
            }
            if(next_direction == -1){
                //this->next_direction = direction;
                 if(this->check_collision(direction)){
                     freeze = true;
                 }
            }
            else{
                direction = next_direction;
                freeze = false;
            }
        }
        move(Sprite::directionToVecF(direction)*this->speed);
    }
}
