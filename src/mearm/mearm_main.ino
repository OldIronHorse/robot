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

enum Joint {GRIPPER, ELBOW, SHOULDER, PAN};
#define JOINTS 4
Servo joints[4];
const int pins[] = {9, 6, 5, 3};
const int min_mu_sec[] = {1800, 1150, 1350, 800};
const int max_mu_sec[] = {2325, 2370, 2350, 2400};
int mu_sec[4];

void setup(){
  DEBUG_INIT(9600);
  nunchuk_init();
  for(int s = 0; s < 4; ++s){
    joints[s].attach(pins[s]);
    mu_sec[s] = (max_mu_sec[s] + min_mu_sec[s]) / 2;
  }
}

#define MAX_STEP 15
#define DELTA_T 5
int last_t = 0;

void loop(){
  int now_t = millis();
  if(now_t - last_t > DELTA_T){
    int deltas[] = {0, 0, 0, 0};
    last_t = now_t;
    nunchuk_get_data();
    int zbutton = nunchuk_zbutton();
    int xjoy = nunchuk_cjoy_x();
    if(abs(xjoy) > 5){
      if(zbutton){
        deltas[GRIPPER] = map(xjoy, 0, 100, 0, MAX_STEP);
      }else{
        deltas[PAN] = -1 * map(xjoy, 0, 100, 0, MAX_STEP);
      }
    }
    int yjoy = nunchuk_cjoy_y();
    if(abs(yjoy) > 5){
      if(zbutton){
        deltas[ELBOW] = map(yjoy, 0, 100, 0, MAX_STEP);
      }else{
        deltas[SHOULDER] = map(yjoy, 0, 100, 0, MAX_STEP);
      }
    }
#ifdef DEBUG_OUTPUT
    DEBUG_PRINT(xjoy)
    DEBUG_PRINT(',')
    DEBUG_PRINT(yjoy)
    DEBUG_PRINT(',')
    DEBUG_PRINT(zbutton)
    DEBUG_PRINT(' ')
    for(int i = 0; i < 4; ++i){
      DEBUG_PRINT(deltas[i])
      DEBUG_PRINT(':')
    }
    DEBUG_PRINTLN()
#endif //DEBUG_OUTPUT
    for(int i = 0; i < 4; ++i){
      mu_sec[i] = max(min_mu_sec[i], min(max_mu_sec[i], mu_sec[i] + deltas[i]));
      joints[i].writeMicroseconds(mu_sec[i]);
    }
  }
}
