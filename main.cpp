#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTimer>
#include "sprite.h"
#include "spritesheetreader.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene(0, 0, 1000, 1000);
    scene.setBackgroundBrush(Qt::black);


/*
    QString path = ":/assets/sprites.png";

    //QPixmap sprites(path);
    //QPixmap pic = sprites.copy(0, 0, 100, 100);

    SpriteSheetReader reader(path, 16);
    auto list = reader.get_spritemap(PacMan);

    for(size_t i=0;i<list.size();i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(list[i]);
        item->setOffset(i*20, 0);
        scene.addItem(item);
    }
    list = reader.get_spritemap(Red);

    for(size_t i=0;i<list.size();i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(list[i]);
        item->setOffset(i*20, 20);
        scene.addItem(item);
    }

    list = reader.get_spritemap(Pink);

    for(size_t i=0;i<list.size();i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(list[i]);
        item->setOffset(i*20, 40);
        scene.addItem(item);
    }

    list = reader.get_spritemap(Cyan);

    for(size_t i=0;i<list.size();i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(list[i]);
        item->setOffset(i*20, 60);
        scene.addItem(item);
    }

    list = reader.get_spritemap(Orange);

    for(size_t i=0;i<list.size();i++){
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(list[i]);
        item->setOffset(i*20, 80);
        scene.addItem(item);
    }
QGraphicsView view(&scene);
        view.show();
*/

    Game game(0, 0, 28, 36, 8);
    QGraphicsView view(&game);
    view.show();
    QTimer *timer = new QTimer(&view);
    QObject::connect(timer, &QTimer::timeout, &game, &Game::advance);
        timer->start(30);

    return a.exec();
}
