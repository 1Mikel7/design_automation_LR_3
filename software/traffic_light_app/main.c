#include <unistd.h>
#include "system.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"


// Биты светофора основной дороги.
#define MAIN_RED     (1u << 0)
#define MAIN_YELLOW  (1u << 1)
#define MAIN_GREEN   (1u << 2)

// Биты светофора второстепенной дороги.
#define SIDE_RED     (1u << 3)
#define SIDE_YELLOW  (1u << 4)
#define SIDE_GREEN   (1u << 5)
#define SIDE_GREEN   (1u << 5)


// Продолжительность сигналов в секундах.

#define MAIN_GREEN_SECONDS   10
#define SIDE_GREEN_SECONDS    5
#define RED_YELLOW_SECONDS    2
#define YELLOW_SECONDS        2
#define ALL_RED_SECONDS       1


// Устанавливает сигналы обоих светофоров.
static void set_traffic_lights(unsigned int signals)
{
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_BASE, signals);
}


// Задержка на заданное количество секунд.
static void delay_seconds(unsigned int seconds)
{
    unsigned int i;

    for (i = 0; i < seconds; i++)
    {
        usleep(1000000);
    }
}



// Сначала включаем оба красных сигнала.
int main(void)
{
    // Начальное безопасное состояние
    set_traffic_lights(MAIN_RED | SIDE_RED);
    delay_seconds(ALL_RED_SECONDS);

    while (1)
    {
        // Подготовка основной дороги к движению.
        set_traffic_lights(MAIN_RED | MAIN_YELLOW | SIDE_RED);
        delay_seconds(RED_YELLOW_SECONDS);

        // Основной дороге разрешено движение.
        set_traffic_lights(MAIN_GREEN | SIDE_RED);
        delay_seconds(MAIN_GREEN_SECONDS);

        // Основная дорога завершает движение.
        set_traffic_lights(MAIN_YELLOW | SIDE_RED);
        delay_seconds(YELLOW_SECONDS);

        // Защитный интервал: оба сигнала красные.
        set_traffic_lights(MAIN_RED | SIDE_RED);
        delay_seconds(ALL_RED_SECONDS);

        // Подготовка второстепенной дороги.
        set_traffic_lights(MAIN_RED | SIDE_RED | SIDE_YELLOW);
        delay_seconds(RED_YELLOW_SECONDS);

        // Второстепенной дороге разрешено движение.
        set_traffic_lights(MAIN_RED | SIDE_GREEN);
        delay_seconds(SIDE_GREEN_SECONDS);

        //  Второстепенная дорога завершает движение.
        set_traffic_lights(MAIN_RED | SIDE_YELLOW);
        delay_seconds(YELLOW_SECONDS);

        // Защитный интервал: оба сигнала красные.
        set_traffic_lights(MAIN_RED | SIDE_RED);
        delay_seconds(ALL_RED_SECONDS);
    }

    return 0;
}
