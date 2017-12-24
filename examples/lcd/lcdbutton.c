/*
  writelcd.c: Write a string in a I2C LCD with RGB backlight

  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>
#include <galileo2io.h>

#define C4 3822192
#define D4 3405299
#define E4 3033704
#define F4 2863442
#define G4 2551020
#define A4 2272727
#define B4 2024783
#define C5 1911132

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
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

void wait_button(int fd)
{
  char s;
  for(;;)
  {
    lseek(fd,0,SEEK_SET);
    read(fd,&s,sizeof s);
    if(s == '1') break;
  }
}

//duty cycle in fraction of period
void set_pwm(int pwm_nb, int period, float duty_cycle, int enable)
{
  char duty_file[100];
  char enable_file[100];
  char str[80];
  int fd;
  int duty = ((int) period * duty_cycle);

  snprintf(str, sizeof str, "%d\n", period);
  printf("Period: %s", str);

  pputs("/sys/class/pwm/pwmchip0/device/pwm_period", str);
  sprintf(duty_file, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_nb);
  sprintf(enable_file, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwm_nb);

  if((fd=open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",O_WRONLY)) < 0)
  {
          perror("Opening duty_cycle:");
  }
  snprintf(str, sizeof str, "%d\n",duty);
  printf("Cycle: %s\n", str);
  pputs(duty_file, str);

  snprintf(str, sizeof str, "%d\n", enable);
  pputs(enable_file, str);
}

int main(int argc,char *argv[])
{
  int fd, fd2;
  char s;
  char *buffer1 = "     Acaba";
  char *buffer2 = "    Semestre";
  char *buffer3 = "    Nunca te";
  char *buffer4 = "    pedi nada";

  if((fd=open("/dev/i2c-0",O_WRONLY)) < 0) i2c_error("Opening /dev/i2c-0");
  usleep(30000);	/* Wait for 30 ms after power on */

  /* LCD initialization */
  if(ioctl(fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

  i2c_write_reg(fd,LCD_C0,LCD_FUNCTIONSET | LCD_2LINE);
  usleep(40);  /* Wait for more than 39 us */

  i2c_write_reg(fd,LCD_C0,LCD_DISPLAYSWITCH | LCD_DISPLAYON |
          LCD_CURSOROFF | LCD_BLINKOFF);
  usleep(40);	/* Wait for more then 39 us */

  i2c_write_reg(fd,LCD_C0,LCD_SCREENCLEAR);
  usleep(1600);	/* Wait for more then 1.53 ms */

  i2c_write_reg(fd,LCD_C0,LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

  /* Backlight initialization */
  if(ioctl(fd,I2C_SLAVE,BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
  i2c_write_reg(fd,BL_MODE1,0);
  i2c_write_reg(fd,BL_LEDOUT,BL_RED_GRPPWM | BL_GREEN_GRPPWM |
          BL_BLUE_GRPPWM);
  i2c_write_reg(fd,BL_MODE2,BL_DMBLNK);

  set_backlight(fd, 0,0,0);

  if((fd2=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
    i2c_error("Opening /sys/class/gpio/gpio6/value");

  wait_button(fd2);

  set_backlight(fd, 255,255,255);

  write_lcd(fd, 0, buffer1);

  set_pwm(1, C4, 0.05, 1);
  usleep(200000);
  set_pwm(1, D4, 0.05, 1);
  usleep(200000);
  set_pwm(1, E4, 0.05, 1);
  usleep(200000);
  set_pwm(1, F4, 0.05, 1);
  usleep(200000);
  set_pwm(1, G4, 0.05, 1);
  usleep(200000);
  
  write_lcd(fd, 1, buffer2);

  set_pwm(1, A4, 0.05, 1);
  usleep(200000);
  set_pwm(1, B4, 0.05, 1);
  usleep(200000);
  set_pwm(1, C5, 0.05, 1);
  usleep(500000);
  set_pwm(1, C5, 0.05, 0);

  usleep(2000000);
  write_lcd(fd, 0, buffer3);
  write_lcd(fd, 1, buffer4);
  for(;;)
  {
    set_backlight(fd, rand(),rand(),rand());
    usleep(90000);
    lseek(fd2,0,SEEK_SET);
    read(fd2,&s,sizeof s);
    if(s == '1') break;
  }

  set_backlight(fd, 0,0,0);
  i2c_write_reg(fd,LCD_C0,LCD_SCREENCLEAR);
  usleep(1600);	/* Wait for more then 1.53 ms */

  set_pwm(1, 0, 0, 0);


  close(fd);
  close(fd2);

	return 0;
}
