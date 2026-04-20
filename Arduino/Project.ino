#include <Wire.h>
#include <Servo.h>

Servo servo_1; // Forward/Backward  - Pin 4
Servo servo_2; // Up/Down           - Pin 3
Servo servo_3; // Gripper           - Pin 2
Servo servo_4; // Left/Right        - Pin 5

const int MPU_addr = 0x68;
int16_t axis_X, axis_Y, axis_Z;
int minVal = 265;
int maxVal = 402;

double x, y, z;
const int buttonPin = 8;

float target1 = 90, current1 = 90;
float target2 = 90, current2 = 90;
float target4 = 90, current4 = 90;
float smoothing = 0.05;

unsigned long lastStepTime = 0;
const int stepDelay = 20;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  servo_1.attach(4); // Forward/Backward
  servo_2.attach(3); // Up/Down
  servo_3.attach(2); // Gripper
  servo_4.attach(5); // Left/Right

  servo_1.write(current1);
  servo_2.write(current2);
  servo_4.write(current4);
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  updateMPU();

  if (digitalRead(buttonPin) == LOW) {
  servo_3.write(0); // Gripper closed when button pressed
} else {
  servo_3.write(180); // Gripper open otherwise
}


  // Forward/Backward (Z)
  if (z >= 0 && z <= 60)
    target1 = map(z, 0, 60, 0, 90);
  else if (z >= 300 && z <= 360)
    target1 = map(z, 360, 250, 0, 180);

  // Up/Down (Y)
  if (y >= 0 && y <= 60)
    target2 = map(y, 0, 60, 0, 180);
  else if (y >= 300 && y <= 360)
    target2 = map(y, 360, 300, 180, 0);

  // Left/Right (X)
  if (x >= 0 && x <= 60)
    target4 = map(x, 0, 60, 90, 180);
  else if (x >= 300 && x <= 360)
    target4 = map(x, 360, 300, 90, 0);

  // Smooth transition
  if (millis() - lastStepTime >= stepDelay) {
    moveSmooth(servo_1, current1, target1);
    moveSmooth(servo_2, current2, target2);
    moveSmooth(servo_4, current4, target4);
    lastStepTime = millis();
  }
}

void updateMPU() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);

  axis_X = Wire.read() << 8 | Wire.read();
  axis_Y = Wire.read() << 8 | Wire.read();
  axis_Z = Wire.read() << 8 | Wire.read();

  int xAng = map(axis_X, minVal, maxVal, -90, 90);
  int yAng = map(axis_Y, minVal, maxVal, -90, 90);
  int zAng = map(axis_Z, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
}

void moveSmooth(Servo &servo, float &current, float target) {
  float step = 1.0; // degrees per update
  if (abs(current - target) < step) {
    current = target;
  } else {
    current += (target > current) ? step : -step;
  }
  servo.write((int)current);
}