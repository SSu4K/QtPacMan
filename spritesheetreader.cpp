#include "spritesheetreader.h"

using namespace std;

QPixmap SpriteSheetReader::get_slice(int x, int y) const{
    return sheet.copy(x*sprite_size, y*sprite_size, sprite_size, sprite_size);
}

SpriteSheetReader::SpriteSheetReader(QString path, int sprite_size) : sheet(path), sprite_size(sprite_size)
{
// PacMan
    vector<QPixmap> map;
    for(int y=0;y<4;y++){
        for(int x=0;x<2;x++){
            map.push_back(get_slice(x, y));
        }
    }
    sprite_maps[PacMan] = map;
    map.clear();
// Ghosts
    enum Sprites ghosts[4] = {Red, Pink, Cyan, Orange};

    for(int i=0;i<4;i++){
        for(int x=0;x<8;x++){
            map.push_back(get_slice(x, 4+i));
        }
        for(int i=8;i<12;i++){
            map.push_back(get_slice(i, 4));
        }
        //map.push_back(get_slice(8, 4));
        //map.push_back(get_slice(9, 4));
        for(int x=8;x<12;x++){
            map.push_back(get_slice(x, 5));
        }
        sprite_maps[ghosts[i]] = map;
        map.clear();
    }
}

vector<QPixmap> SpriteSheetReader::get_spritemap(enum Sprites sprite){
    return sprite_maps[sprite];
}

int SpriteSheetReader::get_size()const{
    return sprite_size;
}
