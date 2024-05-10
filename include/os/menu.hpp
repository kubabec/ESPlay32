#ifndef MENU_H
#define MENU_H
#include "app/stoper.hpp"
#include "os/displayprovider.hpp"
#include "targetDatatypes.hpp"
#include <queue>
#include <vector>

struct HorizontalLineParameters
{
    int y;
};

enum MenuInputRequest
{
    MENU_INPUT_UP,
    MENU_INPUT_DOWN,
    MENU_INPUT_SELECT
};

class Menu {
    std::vector<String> menuElements;
    bool activationRequested = false;
    std::queue<MenuInputRequest> pendingRequests;

    public:
    // Constructor
    Menu(std::vector<String> a_menuElements);
    // Interface to register callback which will allow app launching in the future
    void registerChoiceDoneCallback(void (*a_choiceDoneCallback)(int8_t));
    void registerChoiceDonePollValue(int8_t* choice);
    
    // Render
    void render(DisplayProvider& display);
    // Update
    void update();
    // Menu input
    void input(InputType menuInput);

    void analogInput(int x, int y);

    // Request menu to start rendering
    void requestActivation();

    void forceRefresh();

    private:
    // Callback for launching App
    void (*choiceDoneCallback)(int8_t) = nullptr;
    int8_t* choicePoll = nullptr;

    // Currently selected user choice
    int8_t selectedChoice = 0;

    // Flag whether menu needs to be refreshed (re-rendered)
    bool needsRefresh = true;

    //Animations
    // Flag whether animation for selecting next is active
    bool isNextSelectedAnimation = false;
    // Flag whether animation for selecting previous is active
    bool isPreviousSelectedAnimation = false;

    // Number of pixels between top and bottom choice green lines
    const int lineYincremet = 35;
    // Top line base parameters
    const HorizontalLineParameters startingTopSelectionLine{0};
    // Text start Y
    const int firstTextLineY = startingTopSelectionLine.y+7;
    // Bottom line base parameters
    const HorizontalLineParameters startingBottomSelectionLine{lineYincremet};
    
    // Current choice top line parameters
    HorizontalLineParameters currentSelectedTopLine{
        startingTopSelectionLine.y};

    // Current choice bottom parameters
    HorizontalLineParameters currentSelectedBottomLine{
        startingBottomSelectionLine.y};

    // Draw green selection lines function
    void drawSelectionLines(DisplayProvider& display);
    // Check if menu animation is still running
    bool refreshInProgress();
};

#endif
