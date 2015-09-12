#ifndef LCD_H_
#define LCD_H_

#include <math.h>

#include "stm32f1xx_hal_conf.h"

extern void delay(uint32_t delayMS);

#define LCD_RS_BIT	GPIO_PIN_6
#define LCD_EN_BIT	GPIO_PIN_7
#define LCD_RW_BIT	GPIO_PIN_12

#define LCD_D4_BIT	GPIO_PIN_8
#define LCD_D5_BIT	GPIO_PIN_9
#define LCD_D6_BIT	GPIO_PIN_10
#define LCD_D7_BIT	GPIO_PIN_11

void lcd_write_cmd(uint8_t data);
void lcd_write_data(uint8_t data);
void lcd_write_string(const char *s);
void lcd_write_number(uint32_t num);
void lcd_clear(void);
void lcd_set_line(uint8_t line);
void lcd_init(void);

#endif /* LCD_H_ */
