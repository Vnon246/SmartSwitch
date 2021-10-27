/*  
    SmartSwitch 1.5 by Vnon246
    
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

int sw_led = 13;  //Auxiliar variables to store the status led pin
int sw_bz = 10; //Auxiliar variable to store the status-buzzer pin

int sw_out = 0; //Auxiliar variable for the device output signal
int sw_mode = 0; //Auxiliar variable for the device mode setup
int sldr_mode = 1; //Auxiliar variable to store device SmartLDR-switch mode

//Sensor reading variables

int ldr_val; //Auxiliar variable to store the ldr sensor data
float us_val; //Auxiliar variable to store the US sensor dara


void setup() {
  
  Serial.begin(9600); //Initialization of Serial port for debugging purposes
  
  pinMode(sw_ldr,0); //Seting of sw_ldr and sw_led pins
  pinMode(sw_led,1);

  SmartSwitch_setup(); //Initial setup function

}

void loop() {

  while(sw_mode == 0){

    
  }
  
  SmartSwitch(); //Call to SmartSwitch function
 
}
 
void SmartSwitch(){

  //Setup of reading variables for LDR and US sensors

  ldr_val = analogRead(sw_ldr); 
  us_val = sw_us.ping_cm();

    //Distance readings from LDR and US sensors will be displayed via Serial port
  
    Serial.println("LDR");
    Serial.println(ldr_val);

    Serial.println ("");
    
    Serial.println("US");
    Serial.println(us_val);

    Serial.println("");
    

  //SmartLDR and device mode selector

  switch(sldr_mode){

    //SmartLDR mode 1 (Daytime)
    
    case 1:

      //Output trigger (push-mode)
      
      if (sw_mode == 2){
      
        if (ldr_val <= 500 && us_val <= 5){ 

          //Change and show device output and turn on indicator LED
        
          sw_out = 1; 
          digitalWrite(sw_led,1);
    
          Serial.println("Switch output");
          Serial.println(sw_out);
        
          Serial.println("");
      
        }else{
          
          //Change and show device output and turn off indicator LED
        
          sw_out = 0;
          digitalWrite(sw_led,0);
 
          Serial.println("Switch output");
          Serial.println(sw_out);
        
          Serial.println("");
          
       }
       
     }
     
   //SmartLDR mode 2 (Nightime)
   
   case 2:

     //Output trigger (push-mode)
      
      if (sw_mode == 2){

        if (ldr_val <= 500 && us_val <= 5){ 

          //Change and show device output and turn on indicator LED
        
          sw_out = 1; 
          digitalWrite(sw_led,1);
    
          Serial.println("Switch output");
          Serial.println(sw_out);
        
          Serial.println("");
      
        }else{
          
          //Change and show device output and turn off indicator LED
        
          sw_out = 0;
          digitalWrite(sw_led,0);
 
          Serial.println("Switch output");
          Serial.println(sw_out);
        
          Serial.println("");
    
        } 
        
     }
       
  }

 delay(500);
 
}

//[SYSTEM SETUP FUNCTIONS]


//Initial setup

void SmartSwitch_setup(){

  //Device initialization
  
  Serial.println("SmartSwitch V1.5");
  Serial.println("By Vnon246");
  Serial.println("");

  digitalWrite(sw_led,1);
  delay(500);
  digitalWrite(sw_led,0);
  delay(500);
  digitalWrite(sw_led,1);
  delay(500);
  digitalWrite(sw_led,0);

  Serial.println("SYS-OK");
  Serial.println("");

  delay(1000);

  //Device initial setup
  
  Serial.println("[SMARTSWITCH SETUP]");
  Serial.println("");

  Serial.println("Welcome to SmartSwitch!");
  Serial.println("First of all lets set up the device mode (1 -> switch 2 -> push)");
  Serial.println("");

    while(Serial.available() == 0){

   }

    int input = Serial.parseInt(); //Auxiliar variable to store serial reading data

    //Device mode selector
    
    switch(input){
            
       //Device-switch mode  
          
      case 1:

            Serial.println("[SmartSwitch 1.5 by Vnon246]");
            Serial.println("ERROR:Switch mode is not available for now! Coming soon :)");
            Serial.println("");

            Serial.println("RESET DEVICE TO CONTINUE");

            break;
           
      //Device push mode
      
      case 2:

           sw_mode = input; //Set the indicated mode
           Serial.println("Mode selected -> Push");
           Serial.println("");
         
           delay(1500);
           SmartLDR_setup(); //Call to SmartLDR setup

           break;
           
      //Device reset function
      
      default:
      
            Serial.println("[SmartSwitch 1.5 by Vnon246]");
            Serial.println("ERROR:Mode not available");
            Serial.println("");

            Serial.println("RESET DEVICE TO CONTINUE");
            
    }
      
}

//SmartLDR setup

void SmartLDR_setup(){

  ldr_val = analogRead(sw_ldr); //Store ldr sensor value
  Serial.println("Auto-setting SmartLDR-switch...");
  
  int t; //Auxiliar variable to store counter time

  //Counter (10 seconds)
  
  for (t = 0; t <= 10; t++){
    
    Serial.print(".");
    delay(1000);

  }
    Serial.println("");

  //SmartLDR mode selector

  //Mode 2 (Nightime)
  
  if(ldr_val <= 350){
      
    sldr_mode = 2;
    Serial.println("SmartLDR-Switch mode -> Nightime");
    Serial.println("");

    delay(1500);
    loop();
      
  }
  
  //Mode 1 (Daytime)
  
  else{

    sldr_mode = 1;
    Serial.println("SmartLDR-Switch mode -> Daytime");
    Serial.println("");

    delay(1500);
    loop();
    
 }
  
}
  
