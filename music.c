//Author: Marcelo Bortolozzo
#include "music.h"

#define F_CONSTANT      1.059463094359
#define A4F             440

#define MIN_OCTAVE      0
#define MAX_OCTAVE      6

#define DEFAULT_VOLUME  5

////////// INTERNAL HEADERS //////////

//Cleaner Error Messages
void music_error(const char *error_msg);

//Calculate note's period in nanoseconds (truncated)
int get_note_period(note_t *note);
int half_steps_from_A4(note_t *note);

note_t * append_to_measure( measure_t *measure,
                            int type,
                            int letter,
                            int octave,
                            int modifier,
                            int duration,
                            int dot_count
                          );

note_t *new_note( int type,
                  int letter,
                  int octave,
                  int modifier,
                  int duration,
                  int dot_count,
                  int volume
                );

measure_t * new_measure();

signature_t* new_signature(int beat_count, int note_value);

//Checks measure's correctness, based on signature and its contents
int check_measure(signature_t signature);

//Outputs the note names in Order, optionally verbose
void simple_print(tune_t *tune, int verbose);
void simple_print_measure(measure_t *measure, int verbose);
void simple_print_note(note_t* note, int verbose);

void print_letter(int letter);
void print_modifier(int modifier);
void print_duration(int duration, int dot_count);

void play_measure(measure_t *measure, int pwm_nb, int tempo, int beat_note);
void play_note(note_t *note, int pwm_nb, int tempo, int beat_note);
int duration_in_micros(int duration, int dot_count, int tempo, int beat_note);
void set_pwm(int pwm_nb, int period, int duty_cycle, int enable);

////////// FUNCTION BODIES //////////

//Struct Creation

tune_t *new_tune(int tempo, int beat_count, int note_value)
{
  tune_t *tune = calloc(1, sizeof(tune_t));
  tune->tempo = tempo;
  tune->signature = new_signature(beat_count, note_value);
  tune->measures = NULL;
  return tune;
}

signature_t *new_signature(int beat_count, int note_value)
{
  signature_t *signature = calloc(1, sizeof(signature));
  signature->beat_count = beat_count;
  signature->note_value = note_value;
  return signature;
}

measure_t *new_measure()
{
  measure_t *measure = calloc(1, sizeof(measure_t));
  measure->notes = NULL;
  measure->next = NULL;
  return measure;
}

note_t *new_note( int type,
                  int letter,
                  int octave,
                  int modifier,
                  int duration,
                  int dot_count,
                  int volume
                )
{
  note_t *note = calloc(1, sizeof(note_t));
  note->type = type;
  note->letter = letter;
  note->octave = octave;
  note->modifier = modifier;
  note->duration = duration;
  note->dot_count = dot_count;
  note->volume = volume;
  note->next = NULL;
  return note;
}

//Appending Elements

measure_t *append_measure(tune_t *tune)
{
  if(!tune) music_error("Invalid Tune Object");
  if(!tune->measures)
  {
    tune->measures = new_measure();
    return tune->measures;
  }
  else
  {
    measure_t *curr = tune->measures;
    for(; curr->next; curr = curr->next);
    curr->next = new_measure();
    return curr->next;
  }
}

note_t *append_to_measure(measure_t *measure,
                          int type,
                          int letter,
                          int octave,
                          int modifier,
                          int duration,
                          int dot_count
                        )
{
  if(!measure) music_error("Invalid Measure Object");
  note_t *note =
    new_note(type, letter, octave, modifier, duration, dot_count, DEFAULT_VOLUME);
  if(!measure->notes)
    measure->notes = note;
  else
  {
    note_t *curr = measure->notes;
    for(; curr->next; curr = curr->next);
    curr->next = note;
  }
  return note;
}

note_t *append_pause(measure_t *measure, int duration, int dot_count)
{
  return append_to_measure(measure, PAUSE, 0, 0, 0, duration, dot_count);
}

note_t *append_note(measure_t *measure,
                    int letter,
                    int octave,
                    int modifier,
                    int duration,
                    int dot_count
                  )
{
  return append_to_measure(measure, NOTE, letter, octave, modifier, duration, dot_count);
}

//Output Functions

void print_tune(tune_t *tune, int mode)
{
  switch (mode) {
    case SIMPLE:      simple_print(tune, 0); break;
    case SIMPLE_V:    simple_print(tune, 1); break;
    default:          music_error("Invalid Print Mode");
  }
}

void simple_print(tune_t *tune, int verbose)
{
  measure_t *curr;
  int i = 0;
  printf("Tune, %dbpm, %d/%d\n", tune->tempo,
            tune->signature->beat_count, tune->signature->note_value);
  for(curr = tune->measures; curr; curr = curr->next)
  {
    if(verbose) printf("Measure %d\t", i);
    simple_print_measure(curr, verbose);
    printf("\n"); i++;
  }
}

void simple_print_measure(measure_t *measure, int verbose)
{
  note_t *curr;
  for(curr = measure->notes; curr; curr = curr->next)
    simple_print_note(curr, verbose);
}

