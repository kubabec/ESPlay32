#include "os/topoverlay.hpp"
#include "os/portableos.hpp"

TopOverlay::TopOverlay()
{
    overlayBackgroundColor = PortableOS::getSystemColor(MOTIVE_COLOR);
}

void TopOverlay::activate(){
    mainText = ACTIVATION_PENDING;
    //isActivationAnimationPending = true;
}

void TopOverlay::deactivate(){
    mainText = DEACTIVATION_PENDING;
    //isDeactivationAnimationPending = true;

}

bool TopOverlay::isActivationAnimation()
{
    if(mainText == ACTIVATION_PENDING || mainText == DEACTIVATION_PENDING ||
            mainText == SLIDE_ANIMATION_ON_PENDING || mainText == SLIDE_ANIMATION_OFF_PENDING)  //isActivationAnimationPending || isDeactivationAnimationPending)
    {
        return true;
    }

    return false;
}

void TopOverlay::activationAnimation(DisplayProvider& display)
{
    static uint16_t currentY = 0;
    const uint16_t yIncrement = 2;

    if(currentY <= overlayHeight - yIncrement){
        // Animation in progress
        //display.fillRect(0, currentY, overlayWidth, yIncrement, overlayBackgroundColor);
        display.setTextColor(TFT_BLACK, overlayBackgroundColor);
        display.drawString(overlayText, overlayTextX, currentY-25);
        display.fillRect(0, currentY, overlayWidth, yIncrement, overlayBackgroundColor);
        display.fillRect(0, currentY-27, overlayWidth, 2, overlayBackgroundColor);

        //Restore background color
        display.setTextColor(TFT_WHITE, TFT_BLACK);

        currentY += yIncrement;

    }else
    {
        //isActivationAnimationPending = false;
        mainText = ACTIVE;
        currentY = 0;

       // activateAppTextMode("Score : 10 AMO: 4", TFT_RED);
    }
}

void TopOverlay::deactivationAnimation(DisplayProvider& display)
{
    static uint16_t currentY = overlayHeight;
    const uint16_t yIncrement = 5;

    if(currentY > 0){
        // Animation in progress
        display.fillRect(0, 0, overlayWidth, currentY, overlayBackgroundColor);

        display.setTextColor(TFT_BLACK);
        display.drawString(overlayText, overlayTextX, currentY-25);
        display.fillRect(0, currentY-5, overlayWidth, 5, PortableOS::getSystemColor(BG_COLOR));
        currentY -= yIncrement;

    }else
    {
        //isDeactivationAnimationPending = false;
        mainText = INACTIVE;
        currentY = overlayHeight;

        // Corner case for disable with app text on
        AppTextY = -30;
    }
}

void TopOverlay::rightSlideAnimationOn(DisplayProvider &display)
{
    const uint32_t maxTextX = 340;
    const uint8_t incrementPx = 5;

    const int maxAppTextY = overlayHeight - 27;

    if(overlayTextX < maxTextX){
        overlayTextX += incrementPx;
    }else
    {
        // ACTIVE

        if(AppTextY >= maxAppTextY)
        {
            mainText = ALIGNED_TO_RIGHT;
        }

        // border line
        display.fillRect(overlayTextX - 8,
                         0, 1, overlayHeight,
                         TFT_BLACK);


    }

    display.setTextColor(TFT_BLACK, overlayBackgroundColor);
    display.drawString(overlayText, overlayTextX, overlayHeight - 27);
    display.fillRect(overlayTextX - incrementPx, overlayHeight - 27, incrementPx, 20, overlayBackgroundColor);

    // APP TEXT ANIMATION


    if(AppTextY < maxAppTextY)
    {
        AppTextY ++;
    }

    display.setTextColor(appTextColor, overlayBackgroundColor);
    display.drawString(appString, 10, AppTextY);

}

void TopOverlay::rightSlideAnimationOff(DisplayProvider &display)
{
    const uint32_t minTextX = (225 - ((overlayText.length()/2) * 10));
    const uint8_t incrementPx = 5;

    const int minAppTextY =  -30;

    if(overlayTextX >= 340)
    {
        // border line
        display.fillRect(overlayTextX - 8,
                         0, 1, overlayHeight,
                         overlayBackgroundColor);
    }

    if(overlayTextX > minTextX){
        overlayTextX -= incrementPx;
    }else
    {
        if(AppTextY <= minAppTextY)
        {
            mainText = ACTIVE;
        }
    }

    display.setTextColor(TFT_BLACK, overlayBackgroundColor);
    display.drawString(overlayText, overlayTextX, overlayHeight - 27);
    display.fillRect(overlayTextX - incrementPx, overlayHeight - 27, incrementPx, 20, overlayBackgroundColor);

    // APP TEXT ANIMATION


    if(AppTextY > minAppTextY)
    {
        AppTextY --;
    }

    display.setTextColor(appTextColor, overlayBackgroundColor);
    display.drawString(appString, 10, AppTextY);


}


bool TopOverlay::isHidingAnimationPending()
{
    return (mainText == DEACTIVATION_PENDING);// isDeactivationAnimationPending;
}

bool TopOverlay::activateAppTextMode(String appText, uint32_t textColor)
{
    if(mainText == ACTIVE || mainText == ALIGNED_TO_RIGHT)
    {
        mainText = SLIDE_ANIMATION_ON_PENDING;
        appString = appText;
        appTextColor = textColor;
        return true;
    }

    return false;
}

bool TopOverlay::deactivateAppTextMode()
{
//    if(mainText == ALIGNED_TO_RIGHT)
//    {
    mainText = SLIDE_ANIMATION_OFF_PENDING;
    return true;
//    }

//    return false;
}


void TopOverlay::render(DisplayProvider& display){

    if(isActivationAnimation())
    {
        overlayBackgroundColor = PortableOS::getSystemColor(MOTIVE_COLOR);
        display.setTextFont(4);
        display.setTextSize(1);
        // display.drawString(overlayText, overlayTextX, 5);

        if(mainText == ACTIVATION_PENDING)// isActivationAnimationPending)
        {
            activationAnimation(display);
        }

        if(mainText == DEACTIVATION_PENDING)
        {
            deactivationAnimation(display);
        }

        if(mainText == SLIDE_ANIMATION_ON_PENDING)
        {
            rightSlideAnimationOn(display);
        }

        if(mainText == SLIDE_ANIMATION_OFF_PENDING)
        {
            rightSlideAnimationOff(display);
        }
    }
}

void TopOverlay::setOverlayText(const String& newText)
{
    overlayText = newText;
    overlayText = overlayText + " ";
    overlayTextX = 225 - ((overlayText.length()/2) * 10);
}

uint16_t TopOverlay::getHeight()
{
    return overlayHeight;
}
