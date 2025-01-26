#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define SSID EXAMPLE
#define PASSWORD EXAMPLE
#define MAX_RETRY 3
#define WIFI_TAG "WIFI"
#define WIFI_CONNECTED_BIT BIT0 
#define WIFI_FAIL_BIT      BIT1

static EventGroupHandle_t s_wifi_event_group;
static int retry_num = 0;

/*When you'll commit this erase SSID and PASSWORD
  also you should not to commit Emacs buffer files*/

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
        if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
                esp_wifi_connect();
        } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
                if (retry_num < MAX_RETRY) {
                        esp_wifi_connect();
                        retry_num++;
                        ESP_LOGI(WIFI_TAG, "Retrying to connect to the AP");
                } else {
                        xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
                }
                ESP_LOGI(WIFI_TAG, "Connect to Wi-Fi failed");
        } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
                ip_event_got_ip_t *event = (ip_event_got_ip_t*)event_data;
                ESP_LOGD(WIFI_TAG, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
                retry_num = 0;
                xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        }
}

void wifi_init_sta(void)
{
        s_wifi_event_group = xEventGroupCreate();
        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_create_default_wifi_sta();

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        esp_event_handler_instance_t instance_any_id;
        esp_event_handler_instance_t instance_got_ip;
        
        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &event_handler,
                                                            NULL,
                                                            &instance_any_id));
        
        ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                           IP_EVENT_STA_GOT_IP,
                                                           &event_handler,
                                                           NULL,
                                                           &instance_got_ip));

        wifi_config_t wifi_config = {
                .sta = {
                        .ssid = SSID,
                        .password = PASSWORD,   
                }
        };

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_start());

        ESP_LOGI(WIFI_TAG, "wifi_init_sta finished");

        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                               pdFALSE,
                                               pdFALSE,
                                               portMAX_DELAY);

        if (bits & WIFI_CONNECTED_BIT) {
                ESP_LOGI(WIFI_TAG, "connected to ap SSID:%s password:%s",
                         SSID, PASSWORD);
        } else if (bits & WIFI_FAIL_BIT) {
                ESP_LOGI(WIFI_TAG, "Failed to connect to SSID:%s, password:%s",
                 SSID, PASSWORD);
        } else {
                ESP_LOGI(WIFI_TAG, "UNEXPECTED EVENT");
        }
}

void wifi_start(void)
{
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                ESP_ERROR_CHECK(nvs_flash_erase());
                ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        ESP_LOGI(WIFI_TAG, "ESP_WIFI_MODE_STA");
        wifi_init_sta();

}

