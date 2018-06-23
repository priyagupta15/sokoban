#include "game.h"

extern Game * game;

Game::~Game()
{
    scene->clear();
    delete map;
    delete player;
}

Game::Game()
{
    game = this; //dunno know why it must be here, but...

    level = 1;

    scene = new QGraphicsScene();
    setScene(scene);

    int d = 16*64;
    scene->setSceneRect(0, 0, d, d);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(d, d);

    map = new Map(level, scene);

    //scale(0.8, 0.8);
}

void Game::restartLevel()
{
    scene->clear();
    scene->update();

    //delete map;
    //delete player;

    map->clear();
    map = new Map(level, scene);
}

void Game::nextLevel()
{
    scene->clear();
    scene->update();

    //delete map;
    //delete player;

    level++;
    map->clear();
    map = new Map(level, scene);
}
