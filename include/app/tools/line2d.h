#ifndef LINE2D_H
#define LINE2D_H


class Line2D
{
    float xb, yb, xe, ye;

    float last_xb, last_yb, last_xe, last_ye;
public:
    Line2D(float axb, float ayb,float axe, float aye);

    void setLine(float axb, float ayb,float axe, float aye);

    float getLength();

    float getX_begin();
    float getY_begin();
    float getX_end();
    float getY_end();

    float getLastX_begin();
    float getLastY_begin();
    float getLastX_end();
    float getLastY_end();
};

#endif // LINE2D_H