void simple_print_note(note_t *note, int verbose)
{
  if(note->type == NOTE)
  {
    print_letter(note->letter);
    printf("%d", note->octave);
    print_modifier(note->modifier);
    if(verbose)
    {
      printf("(");
      print_duration(note->duration, note->dot_count);
      printf(", %d, %d)", note->volume, get_note_period(note));
    }
  }
  else
  {
    printf("PAUSE(");
    print_duration(note->duration, note->dot_count);
    printf(")");
  }
  printf("\t");
}

void print_letter(int letter)
{
  switch (letter) {
    case A:     printf("A"); break;
    case B:     printf("B"); break;
    case C:     printf("C"); break;
    case D:     printf("D"); break;
    case E:     printf("E"); break;
    case F:     printf("F"); break;
    case G:     printf("G"); break;
    default:    music_error("Invalid Note Name");
  }
}

void print_modifier(int modifier)
{
  switch (modifier) {
    case SHARP:     printf("#"); break;
    case FLAT:      printf("b"); break;
    case NONE:      break;
    default:        music_error("Invalid Note Modifier");
  }
}

void print_duration(int duration, int dot_count)
{
  switch (duration) {
    case WHOLE:       printf("WHOLE"); break;
    case HALF:        printf("HALF"); break;
    case QUARTER:     printf("QUARTER"); break;
    case EIGTH:       printf("EIGTH"); break;
    case SIXTEENTH:   printf("SIXTEENTH"); break;
    default:          music_error("Invalid Note Duration");
  }
  if(dot_count)
  {
    printf(" DOTTED");
    if(dot_count > 1) printf(" x%d", dot_count);
  }
}

//Note Period Calculation

int get_note_period(note_t *note)
{
  int n = half_steps_from_A4(note);
  double freq = A4F * pow(pow(2,1.0/12), n);
  printf("Freq: %f\n", freq);
  double period = 1/freq * pow(10, 9);
  return ((int) period);
}

int half_steps_from_A4(note_t *note)
{
  int half_steps = 0;
  //set generic letter interval
  switch (note->letter) {
    case A: break;
    case B: half_steps = 2; break;
    case C: half_steps = -9; break;
    case D: half_steps = -7; break;
    case E: half_steps = -5; break;
    case F: half_steps = -4; break;
    case G: half_steps = -2; break;
    default: music_error("Invalid Note Name");
  }

  //consider different octaves
  if(note->octave < MIN_OCTAVE || note->octave > MAX_OCTAVE)
    music_error("Invalid Octave Number");
  half_steps += 12 * (note->octave - 4);

  //add modifier
  switch (note->modifier) {
    case SHARP: half_steps++; break;
    case FLAT:  half_steps--; break;
    case NONE:  break;
    default:    music_error("Invalid Note Modifier");
  }

  return half_steps;
}

//Output to Sound

void play_tune(tune_t *tune, int pwm_nb)
{
  measure_t *curr;
  for(curr = tune->measures; curr; curr = curr->next)
    play_measure(curr, pwm_nb, tune->tempo, tune->signature->note_value);

  set_pwm(pwm_nb, 0,0,0);
}

void play_measure(measure_t *measure, int pwm_nb, int tempo, int beat_note)
{
  note_t *curr;
  for(curr = measure->notes; curr; curr = curr->next)
    play_note(curr, pwm_nb, tempo, beat_note);
}

void play_note(note_t* note, int pwm_nb, int tempo, int beat_note)
{
  simple_print_note(note, 0); printf("\n");
  int duration = duration_in_micros(note->duration, note->dot_count,
                                    tempo, beat_note);
  int period = 0;
  int duty_cycle = 0;
  int enable = 0;
  switch (note->type) {
    case NOTE:
      period = get_note_period(note);
      duty_cycle = note->volume / 2;
      enable = 1;
      break;
    case PAUSE:
      enable = 0;
      break;
    default:
      music_error("Invalid Note Type");
  }
  set_pwm(pwm_nb, period, duty_cycle, enable);

  usleep(duration* .95);
  set_pwm(pwm_nb, period, duty_cycle, 0);
  usleep(duration* .05);

}

int duration_in_micros(int duration, int dot_count, int tempo, int beat_note)
{
  float beats = ((float)beat_note) / duration;
  beats = beats * (2 - (1 / pow(2, dot_count)));
  printf("duration: %d, beats: %f\n", duration, beats);

  int micros = beats * 60000000 / tempo;
  printf("micros: %d\n", micros);
  return micros;
}

void set_pwm(int pwm_nb, int period, int duty_cycle, int enable)
{
  char duty_file[100];
  char enable_file[100];
  char str[80];
  int fd;
  int duty = period * duty_cycle / 100;

  snprintf(str, sizeof str, "%d\n", period);
  printf("Period: %s", str);

  pputs("/sys/class/pwm/pwmchip0/device/pwm_period", str);
  sprintf(duty_file, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwm_nb);
  sprintf(enable_file, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwm_nb);

  if((fd=open("/sys/class/pwm/pwmchip0/pwm1/duty_cycle",O_WRONLY)) < 0)
  {
          perror("Opening duty_cycle:");
  }
  snprintf(str, sizeof str, "%d\n",duty);
  printf("Cycle: %s\n", str);
  pputs(duty_file, str);

  snprintf(str, sizeof str, "%d\n", enable);
  pputs(enable_file, str);
}

//Error Handling

void music_error(const char *error_msg)
{
  printf("ERROR: %s\n", error_msg);
  exit(-1);
}
