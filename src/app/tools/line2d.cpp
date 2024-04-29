#include "app/tools/line2d.h"
#include <math.h>

Line2D::Line2D(float axb, float ayb,float axe, float aye):
    xb(axb), yb(ayb), xe(axe), ye(aye), last_xb(xb),
    last_yb(yb), last_xe(xe),last_ye(ye)
{

}

void Line2D::setLine(float axb, float ayb, float axe, float aye)
{
    last_xb = xb;
    last_yb = yb;
    last_xe = xe;
    last_ye = ye;

    xb = axb;
    yb = ayb;
    xe = axe;
    ye = aye;
}

float Line2D::getLength()
{
    return sqrt((((xe - xb)*(xe - xb)) + ((ye - yb)*(ye - yb))));
}

float Line2D::getX_begin()
{
    return xb;
}

float Line2D::getY_begin()
{
    return yb;
}

float Line2D::getX_end()
{
    return xe;
}

float Line2D::getY_end()
{
    return ye;
}

float Line2D::getLastX_begin()
{
    return last_xb;
}

float Line2D::getLastY_begin()
{
    return last_yb;
}

float Line2D::getLastX_end()
{
    return last_xe;
}

float Line2D::getLastY_end()
{
    return last_ye;
}
