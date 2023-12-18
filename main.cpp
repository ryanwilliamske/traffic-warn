/*
Devices used:
    - Arduino Kit
    - Red LED 
    - Temperature sensor
    - Piezo (Impact sensor)
*/

#include <LiquidCrystal.h>
int LED = 13;
//Red Light connected to digital pin 13

const int TEMP_PIN = A0;
// Temperature sensor, connected to analog pin 0

// LCD display stuff
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//impact sensor
const int knockSensor = A1;
const int threshold = 100;
int sensorReading = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  lcd.begin(16,2);
  //initializing the light & temperature sensors, and the screen
}

void loop(){
  int temp = analogRead(TEMP_PIN);
  float eV = temp * 4.9;
  float tempInC = (eV - 500)/10;
  //sensorReading = analogRead(knockSensor);
  //This is an extreme test
  sensorReading = 300;
  
  if (tempInC > 80 || sensorReading >= threshold){
 /*
 If the temperature is above 120 degrees C, or the impact is above 100N
 System flags that the car has been involved in an accident.
 
 */
    
  	digitalWrite(LED, HIGH);
  	delay(500);
  	digitalWrite(LED, LOW);
  	delay(500);
    
    Serial.print("Warning: Possible fire!");
    Serial.print("Temperature: ");
  	Serial.print(tempInC);
  	Serial.print(" \n");
    lcd.print("Accident or Fire. Calling for help!");
    delay (2000);
  }
  else {
    lcd.print(tempInC);
    lcd.print(" degrees celsius. Truck OK.");
    //Normal temperature aka no accident
  	Serial.print("Temperature: ");
  	Serial.print(tempInC);
  	Serial.print(" \n");
  	delay(2000);
  }
  
  for (int positionCounter = 1; positionCounter++;){
    lcd.scrollDisplayLeft();
    delay(100);
  }
  delay(100);
}