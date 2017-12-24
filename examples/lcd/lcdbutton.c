/*
  lcdbutton.c: Outputs string to lcd, on button push, with changing bg color

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

#include <galileo2io.h>
#include <lcd.h>

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

int main(int argc,char *argv[])
{
  int fd, fd2;
  char s;
  char *buffer1 = "    Testing";
  char *buffer2 = "      123";
  char *buffer3 = "    Colors";
  char *buffer4 = "   Changing";

  if((fd=open("/dev/i2c-0",O_WRONLY)) < 0)
  {
    printf("Opening /dev/i2c-0");
    exit(-1);
  }
  usleep(30000);	/* Wait for 30 ms after power on */

  lcd_init(fd);
  backlight_init(fd);

  set_backlight(fd, 0,0,0);

  if((fd2=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
  {
    printf("Opening /sys/class/gpio/gpio6/value");
    exit(-1);
  }

  wait_button(fd2);

  set_backlight(fd, 255,255,255);

  write_lcd(fd, 0, buffer1);
  usleep(1000000);
  write_lcd(fd, 1, buffer2);

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
  usleep(1600);	/* Wait for more then 1.53 ms */

  close(fd);
  close(fd2);

	return 0;
}
