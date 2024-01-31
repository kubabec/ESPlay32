#ifndef MAIN_LOADING_SCREEN_H
#define MAIN_LOADING_SCREEN_H
#include "displayprovider.hpp"

#define TEXT_START_X 15.f
#define LETTERS_SPACING 55.f
#define TEXT_Y 250.f

#define RECT_INCREMENT 3
#define RECT_Y 280

struct AnimatedLetter
{
    char letter;
    float x = 0;
    float y = 0;
    float destinationY = 0;
    bool animationFinished = false;
    bool needsPrint = false;
    AnimatedLetter() { }
    AnimatedLetter(char a, float b, float c, float destY, bool d, bool e)
    {
        letter = a;
        x = b;
        y = c;
        destinationY = destY;
        animationFinished = d;
        needsPrint = e;
    }
};

class MainLoadingScreen {

    static bool isLoaded;
    static AnimatedLetter textArray[8];
    static int loadedLettersIndex;
    static const int animationIntervalMs;
    static int currentRect1X;
    static int currentRect2X;
    static int currentRect3X;

    static void animateNextLetter();

    public:
    static void init();
    static bool update();
    static void render(DisplayProvider& display);

};


#endif 