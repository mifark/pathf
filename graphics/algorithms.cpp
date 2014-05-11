#include "algorithms.h"

PathAlgorithms::PathAlgorithms()
{

}

void PathAlgorithms::start_WaveSearch()
{
    if(map.size()!=0)
    {
        QList<QPoint> oldWave;
        QList<QPoint> wave;
        oldWave.append(start);
        int step = 0;
        map[start.x()][start.y()].g = 0;
        while(oldWave.size()>0 || step!=-1)
        {
            ++step;
            wave.clear();
            for(QList<QPoint>::iterator i = oldWave.begin() ; i!=oldWave.end(); ++i)
            {
                for(int d=0; d<4; ++d)
                {
                    int nx = i->x() + dx[d];
                    int ny = i->y() + dy[d];
                    if(map[nx][ny].celtype != clNames::wall)
                    {
                        wave.push_back(QPoint(nx,ny));
                        map[nx][ny].g = step;
                        if(nx==goal.x() && ny==goal.y())
                        {
                            oldWave.clear();
                            wave.clear();
                            step = -1;
                            break;
                        }
                    }
                }
            }
            oldWave = wave;
        }
    }
}

void PathAlgorithms::makePath()
{
    int x = goal.x();
    int y = goal.y();
    QList<QPoint> returnPath;
    returnPath.clear();
    returnPath.push_back(goal);
    while(map[x][y].g !=0)
    {
        for (int d = 0; d < 4; ++d)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (map[x][y].g - 1 == map[nx][ny].g)
            {
                x = nx;
                y = ny;
                returnPath.push_back(QPoint(x,y));
                break;
            }
        }
    }
}

void PathAlgorithms::setMap(QList<QList<WaveCell> > map)
{
    this->map.clear();
    this->map.append(map);
}

void PathAlgorithms::setPoints(QPoint start, QPoint goal)
{
    this->start = start;
    this->goal = goal;
}

QList<QPoint> PathAlgorithms::getPath()
{
    return returnPath;
}
