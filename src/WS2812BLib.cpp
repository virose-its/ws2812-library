#include "WS2812BLib.h"

LEDTask::LEDTask(uint8_t startLed, uint8_t endLed) {
    this->startLed = startLed;
    this->endLed = endLed;
    this->mode = OFF;

    // Start task.
    xTaskCreate(
        [](void *obj) -> void {
            static_cast<LEDTask *>(obj)->Task(obj);
        },
        String("LEDTask" + String(startLed)).c_str(),
        5000,
        this,
        0,
        NULL);
}

void LEDTask::Task(void *pvParameters) {
    int fadeTime = 0;
    int brightness = 0;
    int brightnessStep = 1;

    for (;;) {
        switch (mode) {
            case FADE:
                if (!fadeTime) fadeTime = onTime;

                brightness += brightnessStep;

                if (brightness >= 100 || brightness <= 0) {
                    fadeTime = brightness >= 100 ? offTime : onTime;
                    brightnessStep = -brightnessStep;
                }

                for (int i = startLed; i < endLed; i++) {
                    leds[i] = color;
                    leds[i].nscale8(brightness);
                }
                FastLED.show();
                vTaskDelay((fadeTime / 100) / portTICK_PERIOD_MS);

                break;
            case FLICKER:
                for (int i = startLed; i < endLed; i++) leds[i] = color;
                FastLED.show();
                vTaskDelay(onTime / portTICK_PERIOD_MS);

                for (int i = startLed; i < endLed; i++) leds[i] = CRGB::Black;
                FastLED.show();
                vTaskDelay(offTime / portTICK_PERIOD_MS);

                break;
            case ON:
                for (int i = startLed; i < endLed; i++) leds[i] = color;
                FastLED.show();
                vTaskDelay(100 / portTICK_PERIOD_MS);

                break;
            case OFF_AFTER:
                for (int i = startLed; i < endLed; i++) leds[i] = color;
                FastLED.show();
                vTaskDelay(onTime / portTICK_PERIOD_MS);
                this->mode = OFF;

                break;
            case OFF:
                for (int i = startLed; i < endLed; i++) leds[i] = CRGB::Black;
                FastLED.show();
                vTaskDelay(100 / portTICK_PERIOD_MS);

                break;
            default:
                FastLED.show();
                vTaskDelay(100 / portTICK_PERIOD_MS);

                break;
        }
    }
}

void LEDTask::setFade(int color, uint16_t fadeInTime, uint16_t fadeOutTime) {
    this->mode = FADE;
    this->color = color;
    this->onTime = fadeInTime;
    this->offTime = fadeOutTime;
}

void LEDTask::setFlicker(int color, uint16_t onTime, uint16_t offTime) {
    this->mode = FLICKER;
    this->color = color;
    this->onTime = onTime;
    this->offTime = offTime;
}

void LEDTask::setOffAfter(int color, uint16_t onTime) {
    this->mode = OFF_AFTER;
    this->color = color;
    this->onTime = onTime;
}

void LEDTask::turnOn(int color) {
    this->mode = ON;
    this->color = color;
}

void LEDTask::turnOff() {
    this->mode = OFF;
}