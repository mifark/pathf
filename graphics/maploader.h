#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QObject>
#include <QDir>
#include <QList>
#include <QMap>
#include <QFile>

enum mapElements{
    freespace,
    wall,
    empty
};

class maploader : public QObject
{
    Q_OBJECT
public:
    explicit maploader(QObject *parent = 0);
    virtual ~maploader();
    void loadFirst();
    void makeMapSymbols();
    QList<QList<QPoint> > getMap();

private:
    QMap<mapElements,QString> mapSymbols;
    QDir maps;
    QFile *current;
    QList<QList<QPoint> > readedMap;
    
    

signals:

public slots:

};

#endif // MAPLOADER_H
