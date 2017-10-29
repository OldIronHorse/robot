#include <testing.h>
#include <string.h>
#include "../tune.h"

std::ostream& operator<<(std::ostream& os, const Note& note){
  os << "Note(" << note._pitch << "," << note._duration << ")";
  return os;
}


DEFINE_TEST(empty_tune)
  Note notes[100];
  parse_tune("\n",notes);
  assertEqual(NOTE_NONE,notes[0]);
}

DEFINE_TEST(short_tune)
  Note notes[100];
  parse_tune("B0|10,A4#|5,C8|12\n",notes);
  assertEqual(Note(NOTE_B0,10),notes[0]);
  assertEqual(Note(NOTE_AS4,5),notes[1]);
  assertEqual(Note(NOTE_C8,12),notes[2]);
  assertEqual(NOTE_NONE,notes[3]);
}

BEGIN_TEST_SUITE(tests_parse_tune)
ADD_TEST(empty_tune)
ADD_TEST(short_tune)
END_TEST_SUITE

int main(void){
  return run(tests_parse_tune);
}
