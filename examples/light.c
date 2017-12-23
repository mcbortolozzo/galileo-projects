#include "music.h"

int main(int argc, char** argv)
{
  tune_t *test_tune = new_tune(120, 4, QUARTER);
  measure_t *measure = append_measure(test_tune);
  append_note(measure, A, 4, NONE, EIGTH, 0);
  append_note(measure, A, 4, NONE, EIGTH, 0);
  append_note(measure, A, 4, NONE, EIGTH, 0);
  append_note(measure, A, 4, NONE, QUARTER, 0);
  append_note(measure, B, 4, NONE, EIGTH, 0);
  append_note(measure, B, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_pause(measure, HALF, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, SHARP, EIGTH, 0);
  append_note(measure, G, 4, SHARP, HALF, 2);

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 1);

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, SIXTEENTH, 0);
  append_note(measure, G, 4, SHARP, HALF, 2);

  measure = append_measure(test_tune);
  append_pause(measure, HALF, 0);
  append_pause(measure, QUARTER, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, G, 4, SHARP, EIGTH, 0);
  append_note(measure, A, 4, NONE, QUARTER, 1);
  append_note(measure, G, 4, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 4, SHARP, SIXTEENTH, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, HALF, 2);
  append_pause(measure, EIGTH, 0);





  play_tune(test_tune, 1);

  return 0;
}
