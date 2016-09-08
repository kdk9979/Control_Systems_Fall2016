//**********************************************************************
void pulseMicroSM(void)
{
  const boolean IS_VERBOSE = false;  
  enum {PULSE, DONE};
  static byte state = DONE, prevState = DONE;
  static unsigned int runticks; // state transition tick target
  static unsigned int ticks; // running count
  boolean isNewState;
  
  if (isMicroPulse) // debug up comm check
  {
    isMicroPulse = false;
    Serial.println("ping: uC");
  }

  isNewState = (state != prevState);
  prevState = state;
  switch (state)
  {
    //----------------------------------------------
    case PULSE:
       // entry behavior
      if (isNewState)
      {
        if (IS_VERBOSE) Serial.println("PULSE");
        ticks = 0;
        runticks = Y_MAX_TICKS;
        digitalWrite(UC_LED,UC_LED_ON);
        Serial.println("tick");
      }
      
      // state business
      ticks++;
      Serial.println(ticks);

      // exit condition
      //if (ticks >= runticks) state = DWELL;
      
      break;
 
    //----------------------------------------------
    case DONE:
      // entry behavior
      if (isNewState)
      {
        if (IS_VERBOSE) Serial.println("DONE");
        isRedPulse = false;
        digitalWrite(UC_LED,UC_LED_OFF);
      }

      // state business: none
      
      // exit condition
      if (isRedPulse) state = PULSE;  
   
      break;
 
    //----------------------------------------------    
    default: state = DONE;
  
  } // switch (state)
  

} // void pulseMicroSM()
