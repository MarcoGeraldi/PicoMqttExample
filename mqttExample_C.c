#include "mqttExample.h"

int main()

{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Enable wifi station
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PSWD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
        // Read the ip address in a human readable way
        uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);

        mqtt_init();
        
        mqtt_subscribe(mqtt->mqtt_client_inst, DEVICE_OUT1_COMMAND_TOPIC, 2, mqtt_sub_request_cb, mqtt);
        
        IoT_device_config_pub_init(mqtt->mqtt_client_inst, mqtt);
        
    }

    while (true) {
        
        /* ------------------------------ Update values ----------------------------- */


        /* ----------------------- Update Status of the Device ---------------------- */
        IoT_device_state_update_pub(mqtt->mqtt_client_inst, mqtt); 

        

        /* --------------------------- Toggle on-board LED -------------------------- */
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN));
        sleep_ms(1000);
        
    }
}

void mqtt_init(){
    
    printf("mqtt client init\n");

    mqtt=(MQTT_CLIENT_DATA_T*)calloc(1, sizeof(MQTT_CLIENT_DATA_T));
    
    printf("mqtt struct initialized\n");
    if (!mqtt) {
        printf("mqtt client instant ini error\n");
    }

    mqtt->mqtt_client_info = mqtt_client_info; 

    // Check Server IP Address
    if (!ip4addr_aton(MQTT_SERVER, &address)) {
        printf("ip error\n");
    }

    mqtt->mqtt_client_inst = mqtt_client_new();
    mqtt_set_inpub_callback(mqtt->mqtt_client_inst, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, mqtt);

    err_t err = mqtt_client_connect(mqtt->mqtt_client_inst, &address, MQTT_PORT, &mqtt_connection_cb, mqtt, &mqtt->mqtt_client_info);
    
    if (err != ERR_OK) {
        printf("connect error\n");
    }

} 

