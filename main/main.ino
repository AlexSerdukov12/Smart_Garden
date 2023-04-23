#include "KY015_Sensor.h"
#include "FanControl.h"
#include "WaterLevelSensor.h"
//// ph 
float calibration_value = 21.34-0.7 ;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
///////
int pH_Value; 
float Voltage;
////

const int LDRInput = A0; //Set Analog Input A0 for LDR.
const int LED = 2;
const int WATER_SENSOR_PIN = A5;

KY015_Sensor ky015Sensor(10);
FanControl fanControl(9, 8, 7, 6);
WaterLevelSensor waterLevelSensor(WATER_SENSOR_PIN);

void setup() {
  Serial.begin(9600);
  fanControl.begin();
  pinMode(LDRInput, INPUT);
  pinMode(LED, OUTPUT);
  waterLevelSensor.begin();
/////////PH??

/////////////////

}

void loop() {
  float temperature = ky015Sensor.getTemperature();
  float humidity = ky015Sensor.getHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (ky015Sensor.isError()) {
    Serial.println("Error: KY015 Sensor not found.");
    fanControl.update(0);
  } else {
    fanControl.update(temperature);
  }

 
/////////////////////WATER SENSOR

  waterLevelSensor.update();
  if (waterLevelSensor.isError()) {
    Serial.println("Error: Water level sensor not working.");
  } else {
    waterLevelSensor.getCurrentLevel();
  }

  /////////////////////////////////


  int value = analogRead(LDRInput); //Reads the Value of LDR(light).
  if (value >= 0 && value <= 1023) {
    Serial.print("LDR value is: ");
    Serial.println(value);
    if (value < 300) {
      digitalWrite(LED, HIGH); //The LED turns ON in Dark.
      Serial.println("Turning on relay LED.");
    } else {
      digitalWrite(LED, LOW); //The LED turns OFF in Light.
      Serial.println("Turning off relay LED.");
    }
  } else {
    Serial.println("Error: LDR sensor not working properly.");
  }

////////////////////////////////PH SENSOR

 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A1);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.5 * volt + calibration_value;

 Serial.print("pH Val: ");
 Serial.println(ph_act);
///////////////////////////////////////////////
  Serial.println("-----------------------------------------------------------");

  delay(2000);
}
