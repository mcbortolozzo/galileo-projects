/*
  lcd.c: Utility for lcd usage

  Copyright (c) 2017 Marcelo Cardoso Bortolozzo <mcbortolozzo@inf.ufrgs.br>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <lcd.h>

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <i2cutil.h>
#include <jhdlcd.h>

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
}

void lcd_init(int fd)
{
  if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

  i2c_write_reg(fd,LCD_C0,LCD_FUNCTIONSET | LCD_2LINE);
  usleep(40);  /* Wait for more than 39 us */

  i2c_write_reg(fd,LCD_C0,LCD_DISPLAYSWITCH | LCD_DISPLAYON |
          LCD_CURSOROFF | LCD_BLINKOFF);
  usleep(40);	/* Wait for more then 39 us */

  i2c_write_reg(fd,LCD_C0,LCD_SCREENCLEAR);
  usleep(1600);	/* Wait for more then 1.53 ms */

  i2c_write_reg(fd,LCD_C0,LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);
}

void backlight_init(int fd)
{
  if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
  i2c_write_reg(fd,BL_MODE1,0);
  i2c_write_reg(fd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM |
          BL_BLUE_GRPPWM);
  i2c_write_reg(fd,BL_MODE2,BL_DMBLNK);
}

void set_backlight(int fd, int r, int g, int b)
{
  if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

  i2c_write_reg(fd,BL_RED,r);
  i2c_write_reg(fd,BL_GREEN,g);
  i2c_write_reg(fd,BL_BLUE,b);
}

void write_lcd(int fd, int line, const char *string)
{
  int i, n;

  if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
  if(line == 0)
  {
    i2c_write_reg(fd,LCD_C0,LCD_DDRAMADDRSET | 0);
  }
  else if(line == 1)
    i2c_write_reg(fd,LCD_C0,LCD_DDRAMADDRSET | 0x40);
  else
    i2c_error("Invalid lcd line");

  n=strlen(string);
  for(i=0;i < n;i++) i2c_write_reg(fd,LCD_RS, string[i]);
}
