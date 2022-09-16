
#include <IRremote.h>    
int Buzz= 6; 
int LED_RED = 8;
int LED_GREEN = 9; 
int LED_BLUE = 2; 
int PIR= 3;
int val= 0;    
int RECV_PIN = 7; 
boolean TRACK_PIR=1;


IRrecv irrecv(RECV_PIN);
decode_results results;     

// Fonction yaku tiya timing ya sensor, 
void calibration(int time){
  for(int a=10;a>=0;a--){
      digitalWrite(LED_BLUE,HIGH);
      delay(a*time);
      digitalWrite(LED_BLUE,LOW);
      delay(a*time);
  }
}

void setup() {
  
pinMode(Buzz, OUTPUT);
pinMode(LED_RED, OUTPUT);
pinMode(LED_GREEN, OUTPUT);
pinMode(LED_BLUE, OUTPUT);
irrecv.enableIRIn();
pinMode(PIR, INPUT);
Serial.begin(9600);



// Sa unawasha system, ifanye calibrage 
calibration(100);


}

void loop() {

if (irrecv.decode())
{      
  Serial.println(irrecv.decodedIRData.decodedRawData,HEX);
    if(irrecv.decodedIRData.decodedRawData==0xB847FF00){
       digitalWrite(Buzz, LOW);
      }
  if(irrecv.decodedIRData.decodedRawData==0xB748FF00){
    // Washa na kuzimisha detection ya alarm
   if(TRACK_PIR==0) {
    // Sa uli zimisha system, fanya calibrage tena
    calibration(100);
    TRACK_PIR=1;
  }else{
    TRACK_PIR=0;
    digitalWrite(Buzz, LOW);
    }
    }
 irrecv.resume();
}   

if(TRACK_PIR){
    digitalWrite(LED_RED,HIGH);
    digitalWrite(LED_GREEN,LOW);
    val = digitalRead(PIR); 
    if(val == HIGH){
        digitalWrite(Buzz,HIGH);
        Serial.println("Movement Detected"); // Print this text in Serial Monitor
    }
    else 
    {
        Serial.println("Movement not Detected");
    }
}else{
      digitalWrite(LED_GREEN,HIGH);
      digitalWrite(LED_RED,LOW);
}
    delay(200);
}
