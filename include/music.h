/*
  music.h: Musical Functionalities for microcontroller buzzer

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
#ifndef MUSIC_H
#define MUSIC_H

//Note Durations
#define WHOLE     1
#define HALF      2
#define QUARTER   4
#define EIGTH     8
#define SIXTEENTH 16

//Note Types
#define NOTE      50
#define PAUSE     51

//Note Letters
#define A         70
#define B         71
#define C         72
#define D         73
#define E         74
#define F         75
#define G         76

//Note Modifiers
#define NONE      90
#define FLAT      91
#define SHARP     92

//Print Modes
#define SIMPLE    100 // Note names only
#define SIMPLE_V  101 // Measures and detailed notes

typedef struct Note
{
  int type; //note or pause
  int letter;
  int octave; // numbered according to piano keys
  int modifier;
  int duration; //reference to duration type not duration itself
  int dot_count;
  int volume; // (0 - 100)%
  struct Note *next;
} note_t;

typedef struct Measure
{
  note_t *notes;
  struct Measure *next;
} measure_t;

typedef struct Signature
{
  int beat_count;
  int note_value;
} signature_t;

typedef struct Tune
{
  int tempo;
  signature_t *signature;
  measure_t *measures;
} tune_t;

tune_t *new_tune(int tempo, int beat_count, int note_value);
measure_t *append_measure(tune_t *tune);
note_t *append_pause(measure_t *measure, int duration, int dot_count);
note_t *append_note(measure_t *measure,
                    int letter,
                    int octave,
                    int modifier,
                    int duration,
                    int dot_count
                  );

void play_tune(tune_t *tune, int pwm_nb);
void print_tune(tune_t *tune, int mode);

//Not implemented yet
int export_tune(int outfile, tune_t *tune);
tune_t *import_tune(int infile);

#endif
