/*
 * Project: Control RC Car via Bluetooth with Android Smartphone
 */
 
//L293 Connection   
  const int motorA1  = 5;  // Pin  2 of L293
  const int motorA2  = 6;  // Pin  7 of L293
  const int motorB1  = 10; // Pin 10 of L293
  const int motorB2  = 9;  // Pin 14 of L293
  
//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
  const int BTState = 2;
  unsigned long time0=0,time=-5000;
//Useful Variables
 int prev=' ';
  int state;
  int vSpeed=255;     // Default speed, from 0 to 255

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(BTState, INPUT);    
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {
  
  //Stop car when connection lost or bluetooth disconnected
     if(digitalRead(BTState)==LOW) {
     state=prev;
 }

  //Save income data to variable 'state'
 
    if(Serial.available() > 0){     
      state = Serial.read();   
      
    }
      prev=state;
  //Change speed if state is equal from 0 to 4. Values must be from 0 to 255 (PWM)
    
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=30;}
    else if (state == '2'){
      vSpeed=60;}
    else if (state == '3'){
      vSpeed=80;}
      else if (state == '4'){
      vSpeed=100;}
        else if (state == '5'){
      vSpeed=130;}
        else if (state == '6'){
      vSpeed=150;}
        else if (state == '7'){
      vSpeed=180;}
        else if (state == '8'){
      vSpeed=210;}
        else if (state == '9'){
      vSpeed=230;}
      else if (state == 'q'){
      vSpeed=255;
    }
  
  /* For debugging
  Serial.print("State " );
  Serial.print((char)state);
  
  Serial.print(" >> ");
  
  Serial.println(vSpeed);
  */
     	  
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {
    	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    else if (state == 'G') {
    	analogWrite(motorA1, 0); analogWrite(motorA2, 0);  
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    else if (state == 'I') {
      	analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
    }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    else if (state == 'H') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    else if (state == 'J') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, 0); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
    	analogWrite(motorA1, vSpeed);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 		
    }

  /************************Stop*****************************/
   //Stop the car if no command recieved within 100ms

    else {
    time0=millis();
    if((time0-time)>100){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
   //     Serial.println("Stopped");
        time=time0;
     }
    }
    
}



