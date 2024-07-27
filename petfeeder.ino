#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <Servo.h> // servo library
int pos=0;
int r=2;
String sign;
unsigned long previousMillis = 0UL;
unsigned long interval = 4000UL;

Servo myservo; // servo name

void setup()
{
  myservo.attach(9); // attach servo signal wire to pin 9
  //Setup usb serial connection to computer
  Serial.begin(9600);
  //Setup Bluetooth serial connection to android
}

void loop()
{
  unsigned long currentMillis = millis();
  //Read from bluetooth and write to usb serial
  while(Serial.available()) // receive number from bluetooth
  {
    delay(10);
    char c=Serial.read();
    sign +=c;
  }
  if(currentMillis - previousMillis >= interval){
      if(r==1)
      {
        for (pos = 190; pos >= 90; pos -= 1) { // goes from 90 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);                       // waits 1 ms for the servo to reach the position
        }
      r=2;
      }
  }
  if(sign.length()>0)
  {
    Serial.println(sign);
    if(sign=="1")
    {  
      if(r==2){
      for (pos = 90; pos <= 190; pos += 1) 
      { // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1); // waits 1 ms for the servo to reach the position
      }
      r=1;
      previousMillis = currentMillis;
    }
    }
    if(sign == "2")
    {
      if(r==1){
      for (pos = 190; pos >= 90; pos -= 1) 
      { // goes from 90 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);                       // waits 1 ms for the servo to reach the position
      }
      r=2;
    }
    }
    sign="";
  }
}
