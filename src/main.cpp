// Kaiser Wilhelmina
// Controller

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

const int minBrightness = 80;
const int maxBrightness = 240;

int brightness = 0;

void touch();
void longSTART();

typedef enum
{
    LED_OFF,
    LED_ON,
} MyActions;

MyActions nextAction = LED_OFF;

int brightened = 0;
int previous = 0;
int longTOUCH = 0;
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

    touch1.attachLongPressStart(longSTART);
    touch2.attachLongPressStart(longSTART);
    touch3.attachLongPressStart(longSTART);
    touch4.attachLongPressStart(longSTART);
    touch5.attachLongPressStart(longSTART);

    R = (pwmIntervals * log10(2)) / (log10(minBrightness));

    delay(50);
}

void loop()
{
    touch1.tick();
    touch2.tick();
    touch3.tick();
    touch4.tick();
    touch5.tick();

    if ((nextAction == LED_OFF) && (previous == 1))
    {
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
        Serial.println("Kaiser's eyes shrink:  " + String(brightness) + "..");
        Serial.println("Kaiser's eyes are heavy..");
        previous = 0;
    }
    else if ((nextAction == LED_ON) && (previous == 0))
    {
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
        Serial.println("Kaiser's eyes open: " + String(brightness) + "..");
        Serial.println("Kaiser's eyes shine bright..");
        previous = 1;
    }
    while ((longTOUCH == 1) && (previous == 1))
    {
        if (brightness <= maxBrightness)
        {
            for (brightness; brightness <= maxBrightness; brightness++)
            {
                analogWrite(LEDone, brightness);
                analogWrite(LEDtwo, brightness);
                analogWrite(LEDthree, brightness);
                analogWrite(LEDfour, brightness);
                analogWrite(LEDfive, brightness);
                delay(10);
            }
            Serial.println("Kaiser's eyes open: " + String(brightness) + "..");
            Serial.println("Kaiser's eyes shine even brighter..");
            longTOUCH = 0;
        }
        else
        {
            for (brightness; brightness >= minBrightness; brightness--)
            {
                analogWrite(LEDone, brightness);
                analogWrite(LEDtwo, brightness);
                analogWrite(LEDthree, brightness);
                analogWrite(LEDfour, brightness);
                analogWrite(LEDfive, brightness);
                delay(10);
            }
            Serial.println("Kaiser's eyes shrink: " + String(brightness) + "..");
            Serial.println("Kaiser's return to normal..");
            longTOUCH = 0;
        }
    }
}
void touch()
{
    if (nextAction == LED_OFF)
        nextAction = LED_ON;
    else
        nextAction = LED_OFF;
}

void longSTART()
{
    longTOUCH = 1;
}
