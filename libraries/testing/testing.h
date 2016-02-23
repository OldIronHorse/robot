#include <iostream>
#include <sstream>
#include <algorithm>

#define DEFINE_TEST(name) \
void name(){ \
  cout << "Begin Test: " << #name << endl;

typedef void (*TestFunc)(void); 

using namespace std;

class TestFailedException {
  public:
    TestFailedException(const char* file_, int line_, const char* func_, const string &msg_);
    
    string file;
    int line;
    string func;
    string msg;
};

template<typename E, typename A>
void assertEqual_labeled(E expected, A actual, const char* file, int line, const char* func) {
  if(expected != actual) {
    stringstream msg;
    msg << "\tExpected: " << expected << ", Actual: " << actual << endl;
    throw TestFailedException(file, line, func, msg.str());
  }
}

template<typename E, typename A>
void assertNotEqual_labeled(E expected, A actual, const char* file, int line, const char* func) {
  if(expected == actual) {
    stringstream msg;
    msg << "\tExpected not: " << expected << ", Actual: " << actual << endl;
    throw TestFailedException(file, line, func, msg.str());
  }
}

template<class C, class P>
void assertContains_labeled(C coll, P pred, const char* file, int line, const char* func) {
  if(coll.end() == std::find_if(coll.begin(), coll.end(), pred)) {
    throw TestFailedException(file, line, func, string());
  }
}

template<class E, class A>
void assertCollectionEqual_labeled(E expected_begin, E expected_end, A actual_begin, A actual_end, const char* file, int line, const char* func) {
  E expected = expected_begin;
  A actual = actual_begin;
  while(expected != expected_end && actual != actual_end){
    if(*expected != *actual){
      stringstream msg;
      msg << "\tNot equal. First differing elements: Expected: " << *expected << " Actual: " << *actual << endl;
      throw TestFailedException(file, line, func, msg.str());
    }
    expected++;
    actual++;
  }
}

#define assertTrue(actual) assertEqual_labeled(true, actual, __FILE__, __LINE__, __func__)
#define assertFalse(actual) assertEqual_labeled(false, actual, __FILE__, __LINE__, __func__)
#define assertEqual(expected, actual) assertEqual_labeled(expected, actual, __FILE__, __LINE__, __func__)
#define assertNotEqual(expected, actual) assertNotEqual_labeled(expected, actual, __FILE__, __LINE__, __func__)
#define assertContains(coll, pred) assertContains_labeled(coll, pred, __FILE__, __LINE__, __func__)
#define assertCollectionEqual(expected_begin, expected_end, actual_begin, actual_end) assertCollectionEqual_labeled(expected_begin, expected_end, actual_begin, actual_end, __FILE__, __LINE__, __func__)

int run(TestFunc tests[], void (*setup)(void) = 0, void (*teardown)(void) = 0);
