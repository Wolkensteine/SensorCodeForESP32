// Imports
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Defines & Variables
#define DHTPIN 27
#define DHTTYPE DHT11

Adafruit_MPU6050 mpu;

DHT dht(DHTPIN, DHTTYPE);

String out = "Hi";
const int rs = 33, en = 12, d4 = 18, d5 = 19, d6 = 17, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  // Serial
  Serial.begin(9600);

  // Temp
  dht.begin();

  // LCD
  lcd.begin(16, 2);
  lcd.print("Welcome!");

  // MPU
  Serial.println("Adafruit MPU6050 test!");
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  // Short delay
  delay(2500);

}

void loop() {

  // Temp
  Serial.println("===== DHT11 DATA ======");
  Serial.println("Temperature " + (String)dht.readTemperature() + " Humidity " + (String)dht.readHumidity());
  Serial.println("");

  // LCD
  lcd.begin(16, 2);
  lcd.print(" Temp    Humi");
  lcd.setCursor(0, 1);
  out = (String)dht.readTemperature() + "C  " + (String)dht.readHumidity() + "%";
  lcd.print(out);

  // MPU update
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // MPU print values
  Serial.println("===== MPU DATA =====");
  Serial.println("Acceleration X: " + (String)a.acceleration.x + " m/s^2, Y: " + (String)a.acceleration.y + " m/s^2, Z: " + (String)a.acceleration.z + " m/s^2");
  Serial.println("Rotation X: " + (String)g.gyro.x + " rad/s, Y: " + (String)g.gyro.y + " rad/s, Z: " + (String)g.gyro.z + " rad/s");
  Serial.println("Temperature: " + (String)temp.temperature + " degC");
  Serial.println("");

  // Delay
  delay(1000);

}
