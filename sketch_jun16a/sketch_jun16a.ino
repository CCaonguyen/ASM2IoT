#include <SoftwareSerial.h>
#include <AFMotor.h>
#define motorType MOTOR12_64KHZ
AF_DCMotor motor1(1, motorType);
AF_DCMotor motor2(2, motorType);
AF_DCMotor motor3(3, motorType);
AF_DCMotor motor4(4, motorType);
#define S2 A3
#define S3 A2
#define S4 A1
#define S5 A0
//Bluetooth value
int btValue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}
void loop() {
  carControl();
}
void carControl()
{
  if (Serial.available() > 0)
  {
    btValue = Serial.read() - '0';
    Serial.println(btValue);
    if (btValue == 1)
    {
      moveForward();
    }
    else if (btValue == 2)
    {
      moveBackward();
    }
    else if (btValue == 3)
    {
      turnLeft();
    }
    else if (btValue == 4)
    {
      turnRight();
    }
    else if (btValue == 5)
    {
      stopMove();
    }
    else if (btValue == 6)
    {
      lineFollowing();
    }
  }
}
void lineFollowing()
{
  int s2Value = digitalRead(S2);
  int s3Value = digitalRead(S3);
  int s4Value = digitalRead(S4);
  if (s2Value == 1 && s3Value == 0 && s4Value == 1)
  {
    moveForward();
  }
  else if (s2Value == 0 && s3Value == 1 && s4Value == 1)
  {
    turnRight();
  }
  else if (s2Value == 1 && s3Value == 1 && s4Value == 0)
  {
    turnLeft();
  }
  else if (s2Value == 0 && s3Value == 0 && s4Value == 0)
  {
    stopMove();
  }
}
//Hàm tiến
void moveForward()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
//Hàm lùi
void moveBackward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
//Hàm rẽ trái
void turnLeft()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
//Hàm rẽ phải
void turnRight()
{
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
void stopMove()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
