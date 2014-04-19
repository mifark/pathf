#include "maploader.h"
#include <QDebug>

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

    QStringList enList = maps.entryList();
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

void maploader::processMap(QTextStream &str)
{
    QString buffer;
    while(!(buffer = str.readLine()).isNull())
    {
        QList<int> list;
        for(int i=0;i<buffer.size();i++)
        {
            qDebug() << mapSymbols.key(QString(buffer[i]));
            list.append(mapSymbols.key(QString(buffer[i])));
        }
        readedMap.append(list);
    }
}

QList<QList<int> > maploader::getMap()
{
    return readedMap;
}


