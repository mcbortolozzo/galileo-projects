#include "music.h"

int main(int argc, char** argv)
{
  tune_t *test_tune = new_tune(120, 4, QUARTER);
  measure_t *measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, G, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, QUARTER, 1);
  append_note(measure, D, 4, NONE, EIGTH, 0);
  append_note(measure, D, 4, NONE, HALF, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, G, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, D, 4, NONE, QUARTER, 1);
  append_note(measure, C, 4, NONE, EIGTH, 0);
  append_note(measure, C, 4, NONE, HALF, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, C, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, F, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, C, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, EIGTH, 0);
  append_note(measure, F, 4, NONE, EIGTH, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, G, 3, NONE, HALF, 0);

  //

  measure = append_measure(test_tune);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, G, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, G, 4, NONE, QUARTER, 0);
  append_note(measure, F, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, C, 4, NONE, QUARTER, 0);
  append_note(measure, D, 4, NONE, QUARTER, 0);
  append_note(measure, E, 4, NONE, QUARTER, 0);

  measure = append_measure(test_tune);
  append_note(measure, D, 4, NONE, QUARTER, 1);
  append_note(measure, C, 4, NONE, EIGTH, 0);
  append_note(measure, C, 4, NONE, HALF, 0);






  play_tune(test_tune, 1);

  return 0;
}
