#ifndef INIT_BME280_H
#define INIT_BME280_H


#define TAG_BME280 "BME280"

#define I2C_MASTER_ACK 0
#define I2C_MASTER_NACK 1

int8_t BME280_I2C_bus_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);
int8_t BME280_I2C_bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);
void BME280_delay_msek(uint32_t msek);
void task_bme280(void *ignore);
void bme280();


#endif