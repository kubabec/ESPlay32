#include <app/tools/gunshot.h>

GunShot::GunShot(Vector2D& apos, Vector2D& ashotDir, uint16_t attl) :
    pos(apos), dir(ashotDir), ttl(attl)
{

}

void GunShot::update()
{
    if(ttl > 0)
    {
        lastPos = pos;
        Vector2D posPrim = pos + (dir * acceleration);
        if(posPrim.getY() > minY)
        {
            pos = posPrim;
        }else
        {
            isDestroyed = true;
        }
        ttl --;
    }else
    {
        isDestroyed = true;
    }
}

void GunShot::draw(DisplayProvider &display)
{
    display.fillCircle(lastPos.getX(), lastPos.getY(), 2, TFT_BLACK);
    if(!isDestroyed){
        display.fillCircle(pos.getX(), pos.getY(), 2, 0xFFFFFF);
    }else
    {
        display.fillCircle(pos.getX(), pos.getY(), 2, TFT_BLACK);
    }
}

bool GunShot::destroyed()
{
    return isDestroyed;
}

void GunShot::destroy()
{
    isDestroyed = true;
}

Vector2D GunShot::getPos()
{
    return pos;
}


