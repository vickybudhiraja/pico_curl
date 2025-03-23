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
#include "lwip/dns.h"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

typedef struct {
    struct tcp_pcb *pcb;
    bool connected;
    bool request_sent;
    char buffer[1024];
} http_client_t;

static http_client_t http_client;

static err_t http_recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) {
        printf("\n[http] Server closed connection.\n");
        tcp_close(tpcb);
        return ERR_OK;
    }

    pbuf_copy_partial(p, http_client.buffer, p->len, 0);
    http_client.buffer[p->len] = '\0';
    printf("%s", http_client.buffer);

    tcp_recved(tpcb, p->len);
    pbuf_free(p);
    return ERR_OK;
}

static err_t http_connect_cb(void *arg, struct tcp_pcb *tpcb, err_t err) {
    if (err != ERR_OK) {
        printf("[http] Connect failed: %d\n", err);
        return err;
    }

    printf("[http] Connected to server!\n");

    const char *request = "GET /?format=3 HTTP/1.1\r\nHost: wttr.in\r\nConnection: close\r\n\r\n";
    tcp_write(tpcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
    return ERR_OK;
}

// callbacks for errors
static void http_err_cb(void *arg, err_t err) {
    printf("[http] TCP error occurred: %d\n", err);
}
static err_t http_sent_cb(void *arg, struct tcp_pcb *tpcb, u16_t len) {
    // Called when data is ACKed
    return ERR_OK;
}

void http_get_request() {

    ip_addr_t ip_addr;
    // use the defs TODO:
    err_t err = dns_gethostbyname("wttr.in", &ip_addr, NULL, NULL);

    if (err != ERR_OK) {
        printf("[http] DNS failed: %d\n", err);
        return;
    }

    http_client.pcb = tcp_new_ip_type(IP_GET_TYPE(&ip_addr));
    if (!http_client.pcb) {
        printf("[http] Failed to allocate PCB\n");
        return;
    }

    tcp_arg(http_client.pcb, NULL);
    tcp_recv(http_client.pcb, http_recv_cb);
    tcp_sent(http_client.pcb, http_sent_cb);
    tcp_err(http_client.pcb, http_err_cb);

    err = tcp_connect(http_client.pcb, &ip_addr, 80, http_connect_cb);
    if (err != ERR_OK) {
        printf("[http] Connect error: %d\n", err);
        tcp_close(http_client.pcb);
    }
}

void http_get_request_old() {

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

    // let the wifi init properly
    while (1) {
        sleep_ms(1000);
    }

    http_get_request();
    // wait for the response
    while (1) {
        sleep_ms(1000);
    }

}
