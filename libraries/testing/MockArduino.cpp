#include "Arduino.h"
#include <sstream>
#include <iostream>
#include <bitset>

using namespace std;

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

string MockArduino::callAnalogRead(int pin){
  stringstream s;
  s << "digitalRead(" << pin << ")";
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

int MockArduino::analogRead(int pin){
  calls.push_back(callAnalogRead(pin));
  return pin_in[pin];
}

void MockArduino::pinMode(int pin, int mode){
  pin_mode[pin] = mode;
  calls.push_back(callPinMode(pin, mode));
}

void MockArduino::delayMicroseconds(int mu_sec){
  calls.push_back(callDelayMicroseconds(mu_sec));
}

long MockArduino::random(int min, int max){
  stringstream s;
  s << "random(" << min << ", " << max << ")";
  calls.push_back(s.str());
  if(random_values.empty()){
    return min;
  }
  long value = random_values.front();
  random_values.pop_front();
  return value;
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

int analogRead(int pin) {
  return MockArduino::instance().analogRead(pin);
}

void delay(int u_sec) {
}

void delayMicroseconds(int mu_sec) {
  MockArduino::instance().delayMicroseconds(mu_sec);
}

int millis() {
  return MockArduino::instance().millis;
}

long random_(int min, int max){
  return MockArduino::instance().random(min, max);
}

void randomSeed(int n){
}

MockSerial Serial;

MockSerial::MockSerial()
:_speed(0){
  _ready = false;
}

void MockSerial::begin(int speed){
  _speed = speed;
  _in_buffer = "";
  _out_buffer = "";
  _ready = true;
};

void MockSerial::end(){
  _ready = false;
}

void Print::print(char c){
  if(_ready){
    _out_buffer.push_back(c);
  }
}

void Print::println(char c){
  if(_ready){
    _out_buffer.push_back(c);
    _out_buffer.push_back('\n');
  }
}

void Print::print(const char *szText){
  if(_ready){
    _out_buffer.append(szText);
  }
}

void Print::println(const char *szText){
  if(_ready){
    _out_buffer.append(szText);
    _out_buffer.push_back('\n');
  }
}

void Print::println(double d, int dp){
  if(_ready){
    print(d,dp);
    _out_buffer.push_back('\n');
  }
}

void Print::print(double d, int dp){
  if(_ready){
    std::stringstream ss;
    ss.precision(dp);
    ss << std::fixed << d;
    _out_buffer.append(ss.str());
  }
}

void Print::println(int n, int base){
  if(_ready){
    print(n,base);
    _out_buffer.push_back('\n');
  }
}

void Print::print(int n, int base){
  if(_ready){
    if(2 == base){ 
      std::string str(std::bitset< 64 >(n).to_string());
      str.erase(0, min(str.find_first_not_of('0'), str.size()-1));
      _out_buffer.append(str);
    }else{
      std::stringstream ss;
      switch(base){
        case 16:
          ss << std::uppercase << std::hex;
          break;
        case 8:
          ss << std::oct;
          break;
      }
      ss << n;
      _out_buffer.append(ss.str());
    }
  }
}

int Stream::read(){
  if(!_ready || _in_buffer.empty()){
    return -1;
  }else{
    char c = _in_buffer.front();
    _in_buffer.erase(0,1);
    return c;
  }
}

int Stream::peek(){
  if(!_ready || _in_buffer.empty()){
    return -1;
  }else{
    return _in_buffer.front();
  }
}

int Stream::available(){
  if(_ready){
    return _in_buffer.length();
  }else{
    return -1;
  }
}
