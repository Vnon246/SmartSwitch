/*  
    SmartSwitch 1.1d by Vnon246
    
    Copyright (C) 2021  Vnon246

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


*/

//Ultrasonic-switch initial setup

#include <NewPing.h>

//Definition of Trigger and Echo pins and setup of maximum reading distance

#define trigger_pin 7
#define echo_pin 6
#define max_distance 200

NewPing sw_us(trigger_pin,echo_pin,max_distance);

//Auxiliar variables

int sw_ldr = 0; //Auxiliar variable to store the ldr-switch pin
int sw_led = 13; //Auxiliar variable to store the status led pin
int sw_out = 0; //Auxiliar variable for the device output signal

//Sensor reading variables

int ldr_val; 
float us_val;

void setup() {
  
  Serial.begin(9600); //Initialization of Serial port for debugging purposes
  
  pinMode(sw_ldr,0); //Seting of sw_ldr and sw_led pins
  pinMode(sw_led,1);

  //Device initial setup

  Serial.println("SmartSwitch V1.1");
  Serial.println("By Vnon246");

  digitalWrite(sw_led,1);
  delay(500);
  digitalWrite(sw_led,0);
  delay(500);
  digitalWrite(sw_led,1);
  delay(500);
  digitalWrite(sw_led,0);

  Serial.println("SYS-OK");

}

void loop() {


  SmartSwitch(); //Call to SmartSwitch function

}


//SmartSwitch function

void SmartSwitch(){

  //Setup of reading variables for LDR and US switches

  ldr_val = analogRead(sw_ldr); 
  us_val = sw_us.ping_cm();

    //Distance readings from LDR and US will be displayed via Serial port
  
    Serial.println("LDR");
    Serial.println(ldr_val);

    Serial.println("US");
    Serial.println(us_val);

  //Output trigger

  if(ldr_val <= 500 && us_val <= 5 ){

    sw_out = 1;
    digitalWrite(sw_led,1);
    
    Serial.println("Switch output ->");
    Serial.print(sw_out);
    
  }else{

    sw_out = 0;
    digitalWrite(sw_led,0);
 
    Serial.println("Switch output ->");
    Serial.println(sw_out);
    
  }

  delay(500);

  
}
