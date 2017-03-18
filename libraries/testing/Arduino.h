// Mock Arduino header file
#ifndef Arduino_h
#define Arduino_h
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

class MockArduino {
	public:
		static MockArduino& instance();
    void reset();

    void digitalWrite(int pin, int value);
    void analogWrite(int pin, int value);
    int analogRead(int pin);
    void pinMode(int pin, int mode);
    void delayMicroseconds(int mu_sec);
    long random(int min, int max);

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

//#define random(a,b) random_(a,b)
#endif
