#include "app/tools/segmentedBg.hpp"



SegmentedBg::SegmentedBg(uint8_t aid, uint8_t asegmentWidth, uint8_t asegmentHeight) :id(aid), segmentWidth(asegmentWidth), segmentHeight(asegmentHeight) {

}

bool SegmentedBg::isAnySegmentPending() {
    if(isWholeBgToBeRepainted) {
        return true;
    }
    else {
        return (stickySegments.size() > 0);
    }
    return false;
}

BgSegmentDetails SegmentedBg::getPendingSegmentDetails() {
    if(isWholeBgToBeRepainted) {
        return {currentX, currentY, 1};
    }
    if(stickySegments.size() > 0) {
        return stickySegments.front();
    }
    return {0, 0, 1};
}

void SegmentedBg::goToNextSegment() {
    if(isWholeBgToBeRepainted) {
        currentX += segmentWidth;
        if(currentX >= 480) {
            currentX = 0;
            currentY += segmentHeight;
        }
        if(currentY >= 320) {
            currentX = 0;
            currentY = 0;
            isWholeBgToBeRepainted = false;
        }
    }
    if(stickySegments.size() > 0) {
        stickySegments.pop();
    }
}

void SegmentedBg::setStickySegment(uint16_t x, uint16_t y, uint8_t affectedRadius) {
    uint16_t xFactor = x / segmentWidth;
    uint16_t yFactor = y / segmentHeight;
    BgSegmentDetails details;
    details.textureID = 1;

    if(getTouchedSegmentsMask(x, y, affectedRadius) == 0)
    {
        details.x = xFactor * segmentWidth;
        details.y = yFactor * segmentHeight;
        stickySegments.push(details);
    }else {
        if(xFactor > 0) {
            xFactor -= 1;
        }
        if(yFactor > 0) {
            yFactor -= 1;
        }
        details.x = xFactor * segmentWidth;
        details.y = yFactor * segmentHeight;
        stickySegments.push(details);
        details.x += segmentWidth;
        stickySegments.push(details);
        details.y += segmentHeight;
        stickySegments.push(details);
        details.x -= segmentWidth;
        stickySegments.push(details);
    }
}

uint8_t SegmentedBg::getTouchedSegmentsMask(uint16_t x, uint16_t y, uint8_t affectedRadius)
{
    int resultX = ((segmentWidth/2) - affectedRadius);
    int resultY = ((segmentWidth/2) - affectedRadius);

    if(((resultX > 0 ) && (resultY > 0)))
    {
        return 0;
    }

    uint8_t returnMask = 0x00;

    //Check left side collision
    // Collision with left side
    if(resultX < 0)
    {
        // set 0000 0010
        returnMask &= (1 << 1);
    }else if (resultX + affectedRadius)

    return returnMask;
}
