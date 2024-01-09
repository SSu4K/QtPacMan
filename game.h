#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <vector>
#include "pacman.h"
#include "ghost.h"
#include "map.h"

#define OBJECT_WIDTH 16
class Game : public QGraphicsScene
{
    Q_OBJECT
    Map map;
    class PacMan *pacman;
    class Ghost *ghost;
public:
    //using QGraphicsScene::QGraphicsScene;
    Game(int x, int y, int map_w, int map_h, int grid_size);
    ~Game();
    void advance();
    void draw_grid();
    void draw_map_debug();
};

#endif // GAME_H
