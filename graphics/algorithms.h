#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QMap>
#include <QList>
#include <QPoint>
#include "nodes.h"

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };

class PathAlgorithms
{
    public:
        PathAlgorithms();
        void setMap(QList<QList<WaveCell> > map);
        void setPoints(QPoint start, QPoint goal);

        void wavesearch();
        void makePath();
       QList<QPoint> getPath();

     private:
       QList<QList<WaveCell> > map;
       QPoint start;
       QPoint goal;
       QList<QPoint> returnPath;
//       QList<Node> openList;
       //QList<Node> closedList;


};

#endif // ALGORITHMS_H
