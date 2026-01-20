
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include <stdio.h>

#define ARCHSEL_OFFSET 0x158
#define AIRCR_OFFSET 0x0ed0c

static inline volatile uint32_t* get_archsel_reg(void) {
    return (volatile uint32_t*)((uintptr_t)OTP_BASE + ARCHSEL_OFFSET);
}
static inline volatile uint32_t* get_aircr_reg(void) {
    return (volatile uint32_t*)((uintptr_t)PPB_BASE + AIRCR_OFFSET);
}

void switch_core_to_risc(void) {
    // Set both cores to RISC
    *get_archsel_reg() = 0x3;

    busy_wait_us(10);

    // magic value + set SYSRESETREQ
    *get_aircr_reg() = (0x05FA << 16) | (1 << 2); 

    while(1);
}

int main()
{
    stdio_init_all();
    printf("Hello from arm side\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    

    for (int i = 0; i < 3; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(500);
    }

    switch_core_to_risc();
}
