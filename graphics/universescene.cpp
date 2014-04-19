#include "universescene.h"
#include <QDebug>

UniverseScene::UniverseScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mpl = new maploader();
    mpl->loadFirst();
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
    if(event->button() == Qt::RightButton)
    {
        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x());
        rcells.append(this->addRect(rect,QPen(Qt::black),QBrush(Qt::black)));
    }
    else if(event->button() == Qt::LeftButton)
    {
        QRectF rect = findPointCell(event->scenePos().y(),event->scenePos().x());
        rcells.removeAt(searchRect(rect));
//        rcells[1]->


    }
        
}

void UniverseScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void UniverseScene::createGrid(int width, int height)
{
    int w = width;
    int h = height;
    int lw = ((double)w)/GRID_SIZE;
    int lh = ((double)h)/GRID_SIZE;
    for(int i=0;i<=w;i+=lw)
        wgrid.append(this->addLine(i,0,i,h,QPen()));
    for(int i=0;i<=h;i+=lh)
        hgrid.append(this->addLine(0,i,w,i,QPen()));
}

QRectF UniverseScene::findCell(int row, int col)
{
    if(row<(hgrid.size()-1) && col<(wgrid.size()-1))
    {
        QPointF topleft,botright;
        hgrid[row]->line().intersect(wgrid[col]->line(),&topleft);
        hgrid[row+1]->line().intersect(wgrid[col+1]->line(),&botright);
        return QRectF(topleft,botright);
    }
    return QRectF();
    
}

QRectF UniverseScene::findPointCell(int y, int x)
{
    int posy;
    for(posy=0;posy<hgrid.size();posy++)
        if(y<hgrid[posy]->line().p1().y())
        {
            posy--;
            break;
        }
            
    int posx;
    for(posx=0;posx<hgrid.size();posx++)
        if(x<wgrid[posx]->line().p1().x())
        {
            posx--;
            break;
        }
    return findCell(posy,posx);
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
    for(int i=0; i<rcells.size();i++)
    {
        if(rcells[i]->rect() == rct)
        {
            return i;
        }

    }
}
