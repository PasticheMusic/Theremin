 /* 

*/
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
int val= 0;
int val2 = 0;
int val3 = 0;
int val4= 0;
int val5= 0;

//Buttons
int but1 = 0;
int prestate1 = 0;
int count1 = 0;
int but2 = 0;
int count2 = 0;
int prestate2 = 0;
int but3 = 0;
int count3 = 0;
int prestate3 = 0;

int pho1, high1 = 1023, low1 = 0;     //light level photoresistor is measuring
int pho2, high2 = 1023, low2 = 0;



void setup(){
Serial.begin(115200);
}


void loop(){

  
  val = analogRead(3) / 8; // read value of potentiometer 1 BLUE
//Serial.write(60, val, 1); // MIDI control change; channel 1
//Serial.write(val); // MIDI controller value from potentiometer 1
MIDI.sendNoteOn(15,val,1);
delay(10);

val2 = analogRead(2) / 8; //RED knob
MIDI.sendNoteOn(26,val2,2);
delay(10);

val3 = analogRead(7) / 8; //GREEN knob
MIDI.sendNoteOn(35,val3,3);
delay(10);

val4 = analogRead(5) / 8; //YELLOW knob
MIDI.sendNoteOn(8,val4,4);
delay(10);

val5 = analogRead(0) / 8; //PURPLE
MIDI.sendNoteOn(11,val5,5);
delay(10);

pho1 = analogRead(8);
MIDI.sendNoteOn(20,pho1,9);
    delay(10);
pho2 = analogRead(13);
MIDI.sendNoteOn(22,pho2,10);
    delay(10);


but1 = digitalRead(3); //red
 
if (but1 == HIGH) {MIDI.sendNoteOn(17,127,6); prestate1 = 1;}
if (but1 == LOW and prestate1 == 1) {MIDI.sendNoteOn(17,0,6); prestate1 = 0;}
delay(10);

but2 = digitalRead(4);//yellow

if (but2 == HIGH) {MIDI.sendNoteOn(18,127,7); prestate2 = 1;}
if (but2 == LOW and prestate2 == 1) {MIDI.sendNoteOn(18,0,7); prestate2 = 0;}
delay(10);

but3 = digitalRead(5);//green

if (but3 == HIGH) {MIDI.sendNoteOn(19,127,8); prestate3 = 1;}
if (but3 == LOW and prestate3 == 1) {MIDI.sendNoteOn(19,0,8); prestate3 = 0;}
delay(10);

//autoTune();  // have the Arduino do the work for us!
}

 void autoTune() {
  // won't have a range all the way from 0 to 1023. It will likely
  // be more like 300 (dark) to 800 (light).

  // In this function, the Arduino will keep track of the highest
  // and lowest values that we're reading from analogRead().
 // save anything read that's lower than that:
  
  if (pho1 < low1)
  {
    low1 = pho1;
  }
//save anything we read that's higher than 0:
  
  if (pho1 > high1)
  {
    high1 = pho1;
  }
   // save anything read that's lower than that:
   if (pho2 < low2)
  {
    low2 = pho2;
  }
//save anything we read that's higher than 0:
  
  if (pho2 > high2)
  {
    high2 = pho2;
  }
  
  // Once we have the highest and lowest values, we can stick them
  // directly into the map() function. No manual tweaking needed!
  
  // One trick we'll do is to add a small offset to low and high,
  // to ensure that the LED is fully-off and fully-on at the limits
  // (otherwise it might flicker a little bit).
  
  pho1 = map(pho1, low1+30, high1-30, 0, 127);
  pho1 = constrain(pho1, 0, 127);
    
  pho2 = map(pho2, low2+30, high2-30, 0, 127);
  pho2 = constrain(pho2, 0, 127);
   //MIDI.sendNoteOn(20,ch1,6);
    //MIDI.sendNoteOn(22,ch2,7);
    delay(10);
 }
