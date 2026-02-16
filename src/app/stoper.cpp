#include "app/stoper.hpp"

Stoper::Stoper()
{
}

void Stoper::start(int w, int h)
{
    width = w;
    height = h;
}

void Stoper::input(InputType input)
{
    switch (input)
    {
    case BUTTON_A:
        isPaused = !isPaused;
        break;
    case BUTTON_B:
        reset();
        break;

    default:
        break;
    }
}

void Stoper::udpDataReceived(int messageID, std::vector<uint8_t> data)
{
}

void Stoper::longPressInput(InputType input)
{
}

void Stoper::longPressRelease(InputType input)
{
}

void Stoper::analogInput(int x, int y)
{
}

void Stoper::touchInput(int x, int y)
{
}

void Stoper::update()
{

    if (!isPaused)
    {
#ifdef EMULATOR
        millisec += 1; //(millis() - lastUpdate);
#else
        millisec += (millis() - lastUpdate);
#endif
        if (millisec >= 1000)
        {
            sec++;
            millisec = 0;
        }
        if (sec >= 60)
        {
            min++;
            sec = 0;
        }
        if (min >= 60)
        {
            hour++;
            min = 0;
        }
        if (hour >= 1000)
        {
            thousandHour++;
            hour = 0;
        }
#ifdef EMULATOR
        currentTime = String(QString::number(hour)) + ":" + String(QString::number(min)) + ":" + String(QString::number(sec)) + "." + String(QString::number(millisec));
#else
        currentTime = String(hour) + ":" + String(min) + ":" + String(sec) + "." + String(millisec);
#endif
    }

#ifdef EMULATOR
    lastUpdate = 1; // millis();
#else
    lastUpdate = millis();
#endif
}

void Stoper::render(DisplayProvider &display)
{
    display.setTextSize(1);

    // Digit font
    display.setTextFont(4);
    display.setTextColor(TFT_GREEN, TFT_LIGHTGREY);
    if (!isDispColor)
    {
        isDispColor = true;
        display.fillScreen(TFT_LIGHTGREY);
        display.drawString("RESET(B)", 10, (height / 3) * 2 + 30);
    }
    if (isPaused)
    {
        display.drawString("RESUME(A)", (width / 3) * 2 + 10, (height / 3) * 2 + 30);
    }
    else
    {
        display.drawString("   PAUSE(A)     ", ((width / 3) * 2) + 10, (height / 3) * 2 + 30);
    }

    display.setTextSize(1);
    display.setTextFont(7);
    display.setTextColor(TFT_YELLOW, TFT_LIGHTGREY);
    display.drawString(currentTime + "       ", 110, height / 4);
}

void Stoper::forceRender(DisplayProvider &display)
{
}

void Stoper::end()
{
}

void Stoper::reset()
{
    millisec = 0;
    sec = 0;
    min = 0;
    hour = 0;
    thousandHour = 0;
#ifdef EMULATOR
    currentTime = String(QString::number(hour)) + ":" + String(QString::number(min)) + ":" + String(QString::number(sec)) + "." + String(QString::number(millisec));
#else
    currentTime = String(hour) + ":" + String(min) + ":" + String(sec) + "." + String(millisec);
#endif
}

String Stoper::getAppNameString()
{
    return "Stoper";
}

uint16_t Stoper::getBackgroundColor()
{
    return TFT_LIGHTGREY;
}
