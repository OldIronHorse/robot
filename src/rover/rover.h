#define PIN_SPEED_2 5
#define PIN_SPEED_1 6
#define PIN_DIRECTION_2 7
#define PIN_DIRECTION_1 8

#define MAX_SPEED 255

namespace rover{

void setup(){
  pinMode(PIN_SPEED_1, OUTPUT);
  pinMode(PIN_SPEED_2, OUTPUT);
  pinMode(PIN_DIRECTION_1, OUTPUT);
  pinMode(PIN_DIRECTION_2, OUTPUT);

  analogWrite(PIN_SPEED_1, 0);
  analogWrite(PIN_SPEED_2, 0);
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);
}

void forward(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void back(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, HIGH);
  digitalWrite(PIN_DIRECTION_2, HIGH);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void stop(){
  analogWrite(PIN_SPEED_1, 0);
  analogWrite(PIN_SPEED_2, 0);
}

void left(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, HIGH);
  digitalWrite(PIN_DIRECTION_2, LOW);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void right(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, HIGH);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

}
