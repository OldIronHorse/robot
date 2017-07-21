#include <testing.h>
#include <Arduino.h>
#include "../mearm.h"
#include "../cmdarm.h"

Mearm arm;
CmdArm arm_cmd(arm);

void setup_arm() {
  MockArduino::instance().reset();
  arm.attach(3,5,6,9);
}

DEFINE_TEST(gripper)
  arm.gripper(true);
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
  arm.gripper(false);
  assertEqual(0,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(elbow)
  arm.elbow(120);
  assertEqual(120,arm._servos[Mearm::ELBOW].m_angle);
  arm.elbow(45);
  assertEqual(45,arm._servos[Mearm::ELBOW].m_angle);
}

DEFINE_TEST(shoulder)
  arm.shoulder(120);
  assertEqual(120,arm._servos[Mearm::SHOULDER].m_angle);
  arm.shoulder(45);
  assertEqual(45,arm._servos[Mearm::SHOULDER].m_angle);
}

DEFINE_TEST(pan)
  arm.pan(120);
  assertEqual(120,arm._servos[Mearm::PAN].m_angle);
  arm.pan(45);
  assertEqual(45,arm._servos[Mearm::PAN].m_angle);
}

DEFINE_TEST(initial_position)
  arm.init();
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
  assertEqual(90,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(90,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(90,arm._servos[Mearm::PAN].m_angle);
}

void setup_coordinated(){
  setup_arm();
  arm.init();
}

DEFINE_TEST(move_to)
  arm.move_to(135,10,120,false);
  while(arm.is_moving()){
    /*
    cout << "Moving..." << arm._step << "/" << arm._step_count << endl;
    for(int i = 0; i < 4; ++i){
      cout << arm._start[i] << " -> " << arm._end[i] << "[" << arm._step_size[i] << "]" << endl;
    }*/
    arm.move();
  }
  assertEqual(135,arm._servos[Mearm::PAN].m_angle);
  assertEqual(10,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(120,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(0,arm._servos[Mearm::GRIPPER].m_angle);
}

void setup_serial(){
  setup_coordinated();
  Serial.begin(9600);
}

DEFINE_TEST(cmd_move_to)
  Serial._in_buffer = "M:135:010:120:C\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(135,arm._servos[Mearm::PAN].m_angle);
  assertEqual(10,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(120,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(0,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(cmd_move_to_multiple)
  Serial._in_buffer = "M:135:010:120:C\nM:45:70:35:O\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(135,arm._servos[Mearm::PAN].m_angle);
  assertEqual(10,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(120,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(0,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(cmd_unknown)
  Serial._in_buffer = "X:135:010:120:C\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(90,arm._servos[Mearm::PAN].m_angle);
  assertEqual(90,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(90,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(cmd_no_command)
  Serial._in_buffer = "135\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(90,arm._servos[Mearm::PAN].m_angle);
  assertEqual(90,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(90,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(cmd_move_to_malformed)
  Serial._in_buffer = "M:1354010:120:C\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(90,arm._servos[Mearm::PAN].m_angle);
  assertEqual(90,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(90,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
}

DEFINE_TEST(cmd_too_long)
  Serial._in_buffer = "M:123456789012345678901234566789\n";
  while(!Serial._in_buffer.empty() || arm.is_moving()){
    arm_cmd.read();
    arm.move();
  }
  assertEqual(90,arm._servos[Mearm::PAN].m_angle);
  assertEqual(90,arm._servos[Mearm::SHOULDER].m_angle);
  assertEqual(90,arm._servos[Mearm::ELBOW].m_angle);
  assertEqual(90,arm._servos[Mearm::GRIPPER].m_angle);
}

BEGIN_TEST_SUITE(arm_dof)
ADD_TEST(gripper)
ADD_TEST(elbow)
ADD_TEST(shoulder)
ADD_TEST(pan)
ADD_TEST(initial_position)
END_TEST_SUITE

BEGIN_TEST_SUITE(coordinated_movement)
ADD_TEST(move_to)
END_TEST_SUITE

BEGIN_TEST_SUITE(arm_serial_commands)
ADD_TEST(cmd_move_to)
ADD_TEST(cmd_move_to_multiple)
ADD_TEST(cmd_unknown)
ADD_TEST(cmd_no_command)
ADD_TEST(cmd_move_to_malformed)
ADD_TEST(cmd_too_long)
END_TEST_SUITE

int main(void) {
  return run(arm_dof, setup_arm) + 
         run(coordinated_movement, setup_coordinated) +
         run(arm_serial_commands, setup_serial);
}
