#ifndef NAMES_H
#define NAMES_H

namespace clNames
{
    enum mapElements{
        passable = 0,
        trees,
        swamp,
        water,
        outOfBounds,
        way
    };

    enum cellTypes{
        empty = 0,
        start = 1,
        stop = 2,
        wall = 3
    };
}

#endif // NAMES_H
