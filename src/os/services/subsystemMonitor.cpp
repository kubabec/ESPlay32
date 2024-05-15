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

void SubsystemMonitorService::update(){
    currentTickValue ++;

    /* Subsystem is not communicating */
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
    }
}

void SubsystemMonitorService::subsystemStatusReceived(){
    currentTickValue = 0;
}

void SubsystemMonitorService::render(DisplayProvider& display){
    
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
