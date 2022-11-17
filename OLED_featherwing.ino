#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>


#define WIRE Wire
#define DHTPIN 27
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

Adafruit_MPU6050 mpu;


void setup() {

  Serial.begin(115200);

  // MPU Setup
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

  // DHT Setup
  Serial.println("Beginning DHT.");
  dht.begin();

  // OLED Setup
  Serial.println("OLED FeatherWing test");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Serial.println("OLED begun");
  delay(1000);

  display.clearDisplay();

  Serial.println("IO test");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Hello world!");
  display.setCursor(0,0);
  display.display();

}

void loop() {

  // DHT11
  Serial.println("===== DHT11 DATA ======");
  Serial.println("Temperature " + (String)dht.readTemperature() + " Humidity " + (String)dht.readHumidity());
  Serial.println("");

  // MPU update
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // MPU print values
  Serial.println("===== MPU DATA =====");
  Serial.println("Acceleration X: " + (String)a.acceleration.x + " m/s^2, Y: " + (String)a.acceleration.y + " m/s^2, Z: " + (String)a.acceleration.z + " m/s^2");
  Serial.println("Rotation X: " + (String)g.gyro.x + " rad/s, Y: " + (String)g.gyro.y + " rad/s, Z: " + (String)g.gyro.z + " rad/s");
  Serial.println("Temperature: " + (String)temp.temperature + " degC");
  Serial.println("");

  // Displaying informations
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Temperature " + (String)dht.readTemperature());
  display.println("Humidity " + (String)dht.readHumidity());
  display.println("X" + (String)a.acceleration.x + " Y" + (String)a.acceleration.y + " Z" + (String)a.acceleration.z);
  display.println("X" + (String)g.gyro.x + " Y" + (String)g.gyro.y + " Z" + (String)g.gyro.z);
  display.display();

  delay(10);

}
