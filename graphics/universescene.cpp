#include "universescene.h"
#include <QGraphicsScene>
#include <QDebug>

UniverseScene::UniverseScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mpl = new maploader();
    palgo = new PathAlgorithms();
    kw = GRSIZE;
    kh = GRSIZE;
    connect(mpl,SIGNAL(sig_WdHt(int,int)),this,SLOT(setWdHt(int,int)));
}

UniverseScene::~UniverseScene()
{
    delete mpl;
    delete palgo;
}

void UniverseScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void UniverseScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x,y;
    if(event->button() == Qt::RightButton)
    {
        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x(),y,x);
//        rcells.append(CellItem(this->addRect(rect,QPen(Qt::black),QBrush(Qt::black)),x,y));

        if(stopMap.item!=NULL)
        {
            delete stopMap.item;
            stopMap.item = new QGraphicsRectItem();
            stopMap.item->setBrush(QBrush(this->pickColor(mpl->getSpecificCell(x,y) ?clNames::empty : clNames::wall )));
            stopMap.item->setPen(QPen(this->pickColor(mpl->getSpecificCell(x,y) ? clNames::empty : clNames::wall )));
        }
        stopMap = CellItem(this->addRect(rect,QPen(Qt::red),QBrush(Qt::red)),(clNames::cellTypes)mpl->getSpecificCell(x,y),x,y);
        stop = QPoint(x,y);

    }
    else if(event->button() == Qt::LeftButton)
    {
        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x(),y,x);

        if(startMap.item!=NULL)
        {
            delete startMap.item;
            startMap.item = new QGraphicsRectItem();
            startMap.item->setBrush(QBrush(this->pickColor(mpl->getSpecificCell(x,y) ?clNames::empty : clNames::wall )));
            startMap.item->setPen(QPen(this->pickColor(mpl->getSpecificCell(x,y) ? clNames::empty : clNames::wall )));
        }
        startMap = CellItem(this->addRect(rect,QPen(Qt::green),QBrush(Qt::green)),(clNames::cellTypes)mpl->getSpecificCell(x,y),x,y);
        start = QPoint(x,y);
    }
        
}

void UniverseScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void UniverseScene::createGrid(int width, int height)
{
    if(kw==0)
    {
        qDebug() << "Null map error";
        return;
    }
    double w = width;
    double h = height;
    double lw = w/((double)kw);
    double lh = h/((double)kh);
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
//    rcells.clear();
}

void UniverseScene::reSetItems()
{
    /*
    QRectF rct;
    for (int i = 0; i < rcells.size(); ++i)
    {
        int x = rcells[i].crd.x();
        int y = rcells[i].crd.y();
        rct = findCell(x,y);
        rcells[i].item->setPen(QPen(rcells[i].item->pen().color()));
        rcells[i].item->setBrush(QBrush(rcells[i].item->brush().color()));
        rcells[i].item->setRect(rct);
        rcells[i].crd.setX(x);
        rcells[i].crd.setY(y);
    }
    */

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

int UniverseScene::pickColor(clNames::cellTypes tp)
{
    switch (tp) {
        case clNames::empty:
            return Qt::white;
            break;
        case clNames::start:
            return Qt::green;
            break;
        case clNames::stop:
            return Qt::red;
            break;
        case clNames::wall:
            return Qt::gray;
            break;
        default:
            return Qt::gray;
            break;
    }
}


int UniverseScene::searchRect(QRectF rct)
{
    for(int i=0; i<rcells.size();i++)
    {
        if(qAbs(rcells[i].item->rect().topLeft().y()-rct.topLeft().y()) < 0.001)
            return i;
    }
    return -1;
}

void UniverseScene::mapToView()
{
//    mpl->loadFirst();
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
            if(col[j]==clNames::empty)
                setRect(clNames::empty,i,j);
            else
                setRect(clNames::wall,i,j);
        }
    }
}

void UniverseScene::setRect(clNames::cellTypes ctp, int col, int row)
{
    Qt::GlobalColor colr = (Qt::GlobalColor)(pickColor(ctp));
    QRectF rect = findCell(col,row);
    rcells.append(CellItem(this->addRect(rect,QPen(colr),QBrush(colr)),ctp,col,row));

}

void UniverseScene::gridToView()
{
    QList<QList<int> > map = mpl->getMap();\
    gridToView(map);
}

void UniverseScene::setWdHt(int kw, int kh)
{
    this->kw =  kw;
    this->kh = kh;
}

void UniverseScene::launchMapLoader(QString mapname)
{
    clearGrid();
    mpl->setMap(mapname);
    mapToView();
    createGrid(GRSIZE,GRSIZE);
    gridToView();
    reSetItems();

}

void UniverseScene::setChoosedAlgo(QString algo)
{
    palgo->setMap(mpl->getWaveMap());
    palgo->setPoints(start,stop);
    palgo->start_WaveSearch();
    QList<QPoint> point = palgo->getPath();

}

void UniverseScene::getMainPoints(QPoint &start, QPoint &stop)
{
    start = startMap.crd;
    stop = stopMap.crd;
}

