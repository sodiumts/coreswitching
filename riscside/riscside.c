#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

#define ARCHSEL_OFFSET 0x158

static inline volatile uint32_t* get_archsel_reg(void) {
    return (volatile uint32_t*)((uintptr_t)OTP_BASE + ARCHSEL_OFFSET);
}

void switch_core_to_arm(void) {
    // Set both cores to ARM
    *get_archsel_reg() = 0x0;

    busy_wait_us(10);

    // force watchdog to kill current core
    watchdog_enable(1, 1);
    sleep_ms(2);

    while(1);
}



int main()
{
    stdio_init_all();
    printf("Hello from risc side\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    for (int i = 0; i < 4; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(100);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(100);
    }

    switch_core_to_arm();
    while (true);
}
