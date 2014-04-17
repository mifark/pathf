#include "maploader.h"

maploader::maploader(QObject *parent) :
    QObject(parent)
{
    makeMapSymbols();
    maps.setPath("./");
}

maploader::~maploader()
{
    delete current;
}

void maploader::makeMapSymbols()
{
    mapSymbols[freespace] = ".";
    mapSymbols[wall] = "T";
    mapSymbols[empty] = "@";
}

void maploader::loadFirst()
{

    current = new QFile(maps.path() + )
}


