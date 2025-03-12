#include <stdio.h>
#include "pico/stdlib.h"
#include <curl/curl.h>

int main() {
    stdio_init_all();
    while (1) {
        printf("Hello, Curl!\n");
        sleep_ms(1000);
    }
    return 0;
}
