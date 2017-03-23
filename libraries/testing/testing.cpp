#include "testing.h"

TestFailedException::TestFailedException(const char* file_, int line_, const char* func_, const string &msg_)
	:file(file_), line(line_), func(func_), msg(msg_) {}

int run(TestFunc tests[], void (*setup)(void), void (*teardown)(void)) {
	int passed = 0;
	int failed = 0;

  for(int n = 0; tests[n] != 0; ++n) {
    if(setup != 0) {
      setup();
    }
    try {
      tests[n]();
      passed++;
    }
    catch(TestFailedException &e) {
      failed++;
      cout << "FAILED: " << e.file << "[" << e.line << "] " << e.func << ": " << e.msg << endl; 
    }
    if(teardown != 0) {
      teardown();
    }
  }

  cout << "Tests run: " << passed + failed << ", passed: " << passed << ", failed: " << failed << endl;
	return failed;
}

