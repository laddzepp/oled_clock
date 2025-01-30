#include "ssd1306.h"
#include "font8x8_basic.h"
#include "timesync.h"
#include "esp_log.h"
#include <time.h>
#include <string.h>
#define DISPLAY_TAG "DISPLAY"


SSD1306_t dev;

void init_oled_display(void)
{ 
        
        int center, bottom, top;

        #if CONFIG_I2C_INTERFACE
	   ESP_LOGI(DISPLAY_TAG, "INTERFACE is i2c");
           ESP_LOGI(DISPLAY_TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
           ESP_LOGI(DISPLAY_TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
           ESP_LOGI(DISPLAY_TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
           i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
         #endif // CONFIG_I2C_INTERFACE


        #if CONFIG_SSD1306_128x64
           top = 2;
           center = 3;
           bottom = 8;
           ESP_LOGI(DISPLAY_TAG, "Panel is 128x64");
           ssd1306_init(&dev, 128, 64);
        #endif // CONFIG_SSD1306_128x64

        ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);        
}

void get_current_time(struct tm *curtime)
{
        char time[6];
        strftime(time, sizeof(time), "%H:%M", curtime);
        ssd1306_display_text_box1(&dev, 2, 20, time, 6, sizeof(time), false, 0);
}

void get_current_month(struct tm *curtime)
{
        char month[18];
        strftime(month, sizeof(month), "%d %B", curtime);
        ssd1306_display_text_box1(&dev, 5, 20, month, strlen(month), strlen(month), false, 0);
}

void get_current_weekday(struct tm *curtime)
{
        char weekday[4];
        strftime(weekday, sizeof(weekday), "%a", curtime);
        ssd1306_display_text_box1(&dev, 7, 20, weekday, strlen(weekday), strlen(weekday), false, 0);
}

void get_current_year(struct tm *curtime)
{
        char year[5];
        strftime(year, sizeof(year), "%Y", curtime);
        ssd1306_display_text_box1(&dev, 7, 60, year, strlen(year),strlen(year), false, 0);
}


void update_time(void)
{
        struct tm curtime = get_time();
        get_current_time(&curtime);
        get_current_month(&curtime);
        get_current_weekday(&curtime);
        get_current_year(&curtime);
}
