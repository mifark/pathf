#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>

#include "names.h"

class maploader : public QObject
{
    Q_OBJECT
public:
    explicit maploader(QObject *parent = 0);
    virtual ~maploader();
    void loadFirst();
    void makeMapSymbols();
    QList<QList<int> > getMap();
    int getWidth();
    int getHeight();

private:
    QMultiMap<mapElements,QString> mapSymbols;
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
