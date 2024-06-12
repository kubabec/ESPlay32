#ifndef SEGMENTEDBG_H
#define SEGMENTEDBG_H

typedef struct
{
    int16_t x, y, textureID;
}BgSegmentDetails;


class SegmentedBg {
    public:
    SegmentedBg(uint8_t id);
    bool isAnySegmentPending();
    BgSegmentDetails getPendingSegmentDetails();
    void goToNextSegment();
};

#endif