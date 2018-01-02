/*
  string-tx.c: Attempt at string transmission protocol

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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <galileo2io.h>

#include "tx-protocol.h"

void tx_preamble(double op_freq, int fd);

void write_gpio(int fd, char *buf, int size)
{
  lseek(fd, 0, SEEK_SET);
  write(fd, buf, size);
}

void enable_out(int fd)
{
  write_gpio(fd, "1", 2);
}

void disable_out(int fd)
{
  write_gpio(fd, "0", 2);
}

char get_bit(char byte, int bit_pos)
{
  if(bit_pos >= 8 || bit_pos < 0)
  {
    printf("Out of Byte range: %d\n", bit_pos);
    exit(-1);
  }
  return ((byte >> bit_pos) & (1));
}

void tx_char(char c, int sig_period, int fd)
{
  int i;
  char bit;
  printf("Transimitting Char: %c\n", c);
  for(i = 0; i < 8; i++)
  {
    bit = get_bit(c, i);
    //printf("Transimitting Bit: %d\n", bit);
    if(bit)
    {
      enable_out(fd);
      usleep(sig_period);
      disable_out(fd);
    }
    else
      usleep(sig_period);
  }
}

void tx_string(char *str, double op_freq, int fd)
{
  int wait_p = 1000000 * 1.0/op_freq; // period in microsecs
  int i = 0;
  char c;
  printf("Transimitting String: %s\n", str);
  do {
    if(i % 5 == 0)
    {
      disable_out(fd);
      usleep(5*wait_p);
      tx_preamble(op_freq, fd);
    }
    c = str[i++];
    tx_char(c, wait_p, fd);


  } while(c != 0);
}

void tx_preamble(double op_freq, int fd)
{
  int wait_p = 1000000 * 1.0/op_freq; // period in microsecs
  printf("SYNC\n");
  int i;

  //printf("Transimitting Preamble, Length = %d\n", PREAMBLE_LENGTH);
  for(i = 0; i < PREAMBLE_LENGTH; i++)
  {
    //printf("Transimitting Bit: 1\n");
    enable_out(fd);
    usleep(wait_p);
    //printf("Transimitting Bit: 0\n");
    disable_out(fd);
    usleep(wait_p);
  }
}

int main(int argc, char* argv[])
{
  char str[] = "olar-abcdefghijklmnopqrstuvwxyz";
  int fd;
  int freq = 75;

  fd = open("/sys/class/gpio/gpio62/value",O_WRONLY);
  tx_string(str, freq, fd);

  return 0;
}
