#include "lcd.h"

uint8_t lcd_check_bf(void)
{
	GPIO_InitTypeDef gpioInit;
	uint8_t ret;

	gpioInit.Pin = GPIO_PIN_11;
	gpioInit.Mode = GPIO_MODE_INPUT;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &gpioInit);

	HAL_GPIO_WritePin(GPIOA, LCD_RW_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	ret = HAL_GPIO_ReadPin(GPIOA, LCD_D7_BIT);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_RW_BIT, GPIO_PIN_RESET);

	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA, &gpioInit);

	return ret;
}

void lcd_write_cmd(uint8_t data)
{
	HAL_GPIO_WritePin(GPIOC, LCD_RS_BIT, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_D4_BIT, data & 0x10);
	HAL_GPIO_WritePin(GPIOA, LCD_D5_BIT, data & 0x20);
	HAL_GPIO_WritePin(GPIOA, LCD_D6_BIT, data & 0x40);
	HAL_GPIO_WritePin(GPIOA, LCD_D7_BIT, data & 0x80);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_D4_BIT, data & 0x01);
	HAL_GPIO_WritePin(GPIOA, LCD_D5_BIT, data & 0x02);
	HAL_GPIO_WritePin(GPIOA, LCD_D6_BIT, data & 0x04);
	HAL_GPIO_WritePin(GPIOA, LCD_D7_BIT, data & 0x08);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	delay(5);
}

void lcd_write_data(uint8_t data)
{
	HAL_GPIO_WritePin(GPIOC, LCD_RS_BIT, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_D4_BIT, data & 0x10);
	HAL_GPIO_WritePin(GPIOA, LCD_D5_BIT, data & 0x20);
	HAL_GPIO_WritePin(GPIOA, LCD_D6_BIT, data & 0x40);
	HAL_GPIO_WritePin(GPIOA, LCD_D7_BIT, data & 0x80);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_D4_BIT, data & 0x01);
	HAL_GPIO_WritePin(GPIOA, LCD_D5_BIT, data & 0x02);
	HAL_GPIO_WritePin(GPIOA, LCD_D6_BIT, data & 0x04);
	HAL_GPIO_WritePin(GPIOA, LCD_D7_BIT, data & 0x08);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	delay(5);
}

void lcd_write_string(const char *s)
{
	while (*s) {
		lcd_write_data(*s++);
	}
}

void lcd_write_number(uint32_t num)
{
	uint32_t tmp, tmp2, dgi, prev;

	/* find out how many digits we have */
	tmp = num;
	dgi = 1;
	while (tmp >= 10) {
		dgi++;
		tmp /= 10;
	}
	prev = 0;
	while (dgi) {
		tmp = num / pow(10, dgi - 1);
		tmp2 = tmp;
		tmp -= prev * 10;
		lcd_write_data(tmp + 0x30);
		prev = tmp2;
		dgi--;
	}
}

void lcd_clear(void)
{
	lcd_write_cmd(0x01);
}

void lcd_set_line(uint8_t line)
{
	if (line) {
		lcd_write_cmd(0xC0);
	} else {
		lcd_write_cmd(0x80);
	}
}

void lcd_init(void)
{
	delay(50);

	/* Reset by instruction */
	HAL_GPIO_WritePin(GPIOC, LCD_RS_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LCD_D4_BIT, 1);
	HAL_GPIO_WritePin(GPIOA, LCD_D5_BIT, 1);
	HAL_GPIO_WritePin(GPIOA, LCD_D6_BIT, 0);
	HAL_GPIO_WritePin(GPIOA, LCD_D7_BIT, 0);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	delay(5);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	delay(1);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_EN_BIT, GPIO_PIN_RESET);
	delay(1);

	lcd_write_cmd(0xF2); /* function set: 4-bit mode */
	lcd_write_cmd(0x28); /* function set: 4-bit mode, 2 lines, 5x8 dots */
	lcd_write_cmd(0x08); /* display off, cursor off, blink off */
	lcd_write_cmd(0x01); /* clear display */
	lcd_write_cmd(0x06); /* increment cursor, position shift off */
	lcd_write_cmd(0x0C); /* display on, cursor off, blink off */
}
