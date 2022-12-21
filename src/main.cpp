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

const int ledPins[] = {20, 19, 18, 17, 16};

int candleMode = false;

void click1();
void click2();
void click3();
void click4();
void click5();

void longPress1();
void longPress2();
void longPress3();
void longPress4();
void longPress5();

void ledsOn();
void ledsOff();
void candle();

void setup()
{
    Serial.begin(9600);
    Serial.println("Kaiser waking");

    touch3.attachDoubleClick(candle);

    touch1.attachClick(click1);
    touch2.attachClick(click2);
    touch3.attachClick(click3);
    touch4.attachClick(click4);
    touch5.attachClick(click5);

    for (int i = 0; i < 5; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop()
{
    touch1.tick();
    touch2.tick();
    touch3.tick();
    touch4.tick();
    touch5.tick();
}

void ledsOn()
{
    Serial.println("Lights On");
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(ledPins[i], HIGH);
    }
    delay(10);
}

void candle()
{
    Serial.println("Candle");
    for (int i = 0; i < 5; i++)
    {
        analogWrite(ledPins[i], random(120) + 135);
    }
    if (candleMode != false)
    {
        candle();
    }
}
void click1()
{
    Serial.println("Touch 1 CLICK");
    ledsOn();
}

void click2()
{
    Serial.println("Touch 2 CLICK");
    ledsOn();
}

void click3()
{
    Serial.println("Touch 3 CLICK");
    ledsOn();
}

void click4()
{
    Serial.println("Touch 4 CLICK");
    ledsOn();
}

void click5()
{
    Serial.println("Touch 5 CLICK");
    ledsOn();
}