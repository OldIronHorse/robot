#include <testing.h>
#include <Arduino.h>
#include "../mearm.h"

Mearm arm;

void setup_arm() {
  MockArduino::instance().reset();
  Serial.begin(9600);
  arm.attach(3,5,6,9);
}

DEFINE_TEST(gripper)
  arm.gripper_open();
  assertEqual(90,arm._gripper.m_angle);
  arm.gripper_close();
  assertEqual(0,arm._gripper.m_angle);
}

DEFINE_TEST(initial_position)
  arm.init();
  assertEqual(90,arm._gripper.m_angle);
  assertEqual(90,arm._elbow.m_angle);
  assertEqual(90,arm._shoulder.m_angle);
  assertEqual(90,arm._pan.m_angle);
}

BEGIN_TEST_SUITE(arm_dof)
ADD_TEST(gripper)
ADD_TEST(initial_position)
END_TEST_SUITE

int main(void) {
  return run(arm_dof,setup_arm);
}
