#include "os/mainloadingscreen.h"

bool MainLoadingScreen::isLoaded = false;
AnimatedLetter MainLoadingScreen::textArray[8];
int MainLoadingScreen::loadedLettersIndex = 0;
const int MainLoadingScreen::animationIntervalMs = 200;
int MainLoadingScreen::currentRect1X = -RECT_INCREMENT;
int MainLoadingScreen::currentRect2X = -4*RECT_INCREMENT;
int MainLoadingScreen::currentRect3X = -8*RECT_INCREMENT;

void MainLoadingScreen::animateNextLetter()
{
    if(textArray[loadedLettersIndex].y < textArray[loadedLettersIndex].destinationY)
    {
        textArray[loadedLettersIndex].y += 5;
        textArray[loadedLettersIndex].needsPrint = true;

        if(textArray[loadedLettersIndex].y >= textArray[loadedLettersIndex].destinationY)
        {
            loadedLettersIndex++;
            if(loadedLettersIndex == 8)
            {
                isLoaded = true;
            }
        }
    }

}

void MainLoadingScreen::init()
{
    textArray[0] = {'E', TEXT_START_X, -10.f, 30, true, false};
    textArray[1] = {'S', textArray[0].x + LETTERS_SPACING, -10.f, 60, true, false};
    textArray[2] = {'P', textArray[1].x + LETTERS_SPACING, -10.f, 90, true, false};
    textArray[3] = {'L', textArray[2].x + LETTERS_SPACING, -10.f, 120, true, false};
    textArray[4] = {'A', textArray[3].x + LETTERS_SPACING, -10.f, 150, false, false};
    textArray[5] = {'Y', textArray[4].x + LETTERS_SPACING, -10.f, 180, false, false};
    textArray[6] = {'3', textArray[5].x + LETTERS_SPACING-20, -10.f, 110, false, false};
    textArray[7] = {'2', textArray[6].x + LETTERS_SPACING, -10.f, 110, false, false};
}

bool MainLoadingScreen::update()
{
    if(!isLoaded)
    {
        animateNextLetter();

        if(currentRect1X < 480)
        {
            currentRect1X += RECT_INCREMENT;
        }
        if(currentRect2X < 480)
        {
            currentRect2X += RECT_INCREMENT;
        }
        if(currentRect3X < 480)
        {
            currentRect3X += RECT_INCREMENT;
        }
    }

    return isLoaded;

}

void MainLoadingScreen::render(DisplayProvider& display)
{
    if(loadedLettersIndex < 6){
        display.setTextSize(5);
        display.setTextFont(2);
        display.setTextColor(TFT_SKYBLUE, 160040);
    }else
    {
        display.setTextSize(2);
        display.setTextFont(7);
        display.setTextColor(TFT_RED, 160040);
    }



    display.fillRect(textArray[loadedLettersIndex].x - 6, textArray[loadedLettersIndex].y - 8, LETTERS_SPACING+5, 8, 160040);
    display.drawString(String(textArray[loadedLettersIndex].letter), textArray[loadedLettersIndex].x, textArray[loadedLettersIndex].y);

    display.fillRect(currentRect1X, RECT_Y+20, RECT_INCREMENT, 20, TFT_BLUE);
    display.fillRect(currentRect2X, RECT_Y, RECT_INCREMENT, 20, TFT_GREEN);
    display.fillRect(currentRect3X, RECT_Y-20, RECT_INCREMENT, 20, TFT_RED);
}