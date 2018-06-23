#include "map.h"
#include "game.h"

extern Game * game;

Map::Map(int level, QGraphicsScene *sc)
{
    scene = sc;

    QString fileName = ":/maps/maps/" + QString::number(level) + ".txt";
    QFile file(fileName);
    if(!file.exists())
    {
        //finished the game
        QGraphicsSimpleTextItem *t = new QGraphicsSimpleTextItem("You finished the game!");
        t->setPos(scene->width()/2, scene->height()/2);
        scene->addItem(t);
        return;
    }


    QTextStream in(&file);

    if (!file.open(QIODevice::ReadOnly))
    {
        //error
        QString temp = "Error while reading: " + fileName;
        QGraphicsSimpleTextItem *t = new QGraphicsSimpleTextItem(temp);
        t->setPos(scene->width()/2, scene->height()/2);
        scene->addItem(t);
        return;
    }
    char c;
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            in >> c;
            while(c == '\n' || c == '\r') //skip endlines
                in >> c;

            int posy = i * 64;
            int posx = j * 64;
            switch(c)
            {
            case '+': //player standing on targer tile
                map[i][j] = new Cell(posx, posy, textures[MAP_TARGET], MAP_TARGET);
                game->player = new Player(posx, posy);
                scene->addItem(game->player);
                break;
            case 'p':
                map[i][j] = new Cell(posx, posy, textures[MAP_FLOOR], MAP_FLOOR);
                //create player            
                game->player = new Player(posx, posy);
                scene->addItem(game->player);
                break;

            case 'o':
                map[i][j] = new Cell(posx, posy, textures[MAP_FLOOR], MAP_FLOOR);
                stones.push_back(new Stone(posx, posy));
                scene->addItem(stones.last());
                //create stone
                break;
            case 'x':
                map[i][j] = new Cell(posx, posy, textures[MAP_TARGET], MAP_TARGET);
                //create target
                break;
            case '*':
                map[i][j] = new Cell(posx, posy, textures[MAP_WALL], MAP_WALL);
                //create wall
                break;
            case ' ':
                //create floor
                map[i][j] = new Cell(posx, posy, textures[MAP_FLOOR], MAP_FLOOR);
                break;
            }

            scene->addItem(map[i][j]);
        }
    }

    file.close();
}


Cell * Map::getCellByPos(int x, int y)
{
    return map[y/64][x/64];
}

Stone * Map::getStoneByPos(int x, int y)
{
   QVector<Stone *>::iterator iter = stones.begin();

   for(; iter != stones.end(); iter++)
   {
        if((*iter)->x() == x && (*iter)->y() == y)
            return *iter;
   }

   return nullptr;
}

bool Map::isStoneAtPos(int x, int y) const
{
    QVector<Stone *>::const_iterator iter = stones.begin();

    for(; iter != stones.end(); iter++)
    {
         if((*iter)->x() == x && (*iter)->y() == y)
             return true;
    }

    return false;
}

bool Map::isLevelFinished() const
{
    QVector<Stone *>::const_iterator iter = stones.begin();

    for(; iter != stones.end(); iter++)
    {
         if(!((*iter)->good))
             return false;
    }

    return true;
}

void Map::clear()
{
    stones.clear();
}

Map::~Map()
{

}
