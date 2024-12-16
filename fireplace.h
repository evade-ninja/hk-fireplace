struct Fireplace : Service::LightBulb{

  int relayPin;                               // store the pin number connected to a relay that turns the Fireplace on/off
  int switchPin;
  SpanCharacteristic *fireplaceState;             // store a reference to the On Characteristic
  
  Fireplace(int relayPin, int switchPin, int longTime, int shortTime, int btnInterval) : Service::LightBulb(){       // constructor() method for Fireplace defined with one parameter.  Note we also call the constructor() method for the LightBulb Service.

    fireplaceState=new Characteristic::On();      // instantiate the On Characteristic and save it as fireplaceState
    this->relayPin=relayPin;                   // save the pin number for the relay
    pinMode(relayPin,OUTPUT);                 // configure the pin as an output using the standard Arduino pinMode function                       
    
    new SpanButton(switchPin, longTime, shortTime, 0, SpanButton::TRIGGER_ON_HIGH); 
    this->switchPin=switchPin;
    this->relayPin=relayPin;

    Serial.print("Configuring Fireplace with relayPin=");
    Serial.print(relayPin);
    Serial.print(" and switchPin=");
    Serial.println(switchPin);

  } // end constructor()
  
  boolean update(){                          // update() method

    digitalWrite(relayPin,fireplaceState->getNewVal());      // use standard Arduino digitalWrite function to change the ledPin to either high or low based on the value requested by HomeKit
   
    return(true);                            // return true to let HomeKit (and the Home App Client) know the update was successful
  
  } // end update()
  
  void button(int pin, int pressType) override {
    LOG1("Found button press on pin: ");            // always a good idea to log messages
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType==SpanButton::LONG?"LONG":(pressType==SpanButton::SINGLE)?"SINGLE":"DOUBLE");
    LOG1("\n");

    int newState;

    if(pin==switchPin){
      if(pressType==SpanButton::SINGLE || pressType==SpanButton::LONG){            // if a SINGLE press of the power button...
        fireplaceState->setVal(1-fireplaceState->getVal());           // ...toggle the value of the power Characteristic
        digitalWrite(relayPin,fireplaceState->getVal());
        LOG1("Toggled!\n");
      } 
    }
  }

};