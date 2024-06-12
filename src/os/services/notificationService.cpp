#include "os/services/notificationService.hpp"

NotificationService::NotificationService() {

}

void NotificationService::start(int w, int h){ 

}

void NotificationService::input(InputType input){ 
    if(contextTakenOver && isRolloutCompleted)
    {
        contextTakenOver = false;
        isRolloutCompleted = false;
        isVerticalRolloutCompleted = false;
        isRolloutStarted = false;
        notificationCurrentX = notificationSidePadding;
        notificationCurrentY = notificationTopPadding;
        OS_SERVICE_API::contextRelease();
    }
}

void NotificationService::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void NotificationService::longPressInput(InputType input)
{

}

void NotificationService::longPressRelease(InputType input)
{

}

void NotificationService::analogInput(int x, int y) {

}

void NotificationService::touchInput(int x, int y) {

}

void NotificationService::update(){
    // Is there any notification not processed which we are not processing yet?
    if(pendingNotifications.size() > 0 && !contextTakenOver)
    {
        // Try to request system context
        contextTakenOver = OS_SERVICE_API::contextOvertake(this);
        if(contextTakenOver)
        {
            currentDisplayedNotification = pendingNotifications.front();
            pendingNotifications.pop();
            isRolloutStarted = true;

            Serial.println("Pushing notification");
        }

    }

}

void NotificationService::render(DisplayProvider& display){
    if(contextTakenOver){
        if(isRolloutStarted && !isRolloutCompleted)
        {
            // Rollout vertical line
            if(!isVerticalRolloutCompleted)
            {
                display.fillRect(notificationCurrentX, 
                    notificationCurrentY, 
                    notificationWidthIncreaseFactor, 
                    notificationWidthIncreaseFactor, 
                    currentDisplayedNotification.bgcolor);

                if(notificationCurrentY >= notificationHeight)
                {
                    isVerticalRolloutCompleted = true;
                    notificationCurrentY = notificationTopPadding;
                }else
                {
                    notificationCurrentY += notificationWidthIncreaseFactor;
                }

            }else { // Then rollout to the right
                display.fillRect(
                    notificationCurrentX,
                    notificationTopPadding,
                    notificationWidthIncreaseFactor,
                    notificationHeight,
                    currentDisplayedNotification.bgcolor);
                
                display.fillRect(
                    notificationCurrentX,
                    notificationTopPadding+35,
                    notificationWidthIncreaseFactor,
                    3,
                    0xFFFF8AE4);


                notificationCurrentX += notificationWidthIncreaseFactor;

                if(notificationCurrentX >= (480 - notificationSidePadding))
                {
                    // Title String
                    display.setTextColor(TFT_WHITE, currentDisplayedNotification.bgcolor);
                    display.setTextFont(2);
                    display.setTextSize(2);
                    display.drawString(currentDisplayedNotification.title, notificationSidePadding+25, notificationTopPadding+3);

                    // display.fillRect(
                    //     notificationSidePadding, 
                    //     notificationTopPadding+35,
                    //     notificationCurrentX-notificationSidePadding,
                    //     3,
                    //     TFT_BLACK);
                    // text string
                    display.setTextSize(1);
                    display.drawString(currentDisplayedNotification.text, notificationSidePadding+5, notificationTopPadding+45);

                    isRolloutCompleted = true;
                }
            }           
        }


        
    }   
}

void NotificationService::forceRender(DisplayProvider& display)
{
    
}

void NotificationService::end(){ 

}

String NotificationService::getAppNameString()
{
    return "NotificationService";
}

uint16_t NotificationService::getBackgroundColor(){
    return TFT_RED;
}

void NotificationService::pushNotification(Notification& notif) {
    pendingNotifications.push(notif);
}