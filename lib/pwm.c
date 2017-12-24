/*
  pwm.c: Utility functions for pwm usage

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

#include <pwm.h>

#include <stdio.h>
#include <galileo2io.h>

void pwm_set_enable(int pwm_nb, int enable);

void pwm_enable(int pwm_nb)
{
  pwm_set_enable(pwm_nb, 1);
}
void pwm_disable(int pwm_nb)
{
  pwm_set_enable(pwm_nb, 0);
}

void pwm_set_enable(int pwm_nb, int enable)
{
  char enable_file[100];
  char str[80];

  sprintf(enable_file, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwm_nb);
  snprintf(str, sizeof str, "%d\n", enable);
  pputs(enable_file, str);
}

void pwm_set_period(int period)
{
  char str[80];
  snprintf(str, sizeof str, "%d\n", period);
  pputs("/sys/class/pwm/pwmchip0/device/pwm_period", str);
}
void pwm_set_duty_cycle(int pwm_nb, int duty_cycle)
{
  char duty_file[100];
  char str[80];
  sprintf(duty_file, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_nb);

  snprintf(str, sizeof str, "%d\n", duty_cycle);
  pputs(duty_file, str);
}

void pwm_set(int pwm_nb, int period, int duty_cycle, int enable)
{
  pwm_set_period(period);
  pwm_set_duty_cycle(pwm_nb, duty_cycle);
  pwm_set_enable(pwm_nb, enable);
}
