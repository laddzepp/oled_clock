#include <time.h>
#include <stdlib.h>
#include "esp_sntp.h"
#include "esp_log.h"
#define TIME_TAG "TIME"
#define NTP_SERVER "pool.ntp.org"

struct tm get_time(void)
{    
        time_t now;
        setenv("TZ", "MSK-3", 1);
        tzset();

        struct tm current_msk_time;
        time(&now);
        localtime_r(&now, &current_msk_time);
        return current_msk_time; 
}

void start_sntp(void)
{
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, NTP_SERVER);
        sntp_init();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
}
