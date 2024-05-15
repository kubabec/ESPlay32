#include "os/menu.hpp"
#include "os/portableos.hpp"

Menu::Menu(std::vector<String> a_menuElements) {

    menuElements = a_menuElements;
}

void Menu::registerChoiceDoneCallback(void (*a_choiceDoneCallback)(int8_t))
{
    // Register callback for future use
    choiceDoneCallback = a_choiceDoneCallback;
}

void Menu::registerChoiceDonePollValue(int8_t* choice)
{
    choicePoll = choice;
}

void Menu::requestActivation(){
    activationRequested = true;
}

void Menu::drawSelectionLines(DisplayProvider& display)
{
    if(!isNextSelectedAnimation){
        // We have to display TOP green line if there is no 
        // NEXT selection animation pending (top line is dissapearing)
        display.fillRect(0, currentSelectedTopLine.y, 480, 3, PortableOS::getSystemColor(SELECTION_COLOR));
    }

    if(!isPreviousSelectedAnimation){
        // We have to display BOTTOM green line if there is no 
        // PREVIOUS selection animation pending (bottom line is dissapearing)
        display.fillRect(0, currentSelectedBottomLine.y, 480, 3, PortableOS::getSystemColor(SELECTION_COLOR));
    }

    // Process NEXT selection animation
    if(isNextSelectedAnimation)
    {
        // Size of single Green line length change
        const int sizingFactor = 96;
        // Point where black line starts
        static int coverX = 480 - sizingFactor;
        // length of black line covering green one
        static int blackLineLength = sizingFactor;
        static int newGreenX = 0;
        // Draw black line to cover green
        display.fillRect(coverX, currentSelectedTopLine.y, blackLineLength, 3, PortableOS::getSystemColor(BG_COLOR));
        // Draw new appearing green line
        display.fillRect(
            newGreenX, 
            currentSelectedBottomLine.y+lineYincremet,
            sizingFactor,
            3,
            PortableOS::getSystemColor(SELECTION_COLOR)
            );

        // Animation is not finished yet
        if(coverX >= 0)
        {
            // decrement new black line X
            coverX -= sizingFactor;
            // increment black line length
            blackLineLength += sizingFactor;

            // Increment appearing green line X
            newGreenX += sizingFactor;
        }
        // Finish the animation
        else{
            // Reset values to initials
            coverX = 480 - sizingFactor;
            blackLineLength = sizingFactor;
            newGreenX = 0;

            // Disable selection animation flag
            isNextSelectedAnimation = false;

            // Swipe lines (old bottom is now top line etc.)
            currentSelectedTopLine = currentSelectedBottomLine;
            currentSelectedBottomLine = {currentSelectedBottomLine.y+lineYincremet};
        }
    }else if(isPreviousSelectedAnimation)
    {

        // The same logic for PREVIOUS selection animation
        // Bottom line dissapearing, top line appearing
        const int sizingFactor = 120;
        static int coverX = 480 - sizingFactor;
        static int blackLineLength = sizingFactor;
        static int newGreenX = 0;
        display.fillRect(coverX, currentSelectedBottomLine.y, blackLineLength, 3, PortableOS::getSystemColor(BG_COLOR));
        display.fillRect(
            newGreenX, 
            currentSelectedTopLine.y - lineYincremet,
            sizingFactor,
            3,
            PortableOS::getSystemColor(SELECTION_COLOR)
            );

        if(coverX >= 0)
        {
            coverX -= sizingFactor;
            blackLineLength += sizingFactor;
            newGreenX += sizingFactor;
        }
        else{

            // Finish the animation
            coverX = 480 - sizingFactor;
            blackLineLength = sizingFactor;
            newGreenX = 0;
            isPreviousSelectedAnimation = false;

            currentSelectedBottomLine = currentSelectedTopLine;
            currentSelectedTopLine = {currentSelectedBottomLine.y-lineYincremet};
        }
    }
}


bool Menu::refreshInProgress()
{
    // Return true, when we still have animation pending
    if(isNextSelectedAnimation || isPreviousSelectedAnimation)
    {
        return true;
    }

    return false;
}

void Menu::render(DisplayProvider& display) {
    if(activationRequested)
    {
        display.fillScreen(PortableOS::getSystemColor(BG_COLOR));
        needsRefresh = true;
        activationRequested = false;
    }

    // Render only when we need to refresh our scene
    if (needsRefresh) {
        int baseY = firstTextLineY;
        display.setTextSize(1);
        display.setTextFont(4);
        // Iterate through names array
        for (unsigned i = 0; i < menuElements.size() ; i++) {
            // Display Normal-Style name
            if(i != selectedChoice)
            {
                display.setTextColor(PortableOS::getSystemColor(MOTIVE_COLOR));
            }
            // Display Selected-Style name
            else {
                display.setTextColor(PortableOS::getSystemColor(SELECTION_COLOR));
            }
            display.drawString(menuElements.at(i), 10, baseY);
            baseY += lineYincremet;
        }
        // Update needsRefreshFlag
        needsRefresh = refreshInProgress();

        drawSelectionLines(display);
    }
}

