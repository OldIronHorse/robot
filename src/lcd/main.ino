#include <LiquidCrystal.h>
#include <Wire.h>
#include <lib/SC16IS750.h>
#include <lib/espduino.h>
#include <lib/rest.h>

#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char* padding = "                ";
volatile char message[64];
volatile const char* next_char = message;

WifiData espSerial;
ESP esp(&espSerial);
REST rest(&esp);

void setup(){
  strcpy((char*)message, "                Mary had a little lamb... ");
  lcd.begin(16,2);
  //lcd.print("Beginning espSerial...");
  espSerial.begin(9600);
  espSerial.println("LCD started....");
  lcd.setCursor(0,0);

  // BEGIN Timer setup
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624/5;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12)|(1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
  // END Timer setup

  espSerial.println("Sending request...");
	const char* connector = "rest";
	const char* server = "euterpe3.lan";
  const int port = 9000;
	const char* method = "GET";
	const char* resource = "/index.html";
  char response[64];
  strcpy(response,"__EMPTY__");
  espSerial.println(response);
  if(rest.begin(server,port,false)){
    espSerial.print("Connected to ");
    espSerial.print(server);
    espSerial.print(":");
    espSerial.println(port);
  }
  rest.get(resource);
  espSerial.println("Request sent.");
  uint16_t r = rest.getResponse(response,64);
  espSerial.print("Response returned: ");
  espSerial.println(r);
  espSerial.println(response);
}

ISR(TIMER1_COMPA_vect){
  lcd.setCursor(0,0);
  if(0 == *next_char){
    lcd.print(' ');
    next_char = message;
  }else{
    lcd.print((const char*)next_char);
    ++next_char;
  }
}

void loop(){
  /*
  char response[64];
  uint16_t r = rest.getResponse(response,64);
  espSerial.print("Response returned: ");
  espSerial.println(r);
  espSerial.println(response);
  delay(1000);
  */
}

