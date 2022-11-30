// transmitter.ino

// include libraries: 
#include <RH_ASK.h>
#include <SPI.h>

// Create an instance of the RadioHead ASK handler:
// -> Default pins for the RF modules:
//    Pin 11: Data input from receiver
//    Pin 12: Data output to transmitter
RH_ASK radio;

// Create and initialize three 8-bit variables for our RGB values:
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

void setup() {
    Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  // initialize the RadioHead library:
  radio.init();
}

void loop() {
  // constantly read in the analog values from the potentiometers:
  if(readValuesCheckHasChanged()){
    // if the values have changed (-> function returns true), send the values to the receiving device:
    sendValues();  
/*
     Serial.print(" R: ");  // imprime Mensaje:
     Serial.print(255-r);   // imprime buffer de mensaje     
     Serial.print(" G: ");  // imprime Mensaje:
     Serial.print(255-g);   // imprime buffer de mensaje     
     Serial.print(" B: ");  // imprime Mensaje:
     Serial.println(255-b);   // imprime buffer de mensaje     
*/



delay(100);
  }
}

bool readValuesCheckHasChanged(){
  // read the analog values from the potentiometers and save them into local variables.

  // -> analogRead() provides 10-bit values (0 - 1023) but we only need 8-bit values (0-255), so divide the values by 4:
  uint8_t rr = analogRead(A1);
  uint8_t gg = analogRead(A2);
  uint8_t bb = analogRead(A3);

  // check if any of the read values differs from the previous values:
  if(r != rr || g != gg || b != bb){
    // if yes, assign the latest RGB values to the global color variables and return true:
    r = rr;
    g = gg;
    b = bb;

    Serial.print(" R: ");  // imprime Mensaje:
     Serial.print(r);   // imprime buffer de mensaje     
     Serial.print(" G: ");  // imprime Mensaje:
     Serial.print(g);   // imprime buffer de mensaje     
     Serial.print(" B: ");  // imprime Mensaje:
     Serial.println(b);   // imprime buffer de mensaje    


    return true;
  }
  // if nothing has changed, return false:
  return false;
}

void sendValues(){
  // put the individual 8-bit RGB values into an array:
  uint8_t dataArray[] = {r, g, b};
  // RadioHead requires the pointer to the array as a parameter, so let's obtain the pointer first:
  const uint8_t *data = dataArray;

  // push the pointer to the data as well as the length of the data (= 3 Bytes) to the RadioHead instance:
  radio.send((uint8_t *)data, 3);
  // wait until RadioHead has sent the entire data packet to the receiver:
  radio.waitPacketSent();
}