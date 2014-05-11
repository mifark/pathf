#ifndef NODES_H
#define NODES_H
#include "names.h"
#include <QGraphicsRectItem>

class CellItem;

struct WaveCell
{
    clNames::cellTypes celtype; // тип клетки
    int g; // пусть с начала

    const WaveCell &operator=(const clNames::cellTypes &right)
    {
        this->celtype = right;
        g = 0;
    }
    const WaveCell &operator=(const int &right)
    {
        this->celtype = (clNames::cellTypes) right;
        g = 0;
    }
};

class Node
{
    /// \brief конструктор
    public:
        Node(QPoint crd, Node *parent, Node *child);
        Node();
        ~Node();

        QPoint crd;
        Node *parent;
        Node *child;

        double g; // путь от начала
       // double h; // путь эвристической функции

        // операция сравнения с узлами Node
       bool operator==(const Node &) const;
       bool operator!=(const Node &) const;

       // операция сравнения с узлами CellItem
       bool operator==(const CellItem &) const;
       bool operator!=(const CellItem &) const;

       const Node &operator=(const Node &);
       const Node &operator=(const QPoint &);
       const Node &operator=(const CellItem &);
};

class CellItem
{
    public:
        QGraphicsRectItem *item;
        CellItem();
        CellItem(QGraphicsRectItem *item,clNames::cellTypes type, int i, int j);
        QPoint crd;
        clNames::cellTypes celtype; // тип клетки

        // операция сравнения с узлами Node
       bool operator==(const Node &) const;
       bool operator!=(const Node &) const;
       // операция сравнения с узлами CellItem
       bool operator==(const CellItem &) const;
       bool operator!=(const CellItem &) const;
};


#endif // NODES_H
