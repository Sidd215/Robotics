#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <EEPROM.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29); // Ensure the correct I2C address

void saveCalibrationData() {
    uint8_t calibrationData[22];
    bno.getSensorOffsets(calibrationData);

    for (int i = 0; i < 22; i++) {
        EEPROM.write(i, calibrationData[i]);
    }
    EEPROM.commit(); // Required to actually save on ESP32
    Serial.println("Calibration saved!");
}

void setup() {
    Serial.begin(115200);
    EEPROM.begin(32); // ESP32 requires EEPROM.begin(size)

    if (!bno.begin()) {
        Serial.println("BNO055 not detected. Check wiring!");
        while (1);
    }

    Serial.println("Move sensor to calibrate...");

    while (true) {
        uint8_t system, gyro, accel, mag;
        bno.getCalibration(&system, &gyro, &accel, &mag);

        Serial.print("Sys: "); Serial.print(system);
        Serial.print(", Gyro: "); Serial.print(gyro);
        Serial.print(", Accel: "); Serial.print(accel);
        Serial.print(", Mag: "); Serial.println(mag);

        if (system == 3 && gyro == 3 && accel == 3 && mag == 3) {
            Serial.println("Fully Calibrated!");
            saveCalibrationData();
            break;
        }
        delay(500);
    }
}

void loop() {
    // Once calibrated, no need to run loop
}
