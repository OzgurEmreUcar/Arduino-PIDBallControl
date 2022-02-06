#include <Servo.h>
Servo servo;

#define trig 2
#define echo 3

#define kp 20
#define ki 0.050
#define kd 400

double priError = 0;
double toError = 0;
float time; 
int period = 50; 
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(5);
  Serial.begin(9600);
  servo.write(50);
  time = millis();

}
void loop() {
  if (millis()> time + period){
    time = millis();
    
      PID();
    }

  //  int a = distance();
  //  Serial.println(a);
}

long distance () {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  return cm;
}

void PID() {
  
  int dis = distance ();
  

  int setP = 14 ;
  double error = setP - dis;

  double Ivalue;
  double Pvalue = error * kp;
  
  double Dvalue = ((error - priError)/period) * kd;
      if(-3 < error && error < 3)
    {
      Ivalue = toError * ki;;
    }
    else
    {
      Ivalue = 0;
    }
  double PIDvalue = Pvalue + Ivalue + Dvalue;
  priError = error;
  toError += error;
  Serial.println(dis);
  Serial.print(',');
  Serial.println(setP);
  int Fvalue = (int)PIDvalue;


  Fvalue = map(Fvalue, -180, 180, 180, 0);


  if (Fvalue < 0) {
    Fvalue = 0;
  }
  if (Fvalue > 180) {
    Fvalue = 180;
  }

  servo.write(Fvalue);
}
