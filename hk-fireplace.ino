/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

/*
/ HomeKit Fireplace Controller
/ Designed to control a gas fireplace that accepts a simple switch as an input to control on/off.
/ Implemented as a LightBulb since HomeKit doesn't have a service that better represents a fireplace.
/ Input: one momentary switch
/ Output: one relay
/ By Travis Marks
*/

#define RELAY_PIN 35
#define SWITCH_PIN 16

#define BUTTON_SHORT_TIME 100
#define BUTTON_LONG_HOLD_TIME 5000


#include "HomeSpan.h"         // include the HomeSpan library
#include "fireplace.h"

void setup() {     
 
  Serial.begin(115200);       // start the Serial interface
  
  homeSpan.begin(Category::Lighting, "Fireplace", "fplace","NinjaHome");           // initialize HomeSpan

  new SpanAccessory();           // Table Lamp Accessory
  
    new Service::AccessoryInformation();            // HAP requires every Accessory to implement an AccessoryInformation Service  
      new Characteristic::Identify();               // HAP requires the Accessory Information Service to include the Identify Characteristic
        
    new Fireplace(RELAY_PIN, SWITCH_PIN, BUTTON_LONG_HOLD_TIME, BUTTON_SHORT_TIME, 0);                              // instantiate the Fireplace Service (defined below) with relayPin set to 16
  
} // end of setup()

void loop(){

 homeSpan.poll(); 

} // end of loop()
