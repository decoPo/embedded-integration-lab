#include <Wire.h>

// I2C scanner for Arduino Nano ESP32 (3.3 V native).
// SDA = A4, SCL = A5. External 4.7 kOhm pull-ups to 3.3 V required.

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  Wire.setClock(100000);

  Serial.println(F("I2C scanner ready. External pull-ups required."));
  Serial.print(F("A4 idle="));
  Serial.print(digitalRead(A4));
  Serial.print(F("  A5 idle="));
  Serial.println(digitalRead(A5));
  Serial.println(F("(both should read 1 if external pull-ups are wired)"));
  delay(1500);
}

void loop() {
  byte found = 0;

  Serial.println(F("---- scanning 0x01..0x7E ----"));
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte err = Wire.endTransmission();
    if (err == 0) {
      Serial.print(F("  device at 0x"));
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
      found++;
    }
  }

  if (found == 0) {
    Serial.println(F("  (no devices)"));
  } else {
    Serial.print(F("done - "));
    Serial.print(found);
    Serial.println(F(" device(s)"));
  }
  Serial.println();

  delay(3000);
}
