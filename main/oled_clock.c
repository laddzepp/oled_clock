#include "wifi_connect.h"
#include "timesync.h"
#include "esp_log.h"
#include "display_control.h"


void app_main(void)
{
        wifi_start();
        start_sntp();
	init_oled_display();
        
        while (1) { 
                update_time();
        }
}
