#include "main.h"

#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "esp_log.h"
#define LOG_TAG "MAIN"



static main app;

extern "C" {
    void app_main();
}


void app_main(void)
{
    ESP_LOGI(LOG_TAG, "Creating default even loop");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(LOG_TAG, "Initialized NVS");
    ESP_ERROR_CHECK(nvs_flash_init());

    app.setup();

    while(true) {
        app.loop();
    }
}

esp_err_t main::setup() {

    esp_err_t status{ESP_OK};

    ESP_LOGI(LOG_TAG, "Setup!");
    status |= led.init();


    return status;
}

void main::loop() {

    ESP_LOGI(LOG_TAG, "LED_ON");
    led.set(true);
    vTaskDelay(pdSECOND);
    ESP_LOGI(LOG_TAG, "LED_OFF");
    led.set(false);
    vTaskDelay(pdSECOND);
}

