/*
  dac.c: Attempt at DAC using PWM

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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pwm.h>
#include <galileo2io.h>

int values[] = {50,89,99,72,28,1,11,50};
int period = 700000;
int main(int argc,char * argv[])
{
  int fd;
  char str[80];

  int duty_cycle = 0;
  int on = 1;

  if((fd=open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",O_WRONLY)) < 0)
  {
          perror("Opening in_voltage0raw:");
          return -1;
  }

  pwm_set(1, period, period/2, 1);

  for(;;)
  {
          if(duty_cycle == 7)
          {
            duty_cycle = 0;
            on = !on;
          }
          else
            duty_cycle++;
          usleep(5);

          int cycle = (int) (period * values[duty_cycle] / 100);
          snprintf(str, sizeof str, "%d\n", cycle);

          lseek(fd,0,SEEK_SET);
          write(fd,str,sizeof str);
  }

  close(fd);
}
