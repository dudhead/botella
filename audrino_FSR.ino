#include <SoftwareSerial.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message

int FSR_Pin = A0; //analog pin 0


void setup(){
 Serial.begin(9600);
}

void loop(){
 // Fetching FSR Analog reading
 int FSRReading = analogRead(FSR_Pin);

 // Mapping it into a voltage
 int voltage = map(FSRReading, 0, 1023, 0, 5000);

 // Calculating Resistance on the FSR
 unsigned long resistance = 5000 - voltage;
 resistance = resistance * 10000;
 resistance = resistance / voltage;

 // Measuring Conductance over the circuit
 unsigned long conductance = 1000000;
 conductance = conductance/resistance;

 // Identifying the force applied on the FSR
 long force;
 force = conductance / 80;

 // Calliberating it into wieght
 double weight = force / 9.8;

 // Send data to bluetooth device
 sendData(weight);
 
 delay(10000); //Delay to emit weight only once every 10 Seconds
}

void sendData(double value) {
  String strValue = String(value);
  String json = String("{\"currentBottleweight\": " + strValue + "}");

  // Start delimiter
  Serial.println("#");
  
  Serial.println(json);
  
  // End delimiter
  Serial.println("~");
}

