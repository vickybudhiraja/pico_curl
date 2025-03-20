#include <stdio.h>
// #include <curl/curl.h>
#include "pico/stdlib.h"
#include <pico/cyw43_arch.h>

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Failed to initialize Wi-Fi module\n");
        return 1;
    }

    while (1) {
        printf("Hello, Curl!\n");
        sleep_ms(1000);
    }
    return 0;
}

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"
// #include "defs.h"


// int main() {
//     stdio_init_all();
    
//     if (cyw43_arch_init()) {
//         printf("Failed to initialize Wi-Fi module\n");
//         return 1;
//     }

//     printf("Connecting to Wi-Fi: %s...\n", WIFI_SSID);
//     cyw43_arch_enable_sta_mode();

//     if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
//         printf("Failed to connect to Wi-Fi\n");
//         return 1;
//     }

//     printf("Connected to Wi-Fi!\n");

//     while (1) {
//         printf("Wi-Fi is connected\n");
//         sleep_ms(5000);
//     }

//     return 0;
// }
