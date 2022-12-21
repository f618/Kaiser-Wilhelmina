// Kaiser Wilhelmina
// Controller
// --- Press ANY for LED_ON - Fade in
// --- Press 5 + 6 at once for CANDLE_MODE
// --- Hold ANY for LED_OFF - Fade out

#include "Arduino.h"
#include "OneButton.h"

OneButton touch1(6, false);
OneButton touch2(5, false);
OneButton touch3(4, false);
OneButton touch4(3, false);
OneButton touch5(2, false);

const int LEDone = 20;
const int LEDtwo = 19;
const int LEDthree = 18;
const int LEDfour = 17;
const int LEDfive = 16;

const int pwmIntervals = 50;

void touch();

typedef enum
{
    LED_OFF,
    LED_ON,
} MyActions;

MyActions nextAction = LED_OFF;

int previous = 0;

float R;

void setup()
{
    Serial.begin(9600);
    Serial.println("Kaiser's waking..");

    touch1.attachClick(touch);
    touch2.attachClick(touch);
    touch3.attachClick(touch);
    touch4.attachClick(touch);
    touch5.attachClick(touch);

    R = (pwmIntervals * log10(2)) / (log10(255));

    delay(50);
}

void loop()
{
    touch1.tick();
    touch2.tick();
    touch3.tick();
    touch4.tick();
    touch5.tick();

    int brightness = 0;

    if ((nextAction == LED_OFF) && (previous == 1))
    {
        Serial.println("Kaiser's eyes are heavy..");
        for (int interval = 0; interval <= pwmIntervals; interval++)
        {
            brightness = pow(2, (-(interval - pwmIntervals) / R)) - 1;
            analogWrite(LEDone, brightness);
            analogWrite(LEDtwo, brightness);
            analogWrite(LEDthree, brightness);
            analogWrite(LEDfour, brightness);
            analogWrite(LEDfive, brightness);
            delay(10);
        }
        previous = 0;
    }
    else if ((nextAction == LED_ON) && (previous == 0))
    {
        Serial.println("Kaiser's eyes shine bright..");
        for (int interval = 0; interval <= pwmIntervals; interval++)
        {
            brightness = pow(2, (interval / R)) - 1;
            analogWrite(LEDone, brightness);
            analogWrite(LEDtwo, brightness);
            analogWrite(LEDthree, brightness);
            analogWrite(LEDfour, brightness);
            analogWrite(LEDfive, brightness);
            delay(10);
        }
        previous = 1;
    }
}
void touch()
{
    if (nextAction == LED_OFF)
        nextAction = LED_ON;
    else
        nextAction = LED_OFF;
}