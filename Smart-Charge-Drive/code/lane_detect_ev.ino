#include <LiquidCrystal_I2C.h>

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Motor Configuration
#define MOTOR_RIGHT_POS 10
#define MOTOR_RIGHT_NEG 9
#define MOTOR_LEFT_POS 6
#define MOTOR_LEFT_NEG 5

// Sensors
#define IR_LEFT A1
#define IR_RIGHT A0
#define VOLTAGE_SENSOR A2

// Speed Control
#define SPEED_FORWARD 50
#define SPEED_TURN 50

void setup() {
  // Motor Pins
  pinMode(MOTOR_RIGHT_POS, OUTPUT);
  pinMode(MOTOR_RIGHT_NEG, OUTPUT);
  pinMode(MOTOR_LEFT_POS, OUTPUT);
  pinMode(MOTOR_LEFT_NEG, OUTPUT);

  // Sensor Pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(VOLTAGE_SENSOR, INPUT);

  // LCD Startup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" SMART EV DRIVE ");
  delay(1500);
  lcd.clear();
}

void loop() {

  int voltage = analogRead(VOLTAGE_SENSOR);

  lcd.setCursor(0,0);
  lcd.print("Voltage:");
  lcd.setCursor(9,0);
  lcd.print(voltage);

  // Lane Logic
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

  if(left && right){
    moveForward();
  }
  else if(!left && right){
    turnLeft();
  }
  else if(left && !right){
    turnRight();
  }
  else {
    stopRobot();
  }
}

// ---------------- Functions ---------------- //

void moveForward(){
  analogWrite(MOTOR_RIGHT_POS, 0);
  analogWrite(MOTOR_RIGHT_NEG, SPEED_FORWARD);
  analogWrite(MOTOR_LEFT_POS, SPEED_FORWARD);
  analogWrite(MOTOR_LEFT_NEG, 0);
}

void turnLeft(){
  analogWrite(MOTOR_RIGHT_POS, 0);
  analogWrite(MOTOR_RIGHT_NEG, SPEED_TURN);
  analogWrite(MOTOR_LEFT_POS, 0);
  analogWrite(MOTOR_LEFT_NEG, SPEED_TURN);
}

void turnRight(){
  analogWrite(MOTOR_RIGHT_POS, SPEED_TURN);
  analogWrite(MOTOR_RIGHT_NEG, 0);
  analogWrite(MOTOR_LEFT_POS, SPEED_TURN);
  analogWrite(MOTOR_LEFT_NEG, 0);
}

void stopRobot(){
  analogWrite(MOTOR_RIGHT_POS, 0);
  analogWrite(MOTOR_RIGHT_NEG, 0);
  analogWrite(MOTOR_LEFT_POS, 0);
  analogWrite(MOTOR_LEFT_NEG, 0);
}
