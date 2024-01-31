#include <os/drivers/keyboarddriver.hpp>

HwButton KeyboardDriver::buttons[6];


void KeyboardDriver::init()
{
    pinMode(KEY_C_PIN, INPUT);
    pinMode(KEY_A_PIN, INPUT);
    pinMode(KEY_F_PIN, INPUT);
    pinMode(KEY_K_PIN, INPUT);
    pinMode(KEY_B_PIN, INPUT);
    pinMode(KEY_D_PIN, INPUT);

    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    KeyboardDriver::buttons[0].btnType = BUTTON_A;
    KeyboardDriver::buttons[0].btnPin = KEY_A_PIN;
    KeyboardDriver::buttons[0].btnName = 'A';
    
    KeyboardDriver::buttons[1].btnType = BUTTON_B;
    KeyboardDriver::buttons[1].btnPin = KEY_B_PIN;
    KeyboardDriver::buttons[1].btnName = 'B';

    KeyboardDriver::buttons[2].btnType = BUTTON_C;
    KeyboardDriver::buttons[2].btnPin = KEY_C_PIN;
    KeyboardDriver::buttons[2].btnName = 'C';

    KeyboardDriver::buttons[3].btnType = BUTTON_D;
    KeyboardDriver::buttons[3].btnPin = KEY_D_PIN;
    KeyboardDriver::buttons[3].btnName = 'D';

    KeyboardDriver::buttons[4].btnType = BUTTON_F;
    KeyboardDriver::buttons[4].btnPin = KEY_F_PIN;
    KeyboardDriver::buttons[4].btnName = 'F';

    KeyboardDriver::buttons[5].btnType = BUTTON_K;
    KeyboardDriver::buttons[5].btnPin = KEY_K_PIN;
    KeyboardDriver::buttons[5].btnName = 'K';
}

void KeyboardDriver::processAnalog() {
    static int lastX = 0;
    static int lastY = 0;

    int analogX = analogRead(ANALOG_X_PIN);
    int analogY = analogRead(ANALOG_Y_PIN);

    int rangedX = (analogX - 2000)/200;
    int rangedY = (analogY - 2000)/200;

    if(abs(lastX - analogX) > 200){
        //Serial.println("X: " + String(rangedX));
        lastX = analogX;
        
    }
    
    if(abs(lastY - analogY) > 200){
        //Serial.println("Y: " + String(rangedY));
        lastY = analogY;
    }

    bool isXmoved = false;
    bool isYmoved = false;

    if(abs(rangedX) > 3)
    {
        isXmoved = true;
    }

    if(abs(rangedY) > 3)
    {
        isYmoved = true;
    }

    if(isYmoved || isXmoved){
        PortableOS::analogInput(rangedX, rangedY);
        digitalWrite(13, HIGH);
    }else{
        digitalWrite(13, LOW);
    }
}

void KeyboardDriver::task()
{
    // Check if pressed buttons were released
    for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        if(!KeyboardDriver::buttons[i].isPressable)
        {
            // When button is relased
            if(digitalRead(KeyboardDriver::buttons[i].btnPin))
            {
                if(millis() - KeyboardDriver::buttons[i].btnPressedTime > BUTTON_REACTIVATION_TIME_MS)
                {
                    // Make it pressable again
                    KeyboardDriver::buttons[i].isPressable = true;

                    digitalWrite(12, LOW);
                }
            }
        }
    }

    // Check if any button is pressed
    for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        // Must be pressable && LOW on pin
        if( KeyboardDriver::buttons[i].isPressable && 
            !digitalRead(KeyboardDriver::buttons[i].btnPin))
        {
            // Send input to OS
            PortableOS::input(KeyboardDriver::buttons[i].btnType);
            Serial.println("Pressed button : " + String(KeyboardDriver::buttons[i].btnName));
            // Set button as notPressable
            KeyboardDriver::buttons[i].isPressable = false;
            KeyboardDriver::buttons[i].btnPressedTime = millis();

            digitalWrite(12, HIGH);
        }


        // check long press
        if(!digitalRead(KeyboardDriver::buttons[i].btnPin)) // is pressed
        {
            if(!buttons[i].isLongPress){ // No longPress set yet
                buttons[i].longPressCounter++; // increment long press counter

                if(buttons[i].longPressCounter > BUTTON_LONG_PRESS_CYCLE_TIMES) // Number of cycles with pressed reached
                {
                    PortableOS::longPressInput(buttons[i].btnType); // Forward longPress to OS
                    buttons[i].isLongPress = true; // setLongPress flag
                    buttons[i].longPressCounter = 0; // reset the counter
                }
            }
        }else // Button is not pressed
        {
            buttons[i].longPressCounter = 0;
            if(buttons[i].isLongPress)
            {
                buttons[i].isLongPress = false;
                PortableOS::longPressRelease(buttons[i].btnType);
            }
        }
    }

    //processAnalog();
}