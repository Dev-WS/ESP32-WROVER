#include "main.h"

//#include "BME280/bme280.h"

extern char strTemperature[250];


void app_main(void)
{
	i2c_master_init();
	ssd1306_init();
 
	//xTaskCreate(&task_ssd1306_display_pattern, "ssd1306_display_pattern",  2048, NULL, 6, NULL);

	//BME280_delay_msek(200);

	xTaskCreate(&task_bme280_normal_mode, "bme280_normal_mode",  2048, NULL, 6, NULL);
	xTaskCreate(&task_ssd1306_display_clear, "ssd1306_display_clear",  2048, NULL, 6, NULL);
	vTaskDelay(100/portTICK_PERIOD_MS);
	// xTaskCreate(&task_ssd1306_display_text, "ssd1306_display_text",  2048,
	// 	(void *)"R", 6, NULL);
    xTaskCreate(&task_ssd1306_display_text, "ssd1306_display_text",  2048,
	  	(void *)strTemperature, 6, NULL);
	//xTaskCreate(&task_ssd1306_contrast, "ssid1306_contrast", 2048, NULL, 6, NULL);
	//xTaskCreate(&task_ssd1306_scroll, "ssid1306_scroll", 2048, NULL, 6, NULL);
	
}
