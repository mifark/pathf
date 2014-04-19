#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>

enum mapElements{
    passable = 0,
    trees,
    swamp,
    water,
    outOfBounds
};

class maploader : public QObject
{
    Q_OBJECT
public:
    explicit maploader(QObject *parent = 0);
    virtual ~maploader();
    void loadFirst();
    void makeMapSymbols();
    QList<QList<int> > getMap();

private:
    QMultiMap<mapElements,QString> mapSymbols;
    QDir maps;
    QFile *current;
    QList<QList<int> > readedMap;
    int mapHeight;
    int mapWidth;

    void processMap(QTextStream &str);
    

signals:

public slots:

};

#endif // MAPLOADER_H
