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
                if(line[x]=='1'){
                    walls[x][y] = 1;
                }
                else{
                    walls[x][y] = 0;
                }

            }

        }
        file.close();
      }

}
