// Instructions: open the serial monitor after uploading this code to the synthesizer (leave it plugged in). Click each number, and record the hex code every time. Put these codes in the index.ino file.

#include <IRremote.h>

int RECV_PIN = 22;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
  if(results.value != 0xFFFFFFFF)
   {
    Serial.println(results.value, HEX);
   }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
