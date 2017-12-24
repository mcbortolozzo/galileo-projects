/*
  pwm.h: Utility functions for pwm usage

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
#ifndef PWM_H
#define PWM_H

void pwm_enable(int pwm_nb);
void pwm_disable(int pwm_nb);

void pwm_set_period(int period);
void pwm_set_duty_cycle(int pwm_nb, int duty_cycle);

void pwm_set(int pwm_nb, int period, int duty_cycle, int enable);

#endif
