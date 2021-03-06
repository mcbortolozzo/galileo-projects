/*
  string-rcv.c: Attempt at string transmission protocol

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
#include <sys/time.h>

#include <galileo2io.h>

#include "tx-protocol.h"

int get_sig_value(int fd)
{
  char data_str[80];

  lseek(fd,0,SEEK_SET);
  read(fd,data_str,sizeof data_str);
  //printf("%s\n", data_str);
  return atoi(data_str);
}


int get_noise_avg(int fd, int nb_measures)
{
  int i;
  float avg = 0;
  char data_str[80];
  int raw = 0;

  for(i = 0; i < nb_measures; i++)
  {
          lseek(fd,0,SEEK_SET);
          read(fd,data_str,sizeof data_str);
          raw=atoi(data_str);
          avg += ((float) raw)/ nb_measures;

          usleep(1000);
  }
  return avg;
}

double read_preamble(int fd, int threshold)
{
  double period = 0;
  int i;
  printf("SYNC\n");

  for(i = 0; i < PREAMBLE_LENGTH; i++)
  {
    while(get_sig_value(fd) < threshold);
    printf("read val\n");
    while(get_sig_value(fd) > threshold);
  }
  return period;
}

char rcv_char(int fd, int threshold, int period)
{
  int i;
  char rcvd = 0;
  for(i = 0; i < 8; i++)
  {
    usleep(period/2);
    int sig = get_sig_value(fd) > threshold ? 1 : 0;;
    rcvd |= sig << i;
    //printf("SIG: %d\n", sig);

    usleep(period/2);
  }
  return rcvd;
}

int main(int argc, char* argv[])
{
  int fd;
  char str[80];
  int i;
  double freq = 75.0;

  if((fd=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
  {
          perror("Opening in_voltage0raw:");
          exit(-1);
  }
  printf("NOISE AVG: %d\n", get_noise_avg(fd, 100));
  printf("Setting up Receiver\n");
  int ref = 1300;// * SIG_THRESHOLD;
  printf("Waiting for Preamble\n");
  printf("threshold = %d\n", ref);

  char rcvd_char = 0;
  i = 0;
  do
  {
    if(i % 5 == 0)
    {
      usleep(2*1000000/freq);
      read_preamble(fd, ref);
      usleep(1000000/freq);
    }
    rcvd_char = rcv_char(fd, ref, 1000000/freq);
    printf("Received: %c\n", rcvd_char);
    str[i++] = rcvd_char;

  } while(rcvd_char != 0);

  printf("Done, received: %s\n", str);

  close(fd);

  return 0;
}
