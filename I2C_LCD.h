/*
 * I2C_LCD.h
 *
 * Created: 6/10/2019 12:44:31 PM
 *  Author: prouser
 */ 


#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#define COMMAND_CLEAR_DISPLAY	0X01

#define COMMAND_DISPLAY_ON_OFF_BIT	2
#define COMMAND_CURSOR_ON_OFF_BIT	1
#define COMMAND_BLINK_ON_OFF_BIT	0

#define START 0x08
#define SLA_W (0x27<<1)				 // I2C LCD ?? 0x27 , <<1 ??? write?? ??
#define SLA_R (0x27<<1 | 0x01)       // I2C LCD ?? 0x27 , Read?? ??

void I2C_LCD_init(void);
void I2C_LCD_write_data(uint8_t data);
void I2C_LCD_write_command(uint8_t command);
void I2C_LCD_clear(void);
void I2C_LCD_write_string(char *string);
void I2C_LCD_goto_XY(uint8_t row, uint8_t col);
void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string);

#endif /* I2C_LCD_H_ */