/*
 * I2C_LCD.c
 *
 * Created: 6/10/2019 12:44:49 PM
 *  Author: prouser
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "I2C_LCD.h"


void I2C_LCD_write_data(uint8_t data)
{
	char data_u, data_l;
	uint8_t data_t[4] = {0,};
	data_u = (data&0xf0);      // ?? 4bit ???
	data_l = ((data<<4)&0xf0); // ?? 4bit ???
	data_t[0] = data_u|0x0D;   //en=1, rs=1           |D7|D6|D5|D4|X|E|RW|RS|
	data_t[1] = data_u|0x09;   //en=0, rs=1
	data_t[2] = data_l|0x0D;   //en=1, rs=1
	data_t[3] = data_l|0x09;   //en=0, rs=1

	for(char i=0;i<4;i++){
		I2C_write_byte(SLA_W, data_t[i]);
	}
}

void I2C_LCD_write_command(uint8_t command)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (command&0xf0);      // command? ?? 4bit ??
	data_l = ((command<<4)&0xf0); // command? ?? 4bit ??
	data_t[0] = data_u|0x0C;  //en=1, rs=0           |D7|D6|D5|D4|X|E|RW|RS|
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	
	for(char i=0;i<4;i++){
		I2C_write_byte(SLA_W, data_t[i]);
	}
}

void I2C_LCD_clear(void)
{
	I2C_LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void I2C_LCD_init(void)
{
	I2C_init(10000);
	_delay_ms(50);
	//Initialization of HD44780-based LCD (4-bit HW)
	I2C_LCD_write_command(0x33);
	I2C_LCD_write_command(0x32);
	I2C_LCD_write_command(0x28);   //Function Set 4-bit mode
	I2C_LCD_write_command(0x0c);   //Display On/Off Control
	I2C_LCD_write_command(0x06);   //Entry mode set
	I2C_LCD_write_command(0x01);   //Clear Display
	//Minimum delay to wait before driving LCD module
	_delay_ms(10);
}

void I2C_LCD_write_string(char *string)
{
	uint8_t i;
	for(i=0; string[i]; i++)
	I2C_LCD_write_data(string[i]);
}

void I2C_LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	I2C_LCD_write_command(command);
}

void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string)
{
	I2C_LCD_goto_XY(row, col);
	I2C_LCD_write_string(string);
}