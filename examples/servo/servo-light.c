/*
  servo-light.c: Moves servo until highest input on light sensor is found

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
  int fd, fd2;
  char str[80];

  double scale;

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

  //Opening ADC File
  if((fd2=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
  {
          perror("Opening in_voltage0raw:");
          return -1;
  }

  pgets(str,sizeof str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
  scale=atof(str)/1000.0;
  pputs("/sys/class/pwm/pwmchip0/device/pwm_period","20000000");

  pwm_set_enable(1, 1);


  int pos, best_pos;
  float light_measure = 0, best_light = 0;

  while(1){
    best_light = 0;
    for(pos = -90; pos < 90; pos++)
    {
      servo_set_angle(1, SERVO_MAX, SERVO_MIN, pos);

      lseek(fd2,0,SEEK_SET);
      read(fd2,str,sizeof str);
      light_measure=atoi(str)*scale;

      if(light_measure > best_light)
      {
        best_pos = pos;
        best_light = light_measure;
      }

      sprintf(str, "%d d %.2f v", pos, light_measure);
      write_lcd(fd, 0, str);

      sprintf(str, "%d d %.2f v", best_pos, best_light);
      write_lcd(fd, 1, str);
    }
    servo_set_angle(1, SERVO_MAX, SERVO_MIN, best_pos);

    sprintf(str, "%d d %.2f l", pos, light_measure);
    write_lcd(fd, 0, str);

    sprintf(str, "%d d %.2f r", best_pos, best_light);
    write_lcd(fd, 1, str);
    
    usleep(1000000);
  }





  return 0;

}
