#include <time.h>
#include <stdlib.h>
#include "esp_sntp.h"
#include "esp_log.h"
#define TIME_TAG "TIME"
#define SNTP_SERVER "pool.ntp.org"

void get_time(void)
{
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        time_t now;
        setenv("TZ", "MSK-3", 1);
        tzset();

        struct tm current_msk_time;
        time(&now);
        localtime_r(&now, &current_msk_time);

        char time[20];
        if (current_msk_time.tm_min < 0) {
                sprintf(time, "%d:0%d", current_msk_time.tm_hour, current_msk_time.tm_min);
                ESP_LOGI(TIME_TAG, "%s", time);
        }

        sprintf(time, "%d:%d", current_msk_time.tm_hour, current_msk_time.tm_min);
        ESP_LOGI(TIME_TAG, "%s", time);
}

void start_sntp(void)
{
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, SNTP_SERVER);
        sntp_init();
}
