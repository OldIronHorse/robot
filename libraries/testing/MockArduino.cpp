#include "Arduino.h"
#include <sstream>

MockArduino MockArduino::only_one;

MockArduino::MockArduino() {
	reset();
}

MockArduino::~MockArduino() {
}

MockArduino& MockArduino::instance() {
	return only_one;
}

string MockArduino::callPinMode(int pin, int mode){
  stringstream s;
  s << "pinMode(" << pin << ", " << mode << ")";
  return s.str();
}

string MockArduino::callDigitalWrite(int pin, int value){
  stringstream s;
  s << "digitalWrite(" << pin << ", " << value<< ")";
  return s.str();
}

string MockArduino::callAnalogWrite(int pin, int value){
  stringstream s;
  s << "analogWrite(" << pin << ", " << value<< ")";
  return s.str();
}

string MockArduino::callDelayMicroseconds(int mu_sec){
  stringstream s;
  s << "delayMicroseconds(" << mu_sec << ")";
  return s.str();
}

void MockArduino::reset() {
	for(int i = 0; i < 14; ++i) {
		pin_mode[i] = -1;
		pin_in[i] = -1;
		pin_out[i] = -1;
	}
  millis = 1000;
  calls.clear();
}

void MockArduino::dumpCalls(ostream& os){
  for(vector<string>::iterator i = MockArduino::instance().calls.begin();
      i != MockArduino::instance().calls.end();
      i++){
    os << *i << endl;
  }
}

void MockArduino::digitalWrite(int pin, int value){
  pin_out[pin] = value;
  calls.push_back(callDigitalWrite(pin, value));
}

void MockArduino::analogWrite(int pin, int value){
  pin_out[pin] = value;
  calls.push_back(callAnalogWrite(pin, value));
}

void MockArduino::pinMode(int pin, int mode){
  pin_mode[pin] = mode;
  calls.push_back(callPinMode(pin, mode));
}

void MockArduino::delayMicroseconds(int mu_sec){
  calls.push_back(callDelayMicroseconds(mu_sec));
}

void pinMode(int pin, int mode) {
	MockArduino::instance().pinMode(pin, mode);
}

int digitalRead(int pin) {
	return MockArduino::instance().pin_in[pin];
}

void digitalWrite(int pin, int value) {
	MockArduino::instance().digitalWrite(pin, value);
}

void analogWrite(int pin, int value) {
	MockArduino::instance().analogWrite(pin, value);
}

void delay(int u_sec) {
}

void delayMicroseconds(int mu_sec) {
  MockArduino::instance().delayMicroseconds(mu_sec);
}

int millis() {
  return MockArduino::instance().millis;
}
