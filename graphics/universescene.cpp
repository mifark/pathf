#include "universescene.h"
#include <QDebug>

UniverseScene::UniverseScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mpl = new maploader();
//    kw = 20;
//    kh = 20;
}

UniverseScene::~UniverseScene()
{
    delete mpl;
}

void UniverseScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void UniverseScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x,y;
    if(event->button() == Qt::RightButton)
    {
//        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x(),y,x);
//        urcells.append(CellItem(this->addRect(rect,QPen(Qt::black),QBrush(Qt::black)),x,y));
    }
    else if(event->button() == Qt::LeftButton)
    {
//        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x(),y,x);
//        int pos;
//        if((pos = searchRect(rect)) != -1)
//        {
//            urcells[searchRect(rect)].item->setBrush(QBrush(Qt::white));
//            this->removeItem(rcells[searchRect(rect)].item);
//            urcells.removeAt(searchRect(rect));
//    //        rcells[1]->
//        }


    }
        
}

void UniverseScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void UniverseScene::createGrid(int width, int height)
{
    double w = width;
    double h = height;
    double lw = w/((double)kw);
    double lh = h/((double)kh);
    qDebug() << "w = " << w << "kw = " << kw << "lw = " << lw;
    qDebug() << "h = " << h << "kh = " << kh << "lh = " << lh;
    for(double i=0;i<=w;i+=lw)
        wgrid.append(this->addLine(i,0,i,h,QPen()));
    for(double i=0;i<=h;i+=lh)
        hgrid.append(this->addLine(0,i,w,i,QPen()));
}

void UniverseScene::clearGrid()
{
    for(int i=0;i<hgrid.size();i++)
        this->removeItem(hgrid[i]);
    for(int j=0;j<wgrid.size();j++)
        this->removeItem(wgrid[j]);
    wgrid.clear();
    hgrid.clear();
}

void UniverseScene::reSetItems()
{
    QRectF rct;
    for (int i = 0; i < rcells.size(); ++i) {
        int x = rcells[i].x;
        int y = rcells[i].y;
        rct = findCell(x,y);
        rcells[i].item->setPen(QPen(rcells[i].item->pen().color()));
        rcells[i].item->setBrush(QBrush(rcells[i].item->brush().color()));
        rcells[i].item->setRect(rct);
        rcells[i].x = x;
        rcells[i].y = y;
    }

}

QRectF UniverseScene::findCell(int row, int col)
{
    if(row<(hgrid.size()-1) && col<(wgrid.size()-1) && col!=-1 && row!=-1)
    {
        QPointF topleft,botright;
        hgrid[row]->line().intersect(wgrid[col]->line(),&topleft);
        hgrid[row+1]->line().intersect(wgrid[col+1]->line(),&botright);
        return QRectF(topleft,botright);
    }
    return QRectF();
    
}

QRectF UniverseScene::findPointCell(int crdy, int crdx, int &posy, int &posx)
{
    graphToCell(crdy,crdx,posy,posx);

    return findCell(posy,posx);
}

void UniverseScene::graphToCell(int crdy, int crdx, int &posy, int &posx)
{
    for(posy=0;posy<hgrid.size();posy++)
        if(crdy<hgrid[posy]->line().p1().y())
        {
            posy--;
            break;
        }

    for(posx=0;posx<wgrid.size();posx++)
        if(crdx<wgrid[posx]->line().p1().x())
        {
            posx--;
            break;
        }

}

int UniverseScene::pickColor(cellTypes tp)
{
    switch (tp) {
        case empty:
            return Qt::white;
            break;
        case start:
            return Qt::green;
            break;
        case stop:
            return Qt::red;
            break;
        case wall:
            return Qt::gray;
            break;
        default:
            return Qt::black;
            break;
    }
}


int UniverseScene::searchRect(QRectF rct)
{
    for(int i=0; i<urcells.size();i++)
    {
        if(urcells[i].item->rect().topLeft() == rct.topLeft())
            return i;
    }
    return -1;
}

void UniverseScene::mapToView()
{
    mpl->loadFirst();
    kw = mpl->getWidth();
    kh = mpl->getHeight();
//    createGrid (mpl->getWidth(),mpl->getHeight ());
 //   gridToView(map);
}

void UniverseScene::gridToView(QList<QList<int> > &map)
{
    for(int i=0;i<map.size();i++)
    {
        QList<int> &col  = map[i];
        for(int j=0;j<col.size();j++)
        {
            if(col[j]==empty)
                setRect(empty,i,j);
            else
                setRect(wall,i,j);
        }
    }
}

void UniverseScene::setRect(cellTypes ctp, int col, int row)
{
    Qt::GlobalColor colr = (Qt::GlobalColor)(pickColor(ctp));
    QRectF rect = findCell(col,row);
    rcells.append(CellItem(this->addRect(rect,QPen(colr),QBrush(colr)),col,row));

}

void UniverseScene::gridToView()
{
    QList<QList<int> > map = mpl->getMap();\
    gridToView(map);
}
