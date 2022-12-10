// Kaiser Wilhelmina
// Controller
// --- Press ANY for LED_ON - Fade in
// --- Press 5 + 6 at once for CANDLE_MODE
// --- Hold ANY for LED_OFF - Fade out

#include "Arduino.h"
#include "AceButton.h"

using namespace ace_button;

const int LED_ON = HIGH;
const int LED_OFF = LOW;

const uint8_t NUM_LEDS = 5;

struct Info
{
    const uint8_t buttonPin;
    const uint8_t ledPin;
    bool ledState;
};

Info INFOS[NUM_LEDS] = {
    {6, 20, LED_OFF},
    {5, 19, LED_OFF},
    {4, 18, LED_OFF},
    {3, 17, LED_OFF},
    {2, 16, LED_OFF},
};

AceButton buttons[NUM_LEDS];

void handleEvent(AceButton *, uint8_t, uint8_t);

void setup()
{
    delay(100);
    Serial.begin(9600);

    while (!Serial)
        ;
    Serial.println(F("setup(): begin"));

    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
        pinMode(INFOS[i].ledPin, OUTPUT);
        pinMode(INFOS[i].buttonPin, INPUT_PULLUP);
        buttons[i].init(INFOS[i].buttonPin, HIGH, i);
    }

    ButtonConfig *buttonConfig = ButtonConfig::getSystemButtonConfig();
    buttonConfig->setEventHandler(handleEvent);
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
    buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);

    Serial.println(F("setup(): ready"));
}
void loop()
{

    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
        buttons[i].check();
    }
}
void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState)
{

    Serial.print(F("handleEvent(): eventType: "));
    Serial.print(eventType);
    Serial.print(F("; buttonState: "));
    Serial.println(buttonState);

    uint8_t id = button->getId();
    uint8_t ledPin = INFOS[id].ledPin;

    switch (eventType)
    {
    case AceButton::kEventPressed: 
        SetAllLEDs(LED_ON); 
        break;
   case AceButton::kEventLongPressed:
        SetAllLEDs(LED_OFF); 
        break;
    }
}

void SetAllLEDs(int newState)
{
  for (int id=0; id < NUM_LEDS; id++)
  {
    digitalWrite(INFOS[id].ledPin, newState);
    INFOS[id].ledState = newState;
  }
}
