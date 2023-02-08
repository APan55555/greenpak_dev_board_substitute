#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin();
  Wire.setClock(400000);
}

uint8_t bytes[256];

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  int thingy = Wire.requestFrom(0x00, 255);
  Serial.println(thingy);
  Serial.println('s');
  for (int i = 0; i < 255; ++i) {
    Serial.println(Wire.read());
  }
  while (true) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

int program(uint8_t bytes[]) {
  delay(10);
  //disable mem protection
  Wire.beginTransmission(0);
  Wire.write(0xF5);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();

  //enable hv sleep mode
  Wire.beginTransmission(0);
  Wire.write(0x11);
  Wire.write(0xFC);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.write(0x03);
  Wire.endTransmission();

  //write nvm mem
  Wire.beginTransmission(0);
  Wire.write(0x00);
  Wire.write(bytes, 187);
  int res = Wire.endTransmission();

  //write i2c config
  
  Wire.beginTransmission(0);
  Wire.write(0xFD);
  Wire.write(0x00);
  Wire.write(0x02);
  Wire.endTransmission();
  return res;
}
