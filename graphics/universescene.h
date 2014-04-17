#ifndef UNIVERSESCENE_H
#define UNIVERSESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>

#define GRID_SIZE 15
enum cellTypes{
    empty = 0,
    start = 1,
    stop = 2,
    wall = 3,
};

class UniverseScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit UniverseScene(QObject *parent = 0);
    void createGrid(int width, int height);
    
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
private:
    QList<QGraphicsLineItem *> hgrid;
    QList<QGraphicsLineItem *> wgrid;
    QList<QGraphicsRectItem *> rcells;
    
    QRectF findCell(int row, int col);
    QRectF findPointCell(int y, int x);
    
    int pickColor(cellTypes tp);

    int searchRect(QRectF rct);
    
signals:
    
public slots:
    
};

#endif // UNIVERSESCENE_H
