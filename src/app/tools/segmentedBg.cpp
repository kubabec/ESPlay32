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

void SegmentedBg::setStickySegment(uint16_t x, uint16_t y) {
    uint16_t xFactor = x / segmentWidth;
    uint16_t yFactor = y / segmentHeight;
    BgSegmentDetails details;
    details.textureID = 1;
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