void Menu::update() {
    // There are some requests waiting to be processed
    if(pendingRequests.size() > 0)
    {
        // We only allow new input when we do not have animation pending
        if(!refreshInProgress()){
            MenuInputRequest request = pendingRequests.front();
            pendingRequests.pop();
            // Select NEXT
            if(request == MENU_INPUT_DOWN){
                // Check if change is possible
                if((selectedChoice + 1) != menuElements.size())
                {
                    // Update selectedChoice to next value
                    selectedChoice = (selectedChoice + 1);
                    // Activate animation
                    isNextSelectedAnimation = true;
                    // we need to refresh scene
                    needsRefresh = true;
                }
            }

            // Select PREVIOUS
            if(request == MENU_INPUT_UP)
            {
                // Check if change is possible
                if(selectedChoice != 0)
                {
                    // Update selectedChoice to previous value
                    selectedChoice = (selectedChoice - 1);
                    // Activate animation
                    isPreviousSelectedAnimation = true;
                    // We need to refresh
                    needsRefresh = true;
                }
            }

            // Check if callback is registered
            if(request == MENU_INPUT_SELECT && choiceDoneCallback != nullptr)
            {
                // choice done callback
                choiceDoneCallback(selectedChoice);
            }

            // Check if callback is registered
            if(request == MENU_INPUT_SELECT && choicePoll != nullptr)
            {
                // choice done callback
                *choicePoll = selectedChoice;
            }
        }
    }

}

void Menu::forceRefresh()
{
    needsRefresh = true;
}

void Menu::input(InputType menuInput) {
    switch(menuInput)
    {
        case BUTTON_C:
            pendingRequests.push(MENU_INPUT_DOWN);
            break;
        case BUTTON_A:
            pendingRequests.push(MENU_INPUT_UP);
            break;
        case BUTTON_K:
            pendingRequests.push(MENU_INPUT_SELECT);
            break;
        default: break;
    }

    // // We only allow new input when we do not have animation pending
    // if(!refreshInProgress()){
    //     // Select NEXT
    //     if(menuInput == BUTTON_C){
    //         // Check if change is possible
    //         if((selectedChoice + 1) != menuElements.size())
    //         {
    //             // Update selectedChoice to next value
    //             selectedChoice = (selectedChoice + 1);
    //             // Activate animation
    //             isNextSelectedAnimation = true;
    //             // we need to refresh scene
    //             needsRefresh = true;
    //         }
    //     }

    //     // Select PREVIOUS
    //     if(menuInput == BUTTON_A)
    //     {
    //         // Check if change is possible
    //         if(selectedChoice != 0)
    //         {
    //             // Update selectedChoice to previous value
    //             selectedChoice = (selectedChoice - 1);
    //             // Activate animation
    //             isPreviousSelectedAnimation = true;
    //             // We need to refresh
    //             needsRefresh = true;
    //         }
    //     }

    //     // Check if callback is registered
    //     if(menuInput == BUTTON_K && choiceDoneCallback != nullptr)
    //     {
    //         // choice done callback
    //         choiceDoneCallback(selectedChoice);
    //     }

    //     // Check if callback is registered
    //     if(menuInput == BUTTON_K && choicePoll != nullptr)
    //     {
    //         // choice done callback
    //         *choicePoll = selectedChoice;
    //     }
    // }
}

void Menu::analogInput(int x, int y) {
    // if(y <= -7){
    //     pendingRequests.push(MENU_INPUT_DOWN);
    // }else if (y >= 7) {
    //     pendingRequests.push(MENU_INPUT_UP);
    // }

    // if(x >= 8){
    //     pendingRequests.push(MENU_INPUT_SELECT);
    // }


    if(!refreshInProgress()) {
        if (y <= -7) {
            if((selectedChoice + 1) !=  menuElements.size())
            {
                // Update selectedChoice to next value
                selectedChoice = (selectedChoice + 1);
                // Activate animation
                isNextSelectedAnimation = true;
                // we need to refresh scene
                needsRefresh = true;
            }
        }
        else if (y >= 7) {
            if(selectedChoice != 0)
            {
                // Update selectedChoice to previous value
                selectedChoice = (selectedChoice - 1);
                // Activate animation
                isPreviousSelectedAnimation = true;
                // We need to refresh
                needsRefresh = true;
            }
        }
        if (x == 10 && choiceDoneCallback != nullptr) {
            // choce done callback
            choiceDoneCallback(selectedChoice);
        }

        if (x == 10 && choicePoll != nullptr) {
            // choce done callback
            *choicePoll = selectedChoice;
        }
    } 
}
