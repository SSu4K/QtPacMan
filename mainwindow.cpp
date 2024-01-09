#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), game(100, 100, 500, 500, 20), view(&game, this)
{
    ui->setupUi(this);
    view.setBackgroundBrush(Qt::red);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    //view.scale(2, 2);
    //view.show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

