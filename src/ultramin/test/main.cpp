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
  assertEqual(Note::NONE,notes[0]);
}

DEFINE_TEST(short_tune)
  Note notes[100];
  parse_tune("31|10,117|5,4186|12\n",notes);
  assertEqual(Note(31,10),notes[0]);
  assertEqual(Note(117,5),notes[1]);
  assertEqual(Note(4186,12),notes[2]);
  assertEqual(Note::NONE,notes[3]);
}

BEGIN_TEST_SUITE(tests_parse_tune)
ADD_TEST(empty_tune)
ADD_TEST(short_tune)
END_TEST_SUITE

int main(void){
  return run(tests_parse_tune);
}
