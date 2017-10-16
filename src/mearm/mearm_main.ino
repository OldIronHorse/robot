#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Wire.h>
#include <wiinunchuk.h>
#include <Servo.h>

/* Calibration (mu sec)
 * gripper  (9) 1800 2325
 * elbow    (6) 1150 2370
 * shoulder (5)  350 2350
 * pan      (3)  800 2400 
 */

Servo shoulder;
Servo elbow;
Servo pan;
Servo gripper;
#define ELBOW_MIN 1150
#define ELBOW_MAX 2370
int mus_elbow = (ELBOW_MAX+ELBOW_MIN)/2;
#define SHOULDER_MIN 1350
#define SHOULDER_MAX 2350
int mus_shoulder = (SHOULDER_MAX+SHOULDER_MIN)/2;
#define GRIPPER_MIN 1800
#define GRIPPER_MAX 2325
int mus_gripper = (GRIPPER_MAX+GRIPPER_MIN)/2;
#define PAN_MIN 800
#define PAN_MAX 2400
int mus_pan = (PAN_MAX+PAN_MIN)/2;

void setup(){
  DEBUG_INIT(9600);
  nunchuk_init();
  elbow.attach(6);
  pan.attach(3);
  gripper.attach(9);
  shoulder.attach(5);
}

#define MAX_STEP 15
int delta_t = 5;
int last_t = 0;

void loop(){
  int now_t = millis();
  if(now_t - last_t > delta_t){
    int delta_g = 0;
    int delta_e = 0;
    int delta_s = 0;
    int delta_p = 0;
    last_t = now_t;
    nunchuk_get_data();
    int zbutton = nunchuk_zbutton();
    int xjoy = nunchuk_cjoy_x();
    if(abs(xjoy) > 5){
      if(zbutton){
        delta_g = map(xjoy, 0, 100, 0, MAX_STEP);
      }else{
        delta_p = -1 * map(xjoy, 0, 100, 0, MAX_STEP);
      }
    }
    int yjoy = nunchuk_cjoy_y();
    if(abs(yjoy) > 5){
      if(zbutton){
        delta_e = map(yjoy, 0, 100, 0, MAX_STEP);
      }else{
        delta_s = map(yjoy, 0, 100, 0, MAX_STEP);
      }
    }
    DEBUG_PRINT(xjoy)
    DEBUG_PRINT(',')
    DEBUG_PRINT(yjoy)
    DEBUG_PRINT(',')
    DEBUG_PRINT(zbutton)
    DEBUG_PRINT(' ')
    DEBUG_PRINT(delta_p)
    DEBUG_PRINT(':')
    DEBUG_PRINT(delta_s)
    DEBUG_PRINT(':')
    DEBUG_PRINT(delta_e)
    DEBUG_PRINT(xjoy)
    DEBUG_PRINT(':')
    DEBUG_PRINT(delta_g)
    DEBUG_PRINTLN()
    mus_gripper = max(GRIPPER_MIN, min(GRIPPER_MAX, mus_gripper + delta_g));
    mus_elbow = max(ELBOW_MIN, min(ELBOW_MAX, mus_elbow + delta_e));
    mus_shoulder = max(SHOULDER_MIN, min(SHOULDER_MAX, mus_shoulder + delta_s));
    mus_pan = max(PAN_MIN, min(PAN_MAX, mus_pan + delta_p));
  }
  elbow.writeMicroseconds(mus_elbow);
  shoulder.writeMicroseconds(mus_shoulder);
  gripper.writeMicroseconds(mus_gripper);
  pan.writeMicroseconds(mus_pan);
}
