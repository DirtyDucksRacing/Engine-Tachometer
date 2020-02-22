//Note that the wheel encoder has 6 pins
//              engine encoder:   5 pins
// Conversion to RPM = Hz (output/printed) * 60 * 1/messageInterval_millis*1/num_magnets=rpm
// Error = +- (60*1/num_magnets * 1/messageInterval_millis) RPM

#define engineEncoderInterruptPin 0
#define messageInterval_millis 500

long enginePulseCount;
long timeToSendMessage;

void engineInterruptFunction(){
  enginePulseCount++;
}

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(engineEncoderInterruptPin, engineInterruptFunction, RISING);
  Serial.begin(115200); // BAUD rate for Serial Communication
  enginePulseCount = 0;
  timeToSendMessage = millis() + messageInterval_millis;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()>timeToSendMessage){
    Serial.println(enginePulseCount*60*1000/messageInterval_millis);
    enginePulseCount = 0;
    timeToSendMessage = millis()+ messageInterval_millis;
  }
  
}
