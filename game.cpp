#include "game.h"

#define GAME_OVER_TIME 200

Game::Game(int x, int y, int map_w, int map_h, int grid_size): QGraphicsScene(x, y, grid_size*map_w, grid_size*map_h), map(map_w, map_h, grid_size, ":assets/map.png")
{
    run = true;
    age = 0;
    game_over_age = 0;
    score = 0;
    QString path = ":/assets/sprites.png";
    SpriteSheetReader reader(path, 16);
    QString map_path = ":/assets/map_layout.txt";
    map.load_layout(map_path);
    setBackgroundBrush(Qt::black);
    map.setPos(0, 1);
    addItem(&map);
    draw_map_debug();

    for(int py=0;py<map.height;py++){
        for(int px=0;px<map.width;px++){
            if(map.walls[px][py]==0){
                if(map.is_crossing(px,py)){
                    points.append(Point(px, py, grid_size, 400, grid_size*0.75));
                }
                else{
                    points.append(Point(px, py, grid_size, 100, grid_size*0.4));
                }
            }
        }
    }
    for(int i=0;i<points.size();i++){
        addItem(&points[i]);
    }
    pacman = new class PacMan(reader, &map);
    addItem(pacman);
    setFocusItem(pacman);
    ghosts.append(Ghost(reader, Sprites::Red, &map, 12, 13, 4, 1));
    ghosts.append(Ghost(reader, Sprites::Pink, &map, 12, 15, 1, 4));
    ghosts.append(Ghost(reader, Sprites::Cyan, &map, 14, 13, -2, 3));
    ghosts.append(Ghost(reader, Sprites::Orange, &map, 14, 15, 2, 3));

    for(int i=0;i<ghosts.size();i++){
        addItem(&ghosts[i]);
    }

    score_display = new QGraphicsTextItem;
    //score_display->setPlainText("Hello world!");
    score_display->setPos(0, (map_w+3)*grid_size);
    score_display->setDefaultTextColor(Qt::white);
    addItem(score_display);
}

Game::~Game(){
    delete pacman;
    delete score_display;
}
void Game::update_targets(){
    QPoint pacman_pos = pacman->get_grid_pos();
    QPoint pacman_dir = Sprite::directionToVec(pacman->get_direction());
    ghosts[0].update_target(pacman_pos);
    ghosts[1].update_target(pacman_pos + 4 * pacman_dir);
    ghosts[2].update_target(pacman_pos);
    ghosts[3].update_target((ghosts[0].get_grid_pos()+ghosts[3].get_grid_pos())/2);

}
void Game::handle_points(){
    QPoint pacman_pos = pacman->get_grid_pos();
    for(int i=0;i<points.size();i++){
        if(pacman_pos == points[i].grid_pos){
            if(points[i].scene()!=NULL){
                this->removeItem(&points[i]);
            }
            score += points[i].score;
            if(points[i].score > 100){
                for(int i=0;i<ghosts.size();i++){
                    if(ghosts[i].get_state()!=Ghost::DEAD){
                        ghosts[i].set_state(Ghost::EDIBLE);
                    }
                }
            }
            points.erase(points.begin()+i);
            i--;
        }
    }
    QString txt = "Score: ";
    txt.append(std::to_string(score).c_str());
    score_display->setPlainText(txt);
    QGraphicsScene::advance();
}
void Game::handle_ghost_collision(){
    auto pacman_pos = pacman->get_grid_pos();
    for(int i=0;i<ghosts.size();i++){
        auto ghost_pos = ghosts[i].get_grid_pos();
        if(pacman_pos==ghost_pos||pacman_pos+Sprite::directionToVec(pacman->get_direction())==ghost_pos){
            auto state = ghosts[i].get_state();
            if(state==1 || state == 2){
                ghosts[i].set_state(Ghost::DEAD);
            }
            else if(state == Ghost::ALIVE){
                run = false;
                game_over_age = age;
                auto ptr = addText("You Lost!");
                ptr->setPos(100, 100);
                ptr->setDefaultTextColor(Qt::red);
            }
        }

    }
}
void Game::advance(){
	age++;
	if(run){
		update_targets();
		handle_points();
		handle_ghost_collision();
	}
	else{
		if(age-game_over_age>GAME_OVER_TIME){
			for(auto &item : items()){
				removeItem(item);
			}
			emit game_over();
		}
		
	}
}

void Game::draw_grid()
{
    int step = map.grid_size;
    QPen pen(QColor(200, 200, 255, 125));
    for(int y=0;y<map.height;y++){
        addLine(0, y*step, width(), y*step, pen);
    }
    for(int x=0;x<map.width;x++){
        addLine(x*step, 0, x*step, height(), pen);
    }
}

void Game::draw_map_debug(){
    int step = map.grid_size;
    QPen pen(QColor(200, 0, 0, 125));
    for(int y=0;y<map.height;y++){
        for(int x=0;x<map.width;x++){
            if(map.walls[x][y]!=0){
                addRect(x*step, y*step, step, step, pen);
            }
        }
    }
}
