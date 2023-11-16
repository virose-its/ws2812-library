#ifndef LED_H
#define LED_H

#include <FastLED.h>

extern CRGB leds[];

enum LED {
    FADE,
    FLICKER,
    ON,
    OFF_AFTER,
    OFF
};

class LEDTask {
   public:
    /**
     * Konstruktor untuk kelas LEDTask.
     *
     * @param startLed start nomor LED yang akan digunakan.
     * @param endLed end nomor LED yang akan digunakan.
     */
    LEDTask(uint8_t, uint8_t);

    /**
     * @brief Fungsi untuk mengaktifkan komponen dengan mode fading.
     *
     * @param color warna yang akan digunakan.
     * @param fadeInTime Durasi (dalam milidetik) untuk menyala semakin terang.
     * @param fadeOutTime Durasi (dalam milidetik) untuk padam semakin redup.
     */
    void setFade(int, uint16_t, uint16_t);

    /**
     * Fungsi untuk mengaktifkan komponen dengan mode flicker.
     *
     * @param color warna yang akan digunakan.
     * @param onTime Durasi (dalam milidetik) untuk menyala.
     * @param offTime Durasi (dalam milidetik) untuk padam.
     */
    void setFlicker(int, uint16_t, uint16_t);

    /**
     * @brief Fungsi untuk menyalakan komponen.
     *
     * @param color warna yang akan digunakan.
     */
    void turnOn(int);

    /**
     * @brief Fungsi untuk menyalakan dan mematikan komponen.
     *
     * @param color warna yang akan digunakan.
     * @param onTime Durasi (dalam milidetik) untuk menyala.
     */
    void setOffAfter(int, uint16_t);

    /**
     * @brief Fungsi untuk mematikan komponen.
     */
    void turnOff();

   private:
    uint8_t startLed;
    uint8_t endLed;
    uint8_t mode;
    int color;
    uint16_t onTime;
    uint16_t offTime;

    void Task(void *pvParameters);
};

#endif