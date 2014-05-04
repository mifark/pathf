#ifndef NODES_H
#define NODES_H
#include "names.h"
#include <QGraphicsRectItem>

struct WaveCell
{
    cellTypes celtype; // тип клетки
    int g; // пусть с начала

    const WaveCell &operator=(const cellType &right)
    {
        this->celtype = right;
        g = 0;
    }
    const WaveCell &operator=(const int &right)
    {
        this->celtype = (cellTypes) right;
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
       const Node &operator=(const Point &);
       const Node &operator=(const CellItem &);
};

class CellItem
{
    public:
        QGraphicsRectItem *item;
        CellItem(QGraphicsRectItem *item,int i, int j);
        QPoint crd;

        // операция сравнения с узлами Node
       bool operator==(const Node &) const;
       bool operator!=(const Node &) const;
       // операция сравнения с узлами CellItem
       bool operator==(const CellItem &) const;
       bool operator!=(const CellItem &) const;
};


#endif // NODES_H
