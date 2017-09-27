// Mock Arduino header file
#ifndef Arduino_h
#define Arduino_h
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <string.h>
#include <iostream>

class MockArduino {
	public:
		static MockArduino& instance();
    void reset();

    void digitalWrite(int pin, int value);
    void analogWrite(int pin, int value);
    int analogRead(int pin);
    void pinMode(int pin, int mode);
    void delayMicroseconds(int mu_sec);
    long random_(int min, int max);

    static std::string callPinMode(int pin, int mode);
    static std::string callDigitalWrite(int pin, int value);
    static std::string callAnalogWrite(int pin, int value);
    static std::string callAnalogRead(int pin);
    static std::string callDelayMicroseconds(int mu_sec);

    void dumpCalls(std::ostream& os);

		int pin_out[14];
		int pin_in[14];
		int pin_mode[14];

    int millis;

    std::vector<std::string> calls;
    std::list<long> random_values;

	private:
		MockArduino();
		~MockArduino();

		static MockArduino only_one;
};

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class MockSerial{
  public:
    MockSerial();

    void begin(int speed);
    void end();
    void print(char c);
    void print(const char *szText);
    void print(int n, int base = DEC);
    void print(double d, int dp = 2);
    void println(char c);
    void println(const char* szText);
    void println(int n, int base = DEC);
    void println(double d, int dp = 2);
    int available();
    int read();
    int peek();
    void flush(){;}

    bool _ready;
    int _speed;
    std::string _out_buffer;
    std::string _in_buffer;
};

extern MockSerial Serial;

void setup(void);
void loop(void);

extern "C"{
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

void pinMode(int pin, int mode);
int digitalRead(int pin);
void digitalWrite(int pin, int value);
void analogWrite(int pin, int value);
int analogRead(int pin);
void delay(int m_sec);
void delayMicroseconds(int mu_sec);
int millis();
long int random_(int min, int max);
void randomSeed(int n);
}

template<class T>
T max(T a, T b){
  return ((a)>(b)?(a):(b));
}

#define F(a) a
#define PROGMEM
#define strncmp_P(a,b,c) strncmp(a,b,c)
#define random(a,b) random_(a,b)
#endif
