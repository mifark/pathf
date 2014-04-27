#ifndef UNIVERSESCENE_H
#define UNIVERSESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>

#include "maploader.h"
#include "names.h"

#define GRID_SIZE 15
struct CellItem{
    QGraphicsRectItem *item;
    int x;
    int y;
    CellItem(QGraphicsRectItem *item,int i, int j) :
        item(item),
        x(i),
        y(j)
    {
    }
};

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
    
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
private:
    QList<QGraphicsLineItem *> hgrid;
    QList<QGraphicsLineItem *> wgrid;
    QList<CellItem> rcells;
    QList<CellItem> urcells;

    QRectF findCell(int row, int col);
    QRectF findPointCell(int crdy, int crdx,int &posy, int &posx);
    void graphToCell(int crdy,int crdx,int &posy, int &posx);
    void setRect(cellTypes ctp,int col,int row);
    
    int pickColor(cellTypes tp);

    int searchRect(QRectF rct);
    void gridToView(QList<QList<int> > &map);

    maploader *mpl;

    unsigned int kw;
    unsigned int kh;
    
signals:
    
public slots:
    void setWdHt(unsigned int kw, unsigned int kh);
    
};

#endif // UNIVERSESCENE_H
