#ifndef SPRITESHEETREADER_H
#define SPRITESHEETREADER_H

#include <QPixmap>
#include <vector>
#include <map>

enum Sprites{PacMan, Red, Pink, Cyan, Orange};

class SpriteSheetReader
{
    QPixmap sheet;
    int sprite_size;
    std::map<enum Sprites, std::vector<QPixmap>> sprite_maps;

public:
    SpriteSheetReader(QString path, int sprite_size);
    QPixmap get_slice(int x, int y) const;
    std::vector<QPixmap> get_spritemap(enum Sprites sprite);
    int get_size()const;
};

#endif // SPRITESHEETREADER_H
