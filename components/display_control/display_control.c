#include "ssd1306.h"
#include "font8x8_basic.h"
#include "esp_log.h"
#define DISPLAY_TAG "DISPLAY"


void init_oled_display(void)
{ 
        SSD1306_t dev;

        #if CONFIG_I2C_INTERFACE
	   ESP_LOGI(DISPLAY_TAG, "INTERFACE is i2c");
           ESP_LOGI(DISPLAY_TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
           ESP_LOGI(DISPLAY_TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
           ESP_LOGI(DISPLAY_TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
           i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
         #endif // CONFIG_I2C_INTERFACE


        #if CONFIG_SSD1306_128x64
           ESP_LOGI(DISPLAY_TAG, "Panel is 128x64");
           ssd1306_init(&dev, 128, 64);
        #endif // CONFIG_SSD1306_128x64

        ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
        ssd1306_display_text(&dev, 1, "Hello", 5, false);

}
