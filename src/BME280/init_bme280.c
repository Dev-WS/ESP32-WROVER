#include "main.h"

double temperatureBME280 = 0.;
double humidityBME280 = 0.;
double pressureBME280 = 0.;

char strTemperature[250];

#define	BME280_INIT_VALUE	(0)

#define	SUCCESS	((uint8_t)0)

void bme280(){

	dev.dev_id = BME280_I2C_ADDR_PRIM;
    dev.intf = BME280_I2C_INTF;
    dev.read = BME280_I2C_bus_read;
    dev.write = BME280_I2C_bus_write;
    dev.delay_ms = BME280_delay_msek;


	rslt = bme280_init(&dev);

    dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;
    rslt = bme280_set_sensor_settings(BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL, &dev);
}

int8_t BME280_I2C_bus_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
	int32_t iError = BME280_INIT_VALUE;

	esp_err_t espRc;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);

	i2c_master_write_byte(cmd, reg_addr, true);
	i2c_master_write(cmd, reg_data, cnt, true);
	i2c_master_stop(cmd);

	espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	if (espRc == ESP_OK) {
		iError = OK;
	} else {
		iError = FAIL;
	}
	i2c_cmd_link_delete(cmd);

	return (int8_t)iError;
}

int8_t BME280_I2C_bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
	int32_t iError = BME280_INIT_VALUE;
	esp_err_t espRc;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, reg_addr, true);

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);

	if (cnt > 1) {
		i2c_master_read(cmd, reg_data, cnt-1, I2C_MASTER_ACK);
	}
	i2c_master_read_byte(cmd, reg_data+cnt-1, I2C_MASTER_NACK);
	i2c_master_stop(cmd);

	espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	if (espRc == ESP_OK) {
		iError = OK;
	} else {
		iError = FAIL;
	}

	i2c_cmd_link_delete(cmd);

	return (int8_t)iError;
}

void BME280_delay_msek(uint32_t msek)
{
	vTaskDelay(msek/portTICK_PERIOD_MS);
}

void task_bme280(void *ignore)
{

		rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
	    dev.delay_ms(40);
	    /* ������ ��� */
	    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
	    if(rslt == BME280_OK)
	    {
	      temperature = comp_data.temperature;      /* ��C  */
	      humidity = comp_data.humidity;          /* %   */
	      pressure = comp_data.pressure * 0.0001;          /* hPa */

          sprintf(strTemperature, "Temp: %d\nPressure: %d\nHumidity: %d", temperature, pressure, humidity);
	    }

	vTaskDelete(NULL);
}
