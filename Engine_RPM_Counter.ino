//Note that the wheel encoder has 6 pins
//              engine encoder:   5 pins
// Conversion to RPM = Hz (output/printed) * 60 * 1/messageInterval_millis*1/num_magnets=rpm
// Error = +- (60*1/num_magnets * 1/messageInterval_millis) RPM

#define engineEncoderInterruptPin 0
#define messageInterval_millis 500

long rpm;
long count;
long enginePulseCount;
long timeToSendMessage;
long timer; 

void engineInterruptFunction(){
  rpm+= pow(micros()-timer, -1)*60000000;count++;
  timer = micros();
}

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(engineEncoderInterruptPin, engineInterruptFunction, RISING);
  Serial.begin(115200); // BAUD rate for Serial Communication
  enginePulseCount = 0;
  count = 0; rpm = 0;
  timeToSendMessage = millis() + messageInterval_millis;
  timer = millis(); 
}

void loop() {
  if(millis()>timeToSendMessage){
    Serial.println(rpm/count);
    rpm=0;
    count=0;
    timeToSendMessage = millis()+messageInterval_millis;
  }
}
