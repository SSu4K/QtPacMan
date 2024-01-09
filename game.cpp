#include "game.h"

Game::Game(int x, int y, int map_w, int map_h, int grid_size): QGraphicsScene(x, y, grid_size*map_w, grid_size*map_h), map(map_w, map_h, grid_size, ":assets/map.png")
{
    QString path = ":/assets/sprites.png";
    SpriteSheetReader reader(path, 16);
    QString map_path = ":/assets/map_layout.txt";
    map.load_layout(map_path);
    setBackgroundBrush(Qt::black);
    map.setPos(0, 1);
    addItem(&map);
    //draw_grid();
    //draw_map_debug();
    pacman = new class PacMan(reader, &map);
    addItem(pacman);
    setFocusItem(pacman);
    ghost = new class Ghost(reader, Sprites::Red, &map, 10, 11, new AStarStrategy());
    addItem(ghost);
}

Game::~Game(){
    delete pacman;
    delete ghost;
}

void Game::advance(){
    ghost->update_target(pacman->get_grid_pos());
    QGraphicsScene::advance();
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
