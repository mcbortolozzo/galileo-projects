#include "music.h"

int main(int argc, char** argv)
{
  tune_t *test_tune = new_tune(112, 4, QUARTER);
  
  measure_t *measure = append_measure(test_tune);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, G, 2, SHARP, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_pause(measure, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_pause(measure, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, G, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, E, 3, NONE, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, E, 2, NONE, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, E, 3, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);

  measure = append_measure(test_tune);

  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, C, 3, SHARP, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, QUARTER, 1);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, QUARTER, 0);
  append_pause(measure, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, B, 3, NONE, SIXTEENTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, B, 3, NONE, SIXTEENTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  //

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, QUARTER, 1);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 1);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, F, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, G, 3, SHARP, SIXTEENTH, 0);
  append_note(measure, B, 3, NONE, SIXTEENTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);
  append_note(measure, E, 3, NONE, QUARTER, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, F, 2, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);

//

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 2, NONE, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);
  append_note(measure, E, 3, NONE, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);
  append_note(measure, E, 3, NONE, QUARTER, 0);
  append_note(measure, F, 3, SHARP, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 1);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 1);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, C, 4, SHARP, EIGTH, 0);
  append_note(measure, B, 3, NONE, EIGTH, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 1);
  append_note(measure, F, 3, SHARP, EIGTH, 0);
  append_note(measure, E, 3, NONE, QUARTER, 0);
  append_note(measure, E, 3, NONE, EIGTH, 0);
  append_note(measure, F, 3, SHARP, EIGTH, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 3, SHARP, QUARTER, 1);
  append_note(measure, B, 3, NONE, EIGTH, 0);
  append_note(measure, G, 3, SHARP, HALF, 0);

  play_tune(test_tune, 1);

  return 0;
}
