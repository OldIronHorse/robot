#include "Servo.h"
#include <algorithm>

using namespace std;

std::list<Servo*> Servo::inventory;

Servo* Servo::by_pin(int pin) {
  return *find_if(inventory.begin(), inventory.end(),
                  [&] (const Servo *s) {return s->m_pin == pin;});
}

Servo::Servo() 
  :m_pin(-1), m_min(-1), m_max(-1), m_angle(-1) {
  inventory.push_back(this);
}

Servo::~Servo() {
  inventory.remove(this);
}

void Servo::attach(int pin, int min, int max) {
  m_pin = pin;
  m_min = min;
  m_max = max;
}

void Servo::write(int angle) {
  m_angle = angle;
}

void Servo::writeMicroseconds(int mu_sec) {
  m_mu_sec = mu_sec;
  musec_calls.push_back(mu_sec);
}

int Servo::readMicroseconds() {
  return m_mu_sec;
}
