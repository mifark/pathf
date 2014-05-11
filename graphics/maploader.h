#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "nodes.h"

class maploader : public QObject
{
    Q_OBJECT
public:
    explicit maploader(QObject *parent = 0);
    virtual ~maploader();
    void loadFirst();
    void makeMapSymbols();
    QList<QList<int> > getMap();
    int getSpecificCell(int x, int y);
    QList<QList<WaveCell> > getWaveMap();
    QList<Node> getNodeList();
    int getWidth();
    int getHeight();
    void setMap(QString mapname);

private:
    QMultiMap<clNames::mapElements,QString> mapSymbols;
    QDir maps;
    QFile *current;
    QList<QList<int> > readedMap;
    int mapHeight;
    int mapWidth;

    void processMap(QTextStream &str);
    void loadMap(QString s);


signals:
    void sig_WdHt(int mapWidth,int mapHeight);

public slots:

};

#endif // MAPLOADER_H
