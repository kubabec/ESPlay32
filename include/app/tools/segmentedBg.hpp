#ifndef SEGMENTEDBG_H
#define SEGMENTEDBG_H

#include <Arduino.h>
#include <queue>

typedef struct
{
    uint16_t x, y, textureID;
}BgSegmentDetails;


class SegmentedBg {

    // 0 - one segment is to be updated
    // BitMask abbreviation
    //      1           1          1            1         1       1      1      1
    //  {TopLeft} {TopRight} {BottomLeft} {BottomRight} {Top} {Bottom} {Left} {Right} 
    uint8_t getTouchedSegmentsMask(uint16_t x, uint16_t y, uint8_t affectedRadius);

    public:
    SegmentedBg(uint8_t aid, uint8_t asegmentWidth, uint8_t asegmentHeight);
    bool isAnySegmentPending();
    BgSegmentDetails getPendingSegmentDetails();
    void goToNextSegment();
    void setStickySegment(uint16_t x, uint16_t y, uint8_t affectedRadius);
    private:
    uint8_t id;
    uint8_t segmentWidth;
    uint8_t segmentHeight;
    bool isWholeBgToBeRepainted = true;
    uint16_t currentX = 0, currentY = 0;
    std::queue<BgSegmentDetails> stickySegments;
};

#endif