void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

int bytes[256];

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 256; ++i) {
    Serial.read();
    while (Serial.available() == 0);
    bytes[i] = Serial.parseInt();
    Serial.print(1);
  }

  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 256; ++i) {
    Serial.println(bytes[i]);
  }
}
