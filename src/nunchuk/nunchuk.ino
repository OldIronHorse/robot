#include <Wire.h>
#include <wiinunchuk.h>

void setup(){
  Serial.begin(9600);
  nunchuk_init();
}

void loop(){
  nunchuk_get_data();
  Serial.print(nunchuk_zbutton());
  Serial.print('|');
  Serial.print(nunchuk_cbutton());
  Serial.print('|');
  Serial.print(nunchuk_cjoy_x());
  Serial.print('|');
  Serial.print(nunchuk_cjoy_y());
  Serial.print('|');
  Serial.print(nunchuk_caccelx());
  Serial.print('|');
  Serial.print(nunchuk_caccely());
  Serial.print('|');
  Serial.print(nunchuk_caccelz());
  Serial.println();
}
