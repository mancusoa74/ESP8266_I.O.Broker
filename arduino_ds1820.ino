
//
//  http://playground.arduino.cc/Learning/OneWire
//
 
#include <OneWire.h>
 
#define ONEWIRE_PIN  2
 
OneWire ds(ONEWIRE_PIN);
 
void setup(void) { Serial.begin(9600); }
 
void loop()
{
  byte data[12];
 
  ds.reset();
  ds.write(0xCC);  // skip ROM
  ds.write(0x44);  // start conversion
 
  delay(1000);
 
  ds.reset();
  ds.write(0xCC);  // skip ROM
  ds.write(0xBE);  // Read Scratchpad
 
  for(byte i = 0; i < 9; i++) { data[i] = ds.read(); }
  if(OneWire::crc8(data, 8) != data[8]) { return; }
  
  int tr = (data[1] << 8) + data[0];
  Serial.print("t="); Serial.println(tr*0.0625);
  
  delay(1000);
}
 
//.
