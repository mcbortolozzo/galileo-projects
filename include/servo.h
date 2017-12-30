/*
  servo.h: Servo utility functions

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

#ifndef SERVO_H
#define SERVO_H

//Min and Max obtained experimentaly, best to override
#define SERVO_MAX     2400000
#define SERVO_MIN     520000
#define SERVO_VOLTAGE 5

void servo_set_pos(int pwm_nb, int max_duty, int min_duty, double pos);
void servo_set_angle(int pwm_nb, int max_duty, int min_duty, double angle);

#endif
