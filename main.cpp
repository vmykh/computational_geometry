#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <iomanip>

#include "point.h"
#include "linesegmentscrossing.h"
#include "angledeterminer.h"

using std::cout;
using std::cin;
using std::endl;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //cout << "Enter coordinates of point!";
   /* Point p1(1, 1);
    Point p2(1, 5);
    Point p3(0, 2);
    Point p4(2, 4);
    LineSegmentsCrossing lineSegmentsCrossing;*/




    /*
    Point p1(-1.5, -5.75);
    Point p2(-3, -6.5);
    Point p3(-1, -5.5);
    Point p4(-0.25, -5.125);
    */



    //lineSegmentsCrossing.solveCrossingProblem(p1, p2, p3 ,p4);




    Vector v1(1, 0.1);
    Vector v2(1, -1);

    angleDeterminer angleDet;
    cout << angleDet.determineAngle(v1, v2);

    return a.exec();
}
