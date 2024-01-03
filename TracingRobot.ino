// Constants for IR sensors and motor speed
const int IR_SENSOR_RIGHT = 11;
const int IR_SENSOR_LEFT = 12;
const int MOTOR_SPEED = 180;

// Pins for the right motor
const int ENABLE_RIGHT_MOTOR = 6;
const int RIGHT_MOTOR_PIN1 = 7;
const int RIGHT_MOTOR_PIN2 = 8;

// Pins for the left motor
const int ENABLE_LEFT_MOTOR = 5;
const int LEFT_MOTOR_PIN1 = 9;
const int LEFT_MOTOR_PIN2 = 10;

void setup() {
  // Timer configuration, set up frequency
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // Initialize motor pins
  pinMode(ENABLE_RIGHT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(ENABLE_LEFT_MOTOR, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);

  // Initialize IR sensor pins
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  // Stop motors initially
  rotateMotor(0, 0);
}

void loop() {
  // Read IR sensor values and combine them into a single number
  int sensors = digitalRead(IR_SENSOR_RIGHT) * 2 + digitalRead(IR_SENSOR_LEFT);

  switch (sensors) {
    case 0: // Both sensors detect LOW
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
      break;
    case 1: // Left sensor detects HIGH, Right sensor detects LOW
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
      break;
    case 2: // Right sensor detects HIGH, Left sensor detects LOW
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
      break;
    case 3: // Both sensors detect HIGH
      rotateMotor(0, 0);
      break;
  }
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{

  if (rightMotorSpeed < 0)
  {
    digitalWrite(RIGHT_MOTOR_PIN1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
    digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  }
  else
  {
    digitalWrite(RIGHT_MOTOR_PIN1, LOW);
    digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  }

  // Control left motor
  if (leftMotorSpeed < 0)
  {
    digitalWrite(LEFT_MOTOR_PIN1, LOW);
    digitalWrite(LEFT_MOTOR_PIN2, HIGH);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(LEFT_MOTOR_PIN1, HIGH);
    digitalWrite(LEFT_MOTOR_PIN2, LOW);
  }
  else
  {
    digitalWrite(LEFT_MOTOR_PIN1, LOW);
    digitalWrite(LEFT_MOTOR_PIN2, LOW);
  }

  // Set motor speeds
  analogWrite(ENABLE_RIGHT_MOTOR, abs(rightMotorSpeed));
  analogWrite(ENABLE_LEFT_MOTOR, abs(leftMotorSpeed));
}
