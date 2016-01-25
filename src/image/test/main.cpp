#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <testing.h>
#include <Arduino.h>
#include "../image.h"


void set_up() {
}

void test_max_index(){
  int values[] = {4,2,3,6,1,5};
  assertEqual(3, max_index(6, values));
}

void test_max_index_last(){
  int values[] = {4,2,3,1,5,6};
  assertEqual(5, max_index(6, values));
}

void test_max_index_first(){
  int values[] = {6,4,2,3,1,5};
  assertEqual(0, max_index(6, values));
}
void test_max_index_duplicate(){
  int values[] = {4,2,6,3,1,6,5};
  assertEqual(2, max_index(7, values));
}

void test_min_index(){
  int values[] = {4,2,3,1,5,6};
  assertEqual(3, min_index(6, values));
}

void test_min_index_last(){
  int values[] = {4,2,3,5,6,1};
  assertEqual(5, min_index(6, values));
}

void test_min_index_first(){
  int values[] = {1,4,2,3,5,6};
  assertEqual(0, min_index(6, values));
}

void test_min_index_duplicate(){
  int values[] = {4,1,2,3,1,5,6};
  assertEqual(1, min_index(7, values));
}

TestFunc tests[] = {&test_min_index,
                    &test_min_index_last,
                    &test_min_index_first,
                    &test_min_index_duplicate,
                    &test_max_index,
                    &test_max_index_last,
                    &test_max_index_first,
                    &test_max_index_duplicate,
                    0};

int main(void) {
  return run(tests, set_up);
}


