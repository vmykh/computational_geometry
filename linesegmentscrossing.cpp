#include "linesegmentscrossing.h"
#include <QDebug>
#include <iostream>
#include <cmath>



LineSegmentsCrossing::LineSegmentsCrossing()
    :crossPoint(0,0), state(0)
{
}

int LineSegmentsCrossing::solveCrossingProblem(Point p1_1, Point p1_2, Point p2_1, Point p2_2)
{
    double a1 = p1_2.y - p1_1.y;
    double b1 = p1_1.x - p1_2.x;
    double c1 = - p1_1.y * b1 - p1_1.x * a1;

    double a2 = p2_2.y - p2_1.y;
    double b2 = p2_1.x - p2_2.x;
    double c2 = - p2_1.y * b2 - p2_1.x * a2;

    //double q = 1e-5;

    try
    {
        if ( fabs(a1) < 2 * MIN_TOLERANCE && fabs(b1) < 2 * MIN_TOLERANCE)
        {
            throw "Line Segment 1 undefined." ;
        }
        if ( fabs(a2) < 2 * MIN_TOLERANCE && fabs(b2) < 2 * MIN_TOLERANCE)
        {
            throw "Line Segment 2 undefined." ;
        }
    }
    catch (const char* error)
    {
        std::cerr << "An exception occured: " << error << "\n\n\n" << endl;
        /*throw error;*/
        state = 0;
        return 0;
    }

    qDebug() << "a1 = " << a1 << "     b1 = " << b1 << "     c1 = " << c1;
    qDebug() << "\na2 = " << a2 << "     b2 = " << b2 << "     c2 = " << c2;



    double system_det = a1 * b2 - b1 * a2;
    if ( fabs(system_det) > MIN_TOLERANCE)
    {
        crossPoint.x = ( - b2 * c1 + b1 * c2 ) / system_det;
        crossPoint.y = ( a2 * c1 - a1 * c2 ) / system_det;

        qDebug() << "\nx = " << crossPoint.x << "     y = " << crossPoint.y;



        // NEW 4.03.2014    START
        auto arePointsSame = [&](Point p1)
        {
            if ( crossPoint.distance(p1) < MIN_TOLERANCE )
                return true;
            else
                return false;
        };

        if  (  ( arePointsSame(p1_1) && arePointsSame(p2_1))
            || ( arePointsSame(p1_1) && arePointsSame(p2_2))
            || ( arePointsSame(p1_2) && arePointsSame(p2_1))
            || ( arePointsSame(p1_2) && arePointsSame(p2_2))
               )
        {
            state = 3;
            qDebug() << "\nstate = " << 3 << "Line segments have one common point at edges.\n";
            return 3;
        }
         // NEW 4.03.2014    END



        //NEW 4.03.2014    +- MIN_TOLEARNCE 4*4*x  (next ~10 lines

        if (      (crossPoint.x > p1_1.x - MIN_TOLERANCE && crossPoint.x < p1_2.x + MIN_TOLERANCE)    //якщо точка перетину належить першому відрізку
              ||  (crossPoint.x > p1_2.x - MIN_TOLERANCE && crossPoint.x < p1_1.x + MIN_TOLERANCE)
              ||  (crossPoint.y > p1_1.y - MIN_TOLERANCE && crossPoint.y < p1_2.y + MIN_TOLERANCE)
              ||  (crossPoint.y > p1_2.y - MIN_TOLERANCE  && crossPoint.y < p1_1.y + MIN_TOLERANCE)
                )
        {
            if (      (crossPoint.x > p2_1.x - MIN_TOLERANCE  && crossPoint.x < p2_2.x + MIN_TOLERANCE)    //і якщо точка перетину належить і другому відрізку
                      ||  (crossPoint.x > p2_2.x - MIN_TOLERANCE  && crossPoint.x < p2_1.x + MIN_TOLERANCE)
                      ||  (crossPoint.y > p2_1.y - MIN_TOLERANCE  && crossPoint.y < p2_2.y + MIN_TOLERANCE)
                      ||  (crossPoint.y > p2_2.y - MIN_TOLERANCE  && crossPoint.y < p2_1.y + MIN_TOLERANCE)
                        )
            {
                state = 1;
                qDebug() << "\nstate = " << 1 << "Line segments crossed.\n";
                return 1;
            }
        }
        state = 2;
        qDebug() << "\nstate = " << 1 << "Line segments didn't cross.\n";
        return 2;
    }
    else
    {
        double k;                           //коефіціент пропорційності
        if ( fabs(a1) > MIN_TOLERANCE )
        {
            k = a2 / a1;
        }
        else
        {
            k = b2 / b1;
        }

        if (   fabs( c2 - ( c1 * k ) )  > MIN_TOLERANCE  )     // відрізки паралельні і не лежать на одній прямій
        {
            state = 2;
            qDebug() << "\nstate = " << 2 << "Line segments didn't cross.\n";
            return 2;
        }
        else
        {
            auto swap = [](Point &p1, Point &p2)
            {
                Point temp = p2;
                p2 = p1;
                p1 = temp;
            };

            if ( fabs(a1) > fabs(b1) )  // якщо кут нахилу прямої більше за 45 градусів  || пряма скоріш вертикальна, ніж горизонтальна
            {

                if (p1_2.y < p1_1.y)              //міняємо точки країв відрізків місцями,
                {                                 //так щоб у кожного з відрізків у точки
                    swap(p1_1, p1_2);             //з меншою ігриковою координатою був менший індекс
                }
                if (p2_2.y < p2_1.y)
                {
                    swap(p2_1, p2_2);
                }

                if (   ( ( p2_2.y - p1_1.y ) < - MIN_TOLERANCE )
                       || ( (p2_1.y - p1_2.y) > MIN_TOLERANCE )
                       )
                {
                    state = 2;
                    qDebug() << "\nstate = " << 2 << "Line segments didn't cross.\n";
                    return 2;
                }
                else
                {
                    if (   (    fabs( p2_2.y - p1_1.y ) < MIN_TOLERANCE && ( p2_1.y < p1_1.y )  )    )
                    {
                        state = 3;
                        qDebug() << "\nstate = " << 3 << "Line segments have one common point at edges.\n";
                        crossPoint = p1_1;
                        return 3;

                    }
                    else
                    {
                        if (    fabs( p2_1.y - p1_2.y ) < MIN_TOLERANCE && ( p2_2.y > p1_2.y)   )
                        {
                            state = 3;
                            qDebug() << "\nstate = " << 3 << "Line segments have one common point at edges.\n";
                            crossPoint = p1_2;
                            return 3;
                        }
                        else
                        {
                            state = 4;
                            qDebug() << "\nstate = " << 4 << "Line segments have infinine number of common points.\n";
                            return 4;
                        }
                    }
                }


            }
            else  // якщо пряма скоріш горизонтальна, ніж вертикальна
            {
                if (p1_2.x < p1_1.x)              //міняємо точки країв відрізків місцями,
                {                                 //так щоб у кожного з відрізків у точки
                    swap(p1_1, p1_2);             //з меншою ігриковою координатою був менший індекс
                }
                if (p2_2.x < p2_1.x)
                {
                    swap(p2_1, p2_2);
                }

                if (   ( ( p2_2.x - p1_1.x ) < - MIN_TOLERANCE )
                       || ( (p2_1.x - p1_2.x) > MIN_TOLERANCE )
                       )
                {
                    state = 2;
                    qDebug() << "\nstate = " << 2 << "Line segments didn't cross.\n";
                    return 2;
                }
                else
                {
                    if (   (    fabs( p2_2.x - p1_1.x ) < MIN_TOLERANCE && ( p2_1.x < p1_1.x )  )    )
                    {
                        state = 3;
                        qDebug() << "\nstate = " << 3 << "Line segments have one common point at edges.\n";
                        crossPoint = p1_1;
                        return 3;

                    }
                    else
                    {
                        if (    fabs( p2_1.x - p1_2.x ) < MIN_TOLERANCE && ( p2_2.x > p1_2.x)   )
                        {
                            state = 3;
                            qDebug() << "\nstate = " << 3 << "Line segments have one common point at edges.\n";
                            crossPoint = p1_2;
                            return 3;
                        }
                        else
                        {
                            state = 4;
                            qDebug() << "\nstate = " << 4 << "Line segments have infinine number of common points.\n";
                            return 4;
                        }
                    }
                }
            }
        }
    }
}

int LineSegmentsCrossing::getLastState()
{
    return state;
}

Point LineSegmentsCrossing::getLastCrossPoint()
{
    if (state == 1 || state == 3)
    {
        return crossPoint;
    }
    else
        throw "Line segments don't have single cross point";

}

void LineSegmentsCrossing::clearData()
{
    state = 0;
}
