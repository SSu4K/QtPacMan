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

    Game game(0, 0, 28, 34, 8);
    QGraphicsView view(&game);
    view.scale(2, 2);
    view.show();
    QTimer *timer = new QTimer(&view);
    QObject::connect(timer, &QTimer::timeout, &game, &Game::advance);
        timer->start(20);
    QObject::connect(&game, &Game::game_over, timer, &QTimer::stop);
    QObject::connect(&game, &Game::game_over, &view, &QWidget::close);


    return a.exec();
}
