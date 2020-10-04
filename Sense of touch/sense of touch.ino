#include <Adafruit_CircuitPlayground.h>

int vals[8] = {3,2,0,1,6,9,10,12};
float pitches [8] = {261.626, 293.665, 329.628, 349.228, 391.995, 440.0, 493.883, 523.251};




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  CircuitPlayground.speaker.enable(false);


 // CircuitPlayground.playTone(200 + c * 100, 2000, false);

  
  for (int i=0; i<7; i++){
     int x = CircuitPlayground.readCap(vals[i]);
     if (x > 600){
      CircuitPlayground.speaker.enable(true);
      CircuitPlayground.playTone(pitches[i],100);
     }
  }
  

  //CircuitPlayground.playTone(500,500,false);

  delay(100);

 
}
