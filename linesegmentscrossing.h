#ifndef LINESEGMENTSCROSSING_H
#define LINESEGMENTSCROSSING_H

#include "point.h"
#include <exception>


#define MIN_TOLERANCE 1e-5     // для коректної роботи мінімальна відстань між точками має бути більша за 3*MIN_TOLERANCE

/*class undefinedLineException: public exception
{

};*/

class LineSegmentsCrossing
{
public:
    LineSegmentsCrossing();

    int solveCrossingProblem (Point p1_1, Point p1_2, Point p2_1, Point p2_2);
    int getLastState();
    Point getLastCrossPoint();
    void clearData();


private:
    int state;   // 0 - undefined state;
                 // 1 - line segments crossed;
                 // 2 - line segments didn't cross
                 // 3 - line segments have one common point at edges
                 // 4 - line segments have infinite number of common points
    Point crossPoint;
};

#endif // LINESEGMENTSCROSSING_H
