/*
  lcd-servo.c: Outputs servo position to lcd, on button press saves position

  Original work Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>
  Modified work Copyright (c) 2017 Marcelo Cardoso Bortolozzo <mcbortolozzo@inf.ufrgs.br>

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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <galileo2io.h>
#include <lcd.h>
#include <servo.h>
#include <pwm.h>

int main(int argc, char* argv[])
{
  int fd, fd2, fd3;
  char str[80];

  double servo_pos;
  double saved_pos = 0;
  double scale;
  char s;
  int initialized = 0;

  //Set up LCD
  if((fd=open("/dev/i2c-0",O_WRONLY)) < 0)
  {
    printf("Opening /dev/i2c-0");
    exit(-1);
  }
  usleep(30000);	/* Wait for 30 ms after power on */

  lcd_init(fd);
  backlight_init(fd);

  set_backlight(fd, 0,0,0);

  //Opening Button File
  if((fd2=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
  {
    printf("Opening /sys/class/gpio/gpio6/value");
    exit(-1);
  }

  //Opening ADC File
  if((fd3=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
  {
          perror("Opening in_voltage0raw:");
          return -1;
  }

  pgets(str,sizeof str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
  scale=atof(str)/1000.0;
  pputs("/sys/class/pwm/pwmchip0/device/pwm_period","20000000");

  pwm_set_enable(1, 1);

  for(;;)
  {
          lseek(fd3,0,SEEK_SET);
          read(fd3,str,sizeof str);
          servo_pos=180.0*atoi(str)*scale/5 - 90.0;

          servo_set_angle(1, SERVO_MAX, SERVO_MIN, servo_pos);

          lseek(fd2,0,SEEK_SET);
          read(fd2,&s,sizeof s);
          if(s == '1')
          {
            initialized = 1;
            saved_pos = servo_pos;
          }

          sprintf(str, "%.2f d %.2f r", servo_pos, M_PI*servo_pos/180.0);
          write_lcd(fd, 0, str);

          if(initialized)
          {
            sprintf(str, "%.2f d %.2f r", saved_pos, M_PI*saved_pos/180.0);
            write_lcd(fd, 1, str);
          }

          if(initialized && servo_pos <= saved_pos + 5 && servo_pos >= saved_pos - 5)
            set_backlight(fd, 255, 255, 0);
          else
            set_backlight(fd, 255, 255, 255);
  }


}
