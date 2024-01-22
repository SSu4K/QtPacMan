#include "map.h"

Map::Map(int width, int height, int grid_size, QString path): width(width), height(height), grid_size(grid_size)
{
    setPixmap(QPixmap(path));
    walls = new int*[width]();
    for(int i =0;i<width;i++){
        walls[i] = new int[height]();
    }
}

Map::~Map(){
    for(int i =0;i<width;i++){
        delete [] walls[i];
    }
    delete [] walls;
}

void Map::randomFill(double propability){
    QRandomGenerator gen;
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            if(gen.generateDouble()<propability){
                walls[x][y] = 1;
            }
            else{
                walls[x][y] = 0;
            }

        }
    }
}

void Map::load_layout(QString path){

     QFile file(path);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
     if (file.exists())
      {
        for(int y=0;y<height;y++){
            const QByteArray line = file.readLine();
            if(file.atEnd()){
                return;
            }
            for(int x=0;x<width;x++){
                walls[x][y] = line[x] - '0';
            }

        }
        file.close();
      }

}
QPoint Map::normalize_point(const QPoint &point){
    QPoint out = point;
    if(out.x()<-1){
        out.setX(width);
    }

    if(out.y()<-1){
        out.setY(height);
    }

    if(out.x()>width){
        out.setX(-1);
    }
    if(out.y()>height){
        out.setY(-1);
    }
    return out;
}

bool Map::is_in_bound(const QPoint &point){
    int x = point.x();
    int y = point.y();
    if(x<0 || x>=width || y<0 || y>height){
        return false;
    }
    return true;
}
bool Map::is_crossing(int x, int y){
    if(!is_in_bound(QPoint(x, y))){
        return false;
    }
    if(walls[x][y]!=0){
        return false;
    }
    int px, py;
    int n=0;
    int neighbours[4][2]={{0,1}, {0, -1}, {1, 0}, {-1, 0}};
    for(int i=0;i<4;i++){
        px = x+neighbours[i][0];
        py = y+neighbours[i][1];
        if(is_in_bound(QPoint(px, py))){
            if(walls[px][py]==0){
                n++;
            }
        }
    }
    return n==4;

}
