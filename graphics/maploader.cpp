#include "maploader.h"
#include "nodes.h"

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
    mapSymbols.insert(clNames::passable,".");
    mapSymbols.insert(clNames::passable,"G");
    mapSymbols.insert(clNames::outOfBounds,"@");
    mapSymbols.insert(clNames::outOfBounds,"O");
    mapSymbols.insert(clNames::trees,"T");
    mapSymbols.insert(clNames::swamp,"S");
    mapSymbols.insert(clNames::water,"W");
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

void maploader::setMap(QString mapname)
{
    loadMap(mapname);
}

void maploader::processMap(QTextStream &str)
{
    QString buffer;
    readedMap.clear();
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

int maploader::getSpecificCell(int x, int y)
{
    int j = readedMap[x][y];
    if(!readedMap.isEmpty())
        return readedMap[x][y];
    else
        return -1;
}

QList<QList<WaveCell> > maploader::getWaveMap()
{
    QList<QList<WaveCell> > returnable;
    for (int i = 0; i < readedMap.size(); ++i) {
        returnable.append(QList<WaveCell>());
        for(int j=0; j < readedMap[i].size(); ++j)
        {
            returnable[i].append(WaveCell());
            returnable[i][j] = readedMap[i][j];
        }
    }
    return returnable;
}

int maploader::getHeight()
{
    return mapHeight;
}

int maploader::getWidth()
{
    return mapWidth;
}


