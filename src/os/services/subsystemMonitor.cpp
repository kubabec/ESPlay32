#include "os/services/subsystemMonitor.hpp"
#include "os/portableos.hpp"


SubsystemMonitorService::SubsystemMonitorService(SubsystemOverview* subsystemOverview)
{
    subsystemOverviewPtr = subsystemOverview;
}

void SubsystemMonitorService::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void SubsystemMonitorService::start(int w, int h){ 

}


void SubsystemMonitorService::longPressInput(InputType input)
{

}

void SubsystemMonitorService::longPressRelease(InputType input)
{

}

void SubsystemMonitorService::analogInput(int x, int y) {

}

void SubsystemMonitorService::input(InputType input) {

}


void SubsystemMonitorService::touchInput(int x, int y) {

}

void SubsystemMonitorService::handleSubsystemDisconnectionIfWasConnectedBefore()
{
    /* Subsystem is not communicating and was before */
    if(currentTickValue > numberOfTicksToDisconnect && lastSubsystemCommunicatingFlag)
    {
        subsystemOverviewPtr->isCommunicating = false;
        subsystemOverviewPtr->credentials.ssid = "none";
        subsystemOverviewPtr->credentials.password = "none";
        subsystemOverviewPtr->data.wasWiFiRequestedFlag = false;
        subsystemOverviewPtr->data.isWiFiConnectedFlag = false;
        subsystemOverviewPtr->data.ipOctet1 = 0;
        subsystemOverviewPtr->data.ipOctet2 = 0;
        subsystemOverviewPtr->data.ipOctet3 = 0;
        subsystemOverviewPtr->data.ipOctet4 = 0;

        Notification subsystemNotConnectedNotification{
            .title = "Ethernet slave not connected!",
            .text = "No connection to secondary ESP32 system",
            .bgcolor = TFT_RED
        };
        OS_API::pushNotification(subsystemNotConnectedNotification);

        lastSubsystemCommunicatingFlag = false;
    }
}

void SubsystemMonitorService::handleWiFiDisconnection()
{
    // We need slave to communicate if we want to handle WiFi disconnection
    if(lastSubsystemCommunicatingFlag){
        if(
            lastSubsystemData.wasWiFiRequestedFlag && // WiFi was requested
            lastSubsystemData.isWiFiConnectedFlag && // WiFi was connected successfully before
            // subsystemOverviewPtr->data.wasWiFiRequestedFlag && // No disconnection was requested
            !subsystemOverviewPtr->data.isWiFiConnectedFlag // But currently it is not connected anymore
        ){
            Notification subsystemNotConnectedNotification{
                .title = "WiFi connection lost!",
                .text = "You are no longer connected to " + lastValidCredentials.ssid,
                .bgcolor = 0xF380
            };
            OS_API::pushNotification(subsystemNotConnectedNotification);
        }
    }
}

void SubsystemMonitorService::detectSubsystemMissingSinceStartup()
{
    if(!subsystemMissingSinceStartup){
        if(currentTickValue > numberOfTicksToDisconnect)
        {
            subsystemOverviewPtr->isCommunicating = false;
            subsystemOverviewPtr->credentials.ssid = "none";
            subsystemOverviewPtr->credentials.password = "none";
            subsystemOverviewPtr->data.wasWiFiRequestedFlag = false;
            subsystemOverviewPtr->data.isWiFiConnectedFlag = false;
            subsystemOverviewPtr->data.ipOctet1 = 0;
            subsystemOverviewPtr->data.ipOctet2 = 0;
            subsystemOverviewPtr->data.ipOctet3 = 0;
            subsystemOverviewPtr->data.ipOctet4 = 0;

            Notification missingSinceStartup{
                .title = "No secondary ESP32 detected!",
                .text = "Check connection with secondary ESP32 WiFi gateway if you want to proceed with network features.",
                .bgcolor = TFT_LIGHTGREY
            };
            OS_API::pushNotification(missingSinceStartup);

            subsystemMissingSinceStartup = true;
        }
    }
}

void SubsystemMonitorService::updateSubsystemDataFlags()
{
    if(subsystemOverviewPtr != nullptr){
        lastSubsystemData.wasWiFiRequestedFlag = subsystemOverviewPtr->data.wasWiFiRequestedFlag;
        lastSubsystemData.isWiFiConnectedFlag = subsystemOverviewPtr->data.isWiFiConnectedFlag;

        if(subsystemOverviewPtr->data.isWiFiConnectedFlag)
        {
            lastValidCredentials.ssid = subsystemOverviewPtr->credentials.ssid;
            lastValidCredentials.password = subsystemOverviewPtr->credentials.password;
        }
    }
    
}

void SubsystemMonitorService::detectNetworkConnection()
{
    if(subsystemOverviewPtr->data.wasWiFiRequestedFlag)
    {
        if(!lastSubsystemData.isWiFiConnectedFlag && subsystemOverviewPtr->data.isWiFiConnectedFlag &&
            subsystemOverviewPtr->credentials.ssid != "none")
        {
            Notification connectedNotification {
                .title = "WiFi connected!",
                .text = "You have been connected to " + subsystemOverviewPtr->credentials.ssid,
                .bgcolor = TFT_GREENYELLOW
            };
            OS_API::pushNotification(connectedNotification);
        }
    }

}

void SubsystemMonitorService::update(){
    currentTickValue ++;
    static uint8_t cycles15Wait = 0;
    cycles15Wait ++;
    detectSubsystemMissingSinceStartup();

    handleSubsystemDisconnectionIfWasConnectedBefore();
    if(cycles15Wait >= 15){
        handleWiFiDisconnection();
        detectNetworkConnection();

        updateSubsystemDataFlags();

        cycles15Wait = 0;
    }

}

void SubsystemMonitorService::subsystemStatusReceived(){
    currentTickValue = 0;
    lastSubsystemCommunicatingFlag = true;


    // Do not detect subsystem missing since startup anymore
    subsystemMissingSinceStartup = true;
}

void SubsystemMonitorService::render(DisplayProvider& display){
    
}

void SubsystemMonitorService::forceRender(DisplayProvider& display)
{
    
}

void SubsystemMonitorService::end(){ 

}


String SubsystemMonitorService::getAppNameString()
{
    return "SubsystemMonitor";
}

uint16_t SubsystemMonitorService::getBackgroundColor(){
    return TFT_BLACK;
}
