#include <Wire.h>

// MPU6500 accelerometer stream for Arduino Nano ESP32.
// Emits one ASCII line per sample matching fake_imu_data.py / the Node-RED
// "Parse KEY=VAL;..." function:
//
//   AX=0.123;AY=-0.456;AZ=0.987
//
// Wiring (Nano ESP32, 3.3 V native):
//   SDA = A4, SCL = A5, VCC = 3V3, GND = GND
//   External 4.7 kOhm pull-ups from SDA/SCL to 3V3.
//   AD0 left low -> I2C address 0x68.

static const uint8_t MPU_ADDR     = 0x68;
static const uint8_t REG_WHO_AM_I = 0x75;
static const uint8_t REG_PWR_MGMT = 0x6B;
static const uint8_t REG_ACCEL_XH = 0x3B;
static const uint8_t WHO_MPU6500  = 0x70;

// ±2 g full-scale (default after reset) -> 16384 LSB per g.
static const float ACCEL_SCALE = 1.0f / 16384.0f;

// Sample period in milliseconds (~20 Hz).
static const uint16_t SAMPLE_PERIOD_MS = 50;

static uint8_t readReg(uint8_t reg) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((int)MPU_ADDR, 1);
  return Wire.read();
}

static void writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  Wire.setClock(400000);

  uint8_t who = readReg(REG_WHO_AM_I);
  Serial.print(F("# WHO_AM_I=0x"));
  if (who < 16) Serial.print('0');
  Serial.println(who, HEX);
  if (who != WHO_MPU6500) {
    Serial.println(F("# warning: WHO_AM_I != 0x70 (expected MPU6500)"));
  }

  // Wake from sleep, internal 20 MHz oscillator.
  writeReg(REG_PWR_MGMT, 0x00);
  delay(50);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_ACCEL_XH);
  if (Wire.endTransmission(false) != 0) {
    Serial.println(F("# i2c write error"));
    delay(200);
    return;
  }

  if (Wire.requestFrom((int)MPU_ADDR, 6) != 6) {
    Serial.println(F("# i2c read short"));
    delay(200);
    return;
  }

  int16_t rawX = (Wire.read() << 8) | Wire.read();
  int16_t rawY = (Wire.read() << 8) | Wire.read();
  int16_t rawZ = (Wire.read() << 8) | Wire.read();

  float ax = rawX * ACCEL_SCALE;
  float ay = rawY * ACCEL_SCALE;
  float az = rawZ * ACCEL_SCALE;

  Serial.print(F("AX="));
  Serial.print(ax, 3);
  Serial.print(F(";AY="));
  Serial.print(ay, 3);
  Serial.print(F(";AZ="));
  Serial.println(az, 3);

  delay(SAMPLE_PERIOD_MS);
}
