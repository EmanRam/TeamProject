#include <Servo.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Servo
Servo servo;

//Ultrasonic
#define trig D0
#define echo D1
long duration;
int distance;

//Motor PINs
#define ENA D3
#define ENB D4

#define IN1 D5
#define IN2 D6
#define IN3 D7
#define IN4 D8

 
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "BnNI5yv02FkJ4hgn8OzkWuVpBr9rCZAI"; //Enter your Blynk application auth token
char ssid[] = ""; //Enter your WIFI name
char pass[] = ""; //Enter your WIFI passowrd

BlynkTimer timer;
WidgetLCD lcd(V5);
 
 
void setup() {
  //motor
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
 
  //ultrasonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //servo
  servo.attach(D2);

  Blynk.begin(auth, ssid, pass);
  
  //setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
 
void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  timer.run();
  smartcar();
}
//servo
BLYNK_WRITE(V6){
  servo.write(param.asInt());
}
void sendSensor(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance= duration*0.034/2;

  Serial.print("Distance = ");
  Serial.println(distance);
  
  lcd.print(0,0, "voidloopRobotic");
  lcd.print(0,1, "Distance = "+ String(distance) + "cm ");
  delay(1000);

  if(distance < 30){
    //scan from 0 to 90 degrees
    servo.write(90);
    }
}
 
void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
