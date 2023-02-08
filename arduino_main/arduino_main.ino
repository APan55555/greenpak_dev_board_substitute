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
  for (int i = 0; i < 256; ++i) {
    Serial.read();
    while (Serial.available() == 0);
    bytes[i] = Serial.parseInt();
    Serial.print(1);
  }

  int result = program(bytes);

  /*for (int i = 0; i < 5; ++i) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }*/
  
  digitalWrite(LED_BUILTIN, HIGH);
  /*Wire.beginTransmission(0);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(0, 1);
  for (int i = 0; i < 1; ++i) {
    Serial.println(Wire.read());
  }*/
  while (true) {
    while (Serial.available() == 0);
    char thing = Serial.read();
    if (thing == 'h') {
      int adr;
      for (adr = 0; adr < 128; ++adr) {
        Wire.beginTransmission(adr);
        Wire.write(0x00);
        int res = Wire.endTransmission();
        if (res == 0) break;
      }
      Serial.print(result);
      Serial.print(adr);
      int thingy = Wire.requestFrom(adr, 255);
      Serial.print(thingy);
      Serial.print('s');
      for (int i = 0; i < 255; ++i) Serial.println(Wire.read());
      break;
    }
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
  Wire.write(bytes, 254);
  int res = Wire.endTransmission();

  //write i2c config
  
  Wire.beginTransmission(0);
  Wire.write(0xFD);
  Wire.write(0x00);
  Wire.write(0x02);
  Wire.endTransmission();
  return res;
}
