// build by specifying the target board we are using: cmake -DPICO_BOARD=pico_w ..

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "defs.h"
// #include "lwip/sockets.h"
// #include "lwip/dns.h"
// #include "lwip/ip4_addr.h"
// #include "lwip/inet.h"
// #include "lwip/netdb.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

void http_get_request() {

    // new tcp connection obj
    struct tcp_pcb *tcp_connection = tcp_new();
    if (tcp_connection == NULL) {
        printf("Failed to create TCP connection\n");
        return;
    }

    // 
    ip_addr_t ip_address;
    gethostbyname(API_HOST, &ip_address);
    // netif_get_hostname(API_HOST);
    // if (netconn_gethostbyname(API_HOST, &ip_address) != ERR_OK) {
    //     printf("Failed to resolve hostname\n");
    //     tcp_close(tcp_connection);
    //     return;
    // }

    if (tcp_connect(tcp_connection, &ip_address, API_PORT, NULL) != ERR_OK) {
        printf("Failed to connect to server\n");
        tcp_close(tcp_connection);
        return;
    }

    char request[256];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", API_ENDPOINT, API_HOST);
    tcp_write(tcp_connection, request, strlen(request), TCP_WRITE_FLAG_COPY);

    struct pbuf *received_data;
    while ((received_data = tcp_input(tcp_connection, NULL)) != NULL) {
        char *data_ptr = (char *)received_data->payload;
        printf("Received data: %s\n", data_ptr);
        pbuf_free(received_data);
    }
    tcp_close(tcp_connection);
}

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

    
    
    struct tcp_pcb *tcp_connection = tcp_new();
    ip_addr_t ip_address;

}
