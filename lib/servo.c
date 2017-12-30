/*
  servo.c: Servo utility functions

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

#include <servo.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>
#include <pwm.h>

void servo_set_pos(int pwm_nb, int max_duty, int min_duty, double pos)
{
  int duty_cycle=(int)((pos*(max_duty-min_duty) + min_duty));
  pwm_set_duty_cycle(pwm_nb, duty_cycle);
}

void servo_set_angle(int pwm_nb, int max_duty, int min_duty, double angle)
{
  double ang = angle * M_PI/180.0;

  if((ang > M_PI_2) || (ang < - M_PI_2))
  {
          puts("Out of range.");
          exit(-1);
  }
  servo_set_pos(pwm_nb, max_duty, min_duty, (ang+M_PI_2)/M_PI);
}
