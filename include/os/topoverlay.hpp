#ifndef TOPOVERLAY_H
#define TOPOVERLAY_H
#include "targetDatatypes.hpp"
#include "displayprovider.hpp"

class TopOverlay
{
    enum AppNameTextStatus{
        INACTIVE,
        ACTIVATION_PENDING,
        DEACTIVATION_PENDING,
        ACTIVE,
        SLIDE_ANIMATION_ON_PENDING,
        SLIDE_ANIMATION_OFF_PENDING,
        ALIGNED_TO_RIGHT
    };

    uint32_t overlayBackgroundColor = TFT_GREENYELLOW;
    bool isActive = false;
    bool needsUpdate = false;
    const uint16_t overlayHeight = 30;
    uint16_t overlayWidth = 480;
    String overlayText = "Example text";
    uint16_t overlayTextX = 480/2;


    AppNameTextStatus mainText = INACTIVE;
    //bool isActivationAnimationPending = false;
    //bool isDeactivationAnimationPending = false;

    void activationAnimation(DisplayProvider& display);
    void deactivationAnimation(DisplayProvider& display);

    // app text mode

    String appString = "AppString";
    int AppTextY = -30;
    uint16_t appTextColor = TFT_BLACK;
    void rightSlideAnimationOn(DisplayProvider& display);
    void rightSlideAnimationOff(DisplayProvider &display);

    
    public:

    bool isActivationAnimation();
    void activate();
    void deactivate();
    void setOverlayText(const String& newText);
    void render(DisplayProvider& display);
    void forceRender(DisplayProvider& display);
    uint16_t getHeight();
    bool isHidingAnimationPending();

    // Additional app text
    bool activateAppTextMode(String appText, uint32_t textColor);
    bool deactivateAppTextMode();

    TopOverlay();

};

#endif
