#include "maploader.h"
#include <QDebug>

maploader::maploader(QObject *parent) :
    QObject(parent)
{
    makeMapSymbols();
    maps.setPath("/home/mifark/pathf/graphics/");
    qDebug() << maps.dirName();
    current = NULL;
}

maploader::~maploader()
{
    if(!current)
        delete current;
}

void maploader::makeMapSymbols()
{
    mapSymbols.insert(passable,".");
    mapSymbols.insert(passable,"G");
    mapSymbols.insert(outOfBounds,"@");
    mapSymbols.insert(outOfBounds,"O");
    mapSymbols.insert(trees,"T");
    mapSymbols.insert(swamp,"S");
    mapSymbols.insert(water,"W");
}

void maploader::loadFirst()
{

    QStringList enList = maps.entryList(QStringList("*.map"));
    current = new QFile(maps.filePath(enList.first()));
    current->open(QIODevice::ReadOnly);
    QTextStream str(current);
    str.readLine();
    QString buf;
    buf = str.readLine();
    mapHeight = buf.split(" ").at(1).toInt();
    buf = str.readLine();
    mapWidth = buf.split(" ").at(1).toInt();
    if(str.readLine()==QString("map"))
    {
       processMap(str);
    }
}

void maploader::loadMap(QString s)
{
    current = new QFile(s);
    current->open(QIODevice::ReadOnly);
    QTextStream str(current);
    str.readLine();
    QString buf;
    buf = str.readLine();
    mapHeight = buf.split(" ").at(1).toInt();
    buf = str.readLine();
    mapWidth = buf.split(" ").at(1).toInt();
    if(str.readLine()==QString("map"))
    {
       processMap(str);
    }

    emit sig_WdHt(mapWidth,mapHeight);
}

void maploader::processMap(QTextStream &str)
{
    QString buffer;
    while(!(buffer = str.readLine()).isNull())
    {
        QList<int> list;
        for(int i=0;i<buffer.size();i++)
            list.append(mapSymbols.key(QChar(buffer[i])));
        readedMap.append(list);
        list.clear();
    }
}

QList<QList<int> > maploader::getMap()
{
    return readedMap;
}

int maploader::getHeight()
{
    return mapHeight;
}

int maploader::getWidth()
{
    return mapWidth;
}


