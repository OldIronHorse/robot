// Mock Arduino header file
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class MockArduino {
	public:
		static MockArduino& instance();
    void reset();

    void digitalWrite(int pin, int value);
    void analogWrite(int pin, int value);
    void pinMode(int pin, int mode);
    void delayMicroseconds(int mu_sec);

    static string callPinMode(int pin, int mode);
    static string callDigitalWrite(int pin, int value);
    static string callAnalogWrite(int pin, int value);
    static string callDelayMicroseconds(int mu_sec);

    void dumpCalls(ostream& os);

		int pin_out[14];
		int pin_in[14];
		int pin_mode[14];

    int millis;

    vector<string> calls;

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
void delay(int m_sec);
void delayMicroseconds(int mu_sec);
int millis();
}
