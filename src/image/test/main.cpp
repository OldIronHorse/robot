#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <testing.h>
#include <Arduino.h>


void set_up() {
}

void test_no_obstruction(){
}

TestFunc tests[] = {&test_no_obstruction,
                    0};

int main(void) {
  return run(tests, set_up);
}


