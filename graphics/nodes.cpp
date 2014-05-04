#include "nodes.h"

//=====================================================================
// Node
//=====================================================================

Node::Node(QPoint crd, Node *parent, Node *child) : crd(crd), parent(parent),child(child)
{
}
Node::Node() : crd(QPoint(0,0)),parent(NULL),child(NULL)
{
}

Node::~Node()
{
}

bool Node::operator==(const Node & right) const
{
   return crd == right.crd
}

// операция сравнения с узлами CellItem
bool Node::operator==(const CellItem & right) const
{
   return crd == right.crd
}

bool Node::operator!=(const Node & right) const
{
    return ! *this == right;
}

bool Node::operator!=(const CellItem & right) const
{
    return ! *this == right;
}

const Node &Node::operator=(const Node & right)
{
    if(&right != this)
    {
        this->crd = right.crd;
        this->child = right.child;
        this->parent = right.parent;
    }
}

const Node &Node::operator=(const QPoint & right)
{
    if(&right != this)
    {
        this->crd = right.crd;
        this->child = NULL;
        this->parent = NULL;
    }
}

const Node &Node::operator=(const CellItem & right)
{
    if(&right != this)
    {
        this->crd = right.crd;
        this->child = right.child;
        this->parent = right.parent;
    }
}
//=====================================================================
// CellItem
//=====================================================================

CellItem::CellItem(QGraphicsRectItem *item,int i, int j) :
    item(item),
    crd(QPoint(i,j))
{}


// операция сравнения с узлами Node
bool CellItem::operator==(const Node & right) const
{
   if(crd == right.crd)
   {
       return true;
   }
}

// операция сравнения с узлами CellItem
bool CellItem::operator==(const CellItem & right) const
{
   if(crd == right.crd)
   {
       return true;
   }
}

bool CellItem::operator!=(const Node & right) const
{
    return ! *this == right;
}

bool CellItem::operator!=(const CellItem & right) const
{
    return ! *this == right;
}
