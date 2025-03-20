// build by specifying the target board we are using: cmake -DPICO_BOARD=pico_w ..

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "defs.h"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Failed to initialize Wi-Fi module\n");
        return 1;
    }

    printf("initialised\n");

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("failed to connect\n");
        return 1;
    }
    printf("connected\n");
}
