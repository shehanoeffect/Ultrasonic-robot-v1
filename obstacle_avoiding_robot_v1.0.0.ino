// ultrasonic robot firmware v1.0.0

#define rightf 16
#define rightb 17
#define leftb 18
#define leftf 19
#define trig 21
#define echo 20
#define t 500
#define ts 1000 // servo time
#define tt 1000 // turning time
#define tb 1000 // backward time

#include <Servo.h>
Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0; // variable to store the servo position

void goforward()
{
  digitalWrite(rightf, HIGH);
  digitalWrite(leftf, HIGH);
  digitalWrite(rightb, LOW);
  digitalWrite(leftb, LOW);
}
void gobackward()
{

  digitalWrite(rightf, LOW);
  digitalWrite(leftf, LOW);
  digitalWrite(rightb, HIGH);
  digitalWrite(leftb, HIGH);
}
void turnleft()
{
  digitalWrite(rightf, HIGH);
  digitalWrite(leftf, LOW);
  digitalWrite(rightb, LOW);
  digitalWrite(leftb, HIGH);
}
void turnright()
{
  digitalWrite(rightf, LOW);
  digitalWrite(leftf, HIGH);
  digitalWrite(rightb, HIGH);
  digitalWrite(leftb, LOW);
}
void hold()
{
  digitalWrite(rightf, LOW);
  digitalWrite(leftf, LOW);
  digitalWrite(rightb, LOW);
  digitalWrite(leftb, LOW);
}
double lfr[3];
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(9); // attaches the servo on pin 9 to the servo object

  pinMode(rightf, OUTPUT);
  pinMode(rightb, OUTPUT);
  pinMode(leftf, OUTPUT);
  pinMode(leftb, OUTPUT);

  digitalWrite(rightf, LOW);
  digitalWrite(leftf, LOW);
  digitalWrite(rightb, LOW);
  digitalWrite(leftb, LOW);
}

double getdistance()
{ digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  double duration = pulseIn(echo, HIGH);
  // S=UT , DISTANCE(D) = SPEED OF SOUND* (time/2) , D= 3.40cms^-1 * t/2 * 10^-6s

  double D = duration * 0.0343 / 2;
  Serial.println("Distance=");
  Serial.print(D);
  Serial.println("cm");
  return D;
}

void loop()
{
  getdistance();
  goforward();

  if ( getdistance() <= 15)
  {
    hold();


    myservo.write(0);
    delay(ts);
    lfr[0] = getdistance();

    myservo.write(90);
    delay(ts);
    lfr[1] = getdistance();

    myservo.write(180);
    delay(ts);
    lfr[2] = getdistance();
    myservo.write(90);

    Serial.println("abc =");
    Serial.print( lfr[0]);
    Serial.print(",");
    Serial.print(lfr[1]);
    Serial.print(",");
    Serial.print(lfr[2]);
  }

  if (lfr[1] >= 20) {
    goforward();
  }
  else if (lfr[0] < 10 && lfr[1] < 10 && lfr[2] < 10)
  {
    gobackward();
    delay(tb);
  }
  else if (lfr[0] < lfr[2])
  {
    turnleft();
    delay(tt);
  }
  else
  {
    turnright();
    delay(tt);
    goforward();
  }

}
