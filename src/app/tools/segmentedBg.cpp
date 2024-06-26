#include "app/tools/segmentedBg.hpp"



SegmentedBg::SegmentedBg(uint8_t aid, uint8_t asegmentWidth, uint8_t asegmentHeight) :id(aid), segmentWidth(asegmentWidth), segmentHeight(asegmentHeight) {

}

void SegmentedBg::forceRepaintAll()
{
    isWholeBgToBeRepainted = true;
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

    // Add segment where sticky point middle is
    const uint16_t mainSegmentX = xFactor * segmentWidth;
    const uint16_t mainSegmentY = yFactor * segmentHeight;

    details.x = mainSegmentX;
    details.y = mainSegmentY;
    stickySegments.push(details);

    // Is there any other segment affected?
    uint8_t affectedNeighboursMask = getTouchedSegmentsMask(x, y, affectedRadius);
    if(affectedNeighboursMask > 0)
    {
        const bool isTopNeighborAffected = affectedNeighboursMask & 0b00000001;
        const bool isBottomNeighborAffected = affectedNeighboursMask & 0b00000010;
        const bool isLeftNeighborAffected = affectedNeighboursMask & 0b00000100;
        const bool isRightNeighborAffected = affectedNeighboursMask & 0b00001000;
        const bool isTopLeftAffected = affectedNeighboursMask & 0b00010000;
        const bool isTopRightAffected = affectedNeighboursMask & 0b00100000;
        const bool isBottomLeftAffected = affectedNeighboursMask & 0b01000000;
        const bool isBottomRightAffected = affectedNeighboursMask & 0b10000000;

        if(isTopNeighborAffected)
        {
            stickySegments.push(BgSegmentDetails{mainSegmentX, (uint16_t)(mainSegmentY - segmentHeight), 1});

            // stickySegments.push(BgSegmentDetails{mainSegmentX, (uint16_t)(mainSegmentY - 2*segmentHeight), 1});

        }

        if(isBottomNeighborAffected)
        {
            stickySegments.push(BgSegmentDetails{mainSegmentX, (uint16_t)(mainSegmentY + segmentHeight), 1});

            // stickySegments.push(BgSegmentDetails{mainSegmentX, (uint16_t)(mainSegmentY + 2*segmentHeight), 1});
        }

        if(isLeftNeighborAffected)
        {
            stickySegments.push(BgSegmentDetails{(uint16_t)(mainSegmentX - segmentWidth), mainSegmentY, 1});

            // stickySegments.push(BgSegmentDetails{(uint16_t)(mainSegmentX - 2*segmentWidth), mainSegmentY, 1});
        }

        if(isRightNeighborAffected)
        {
            stickySegments.push(BgSegmentDetails{(uint16_t)(mainSegmentX + segmentWidth), mainSegmentY, 1});

            // stickySegments.push(BgSegmentDetails{(uint16_t)(mainSegmentX + 2*segmentWidth), mainSegmentY, 1});
        }

        if(isTopLeftAffected)
        {
            stickySegments.push(BgSegmentDetails{
                (uint16_t)(mainSegmentX - segmentWidth), 
                (uint16_t)(mainSegmentY - segmentHeight), 
                1
            });
        }

        if(isTopRightAffected)
        {
            stickySegments.push(BgSegmentDetails{
                (uint16_t)(mainSegmentX + segmentWidth), 
                (uint16_t)(mainSegmentY - segmentHeight), 
                1
            });
        }

        if(isBottomLeftAffected)
        {
            stickySegments.push(BgSegmentDetails{
                (uint16_t)(mainSegmentX - segmentWidth), 
                (uint16_t)(mainSegmentY + segmentHeight), 
                1
            });
        }

        if(isBottomRightAffected)
        {
            stickySegments.push(BgSegmentDetails{
                (uint16_t)(mainSegmentX + segmentWidth), 
                (uint16_t)(mainSegmentY + segmentHeight), 
                1
            });
        }


    }
}

uint8_t SegmentedBg::getTouchedSegmentsMask(uint16_t x, uint16_t y, uint8_t affectedRadius)
{
    uint16_t absoluteX = x % segmentWidth; // Get ABS of X -> e.g.  134 % 30 (width) => 14
    uint16_t absoluteY = y % segmentHeight; 


    Serial.println("ABS:" + String(absoluteX) + ", " + String(absoluteY));


    bool leftAffected = ((int)(absoluteX - affectedRadius) <= 2);
    bool rightAffected = ((absoluteX + affectedRadius) > segmentWidth);
    bool topAffected = ((int)(absoluteY - affectedRadius) <= 2);
    bool bottomAffected = ((absoluteY + affectedRadius) > segmentHeight);


    uint8_t isTopNeighborAffected = topAffected ?               0b00000001 : 0x00;
    uint8_t isBottomNeighborAffected = bottomAffected ?         0b00000010 : 0x00;
    uint8_t isLeftNeighborAffected = leftAffected ?             0b00000100 : 0x00;
    uint8_t isRightNeighborAffected = rightAffected ?           0b00001000 : 0x00;

    // corner neighbours check
    uint8_t isTopLeftAffected = topAffected && leftAffected ?   0b00010000 : 0x00;
    uint8_t isTopRightAffected = topAffected && rightAffected?  0b00100000 : 0x00;
    uint8_t isBottomLeftAffected = bottomAffected && leftAffected ?0b01000000 : 0x00;
    uint8_t isBottomRightAffected = bottomAffected&&rightAffected? 0b10000000 : 0x00;


    uint8_t returnMask = 0x00;

    // apply masks
    returnMask |= isTopNeighborAffected;
    returnMask |= isBottomNeighborAffected;
    returnMask |= isLeftNeighborAffected;
    returnMask |= isRightNeighborAffected;
    returnMask |= isTopLeftAffected;
    returnMask |= isTopRightAffected;
    returnMask |= isBottomLeftAffected;
    returnMask |= isBottomRightAffected;

    Serial.println(String(returnMask));

    return returnMask;
}
