#include <testing.h>
#include "../tune.h"

DEFINE_TEST(empty_tune)
  Note notes[100];
  parse_tune("\n",notes);
  assertTrue(notes[0].is_eot());
}

DEFINE_TEST(short_tune)
  Note notes[100];
  parse_tune("B0|10,A4#|5,C8|12\n",notes);
  assertEqual(Note(NOTE_B0,10),notes[0]);
  assertEqual(Note(NOTE_AS4,5),notes[1]);
  assertEqual(Note(NOTE_C8,12),notes[2]);
  assertTrue(notes[3].is_eot());
}

BEGIN_TEST_SUITE(tests_parse_tune)
ADD_TEST(empty_tune)
ADD_TEST(short_tune)
END_TEST_SUITE

int main(void){
  return run(tests_parse_tune);
}
