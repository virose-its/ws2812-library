#include <WS2812BLib.h>

// Ganti dengan jumlah LED yang digunakan.
#define NUM_LEDS 2
// Ganti dengan pin data LED.
#define DATA_PIN 32

CGRB leds[NUM_LEDS];
// Definisikan LEDTask dengan parameter startLed dan endLed.
LEDTask ledTask1(0, 1);
LEDTask ledTask1(1, 2);

void setup() {
    Serial.begin(115200);

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
    // Set LEDTask dengan mode fading.
    ledTask1.setFade(CRGB::Red, 1000, 1000);
    ledTask2.setFade(CRGB::Blue, 1000, 1000);
    // Tunggu sampai LEDTask selesai.
    delay(2000);

    // Set LEDTask dengan mode flicker.
    ledTask1.setFlicker(CRGB::Red, 1000, 1000);
    ledTask2.setFlicker(CRGB::Blue, 1000, 1000);
    // Tunggu sampai LEDTask selesai.
    delay(2000);

    // Set LEDTask dengan mode on.
    ledTask1.turnOn(CRGB::Red);
    ledTask2.turnOn(CRGB::Blue);
    // Tunggu sampai LEDTask selesai.
    delay(2000);

    // Set LEDTask dengan mode off after.
    ledTask1.setOffAfter(CRGB::Red, 1000);
    ledTask2.setOffAfter(CRGB::Blue, 1000);
    // Tunggu sampai LEDTask selesai.
    delay(2000);

    // Set LEDTask dengan mode off.
    ledTask1.turnOff();
    ledTask2.turnOff();
    // Tunggu sampai LEDTask selesai.
    delay(2000);
}
