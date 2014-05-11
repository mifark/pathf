#ifndef UNIVERSESCENE_H
#define UNIVERSESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>

#include "maploader.h"
#include "algorithms.h"
#include "names.h"

#define GRID_SIZE 15
#define GRSIZE 3000

class UniverseScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit UniverseScene(QObject *parent = 0);
    virtual ~UniverseScene();
    void createGrid(int width, int height);
    void clearGrid();
    void reSetItems();
    void mapToView();
    void gridToView();

    void getMainPoints(QPoint &start, QPoint &stop);
    
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
private:
    QList<QGraphicsLineItem *> hgrid;
    QList<QGraphicsLineItem *> wgrid;
    QList<CellItem> rcells;

    QRectF findCell(int row, int col);
    QRectF findPointCell(int crdy, int crdx,int &posy, int &posx);
    void graphToCell(int crdy,int crdx,int &posy, int &posx);
    void setRect(clNames::cellTypes ctp,int col,int row);
    
    int pickColor(clNames::cellTypes);

    int searchRect(QRectF rct);
    void gridToView(QList<QList<int> > &map);

    maploader *mpl;
    PathAlgorithms *palgo;

    QPoint start;
    QPoint stop;
    CellItem startMap;
    CellItem stopMap;


    int kw;
    int kh;
    
signals:
    
public slots:
    void setWdHt(int kw,int kh);
    void launchMapLoader(QString mapname);

    void setChoosedAlgo(QString algo);
    
};

#endif // UNIVERSESCENE_H
