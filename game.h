#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <vector>
#include "pacman.h"
#include "ghost.h"
#include "map.h"
#include "point.h"
#include <QList>

#define OBJECT_WIDTH 16
class Game : public QGraphicsScene
{
    Q_OBJECT
    Map map;
    int score;
    class PacMan *pacman;
    QGraphicsTextItem *score_display;
    QList<Ghost> ghosts;
    QList<Point> points;
    bool run;
    int age;
    int game_over_age;
    void update_targets();
    void handle_points();
    void handle_ghost_collision();
public:
    //using QGraphicsScene::QGraphicsScene;
    Game(int x, int y, int map_w, int map_h, int grid_size);
    ~Game();
    void advance();
    void draw_grid();
    void draw_map_debug();

signals:
    void game_over();
};

#endif // GAME_H
