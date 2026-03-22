# ArduinoSynthesizer  
This repository consists of all the software and instructions for the Arduino Synthesizer project.  

# Introduction / Use  
The Synthesizer is controlled with an IR remote.  
- Keys 1-8 | Plays respective note in selected scale
- Key 0 | Turns off current note playing
- Left & Right Arrows | Switches scale
- OK | Toggles MIDI mode
- Up & Down Arrows | Changes octave (MIDI mode only)
- Keys 9, #, and * have no function.

If you want to use the synthesizer as a MIDI controller, you will need three apps: a DAW (I used [FL Studio](https://www.image-line.com)), [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html), and [hairless-MIDIserial](https://projectgus.github.io/hairless-midiserial/). The loopMIDI app will create a MIDI port, while the hairless-midiserial app connects the device to the MIDI port. From there, the DAW will pick up the MIDI signals and play notes. Keep in mind that you will need to connect the device to your laptop with a USB-A to USB-B cable.  

# Hardware Instructions  
**Necessary Components:**  
- Arduino Mega 2560 w/USB-B port
- 128x64 Pixel OLED Display
- 8Ω Arduino Speaker
- IR Receiver
- IR Remote
- Breadboard & 120Ω resistor
- USB-A to USB-B Cable
**Optional Components:**  
- 3D Printer (to print the housing)
- 9v Battery w/DC connector

**Assembly**  
1. Connect the 8Ω speaker's VCC -> 120Ω resistor -> port 12 (digital) on the MEGA, and GND -> GND.
2. Connect the OLED's GND -> GND, VCC -> 5V, SDA -> SDA (20), SCL -> SCL (21).
3. Connect the IR Receiver's GND -> GND, VCC -> 5V, 3rd port -> 22 (digital).
4. Fit everything inside the housing if you 3D printed it (you can find it [here](https://www.printables.com/model/1645729-arduino-synthesizer-case)):
   1. Align the Mega 2560 with the port holes.
   2. Put the breadboard if you used one (for the speaker resistor) on top of the Mega.
   3. Align the speaker next to the Mega with the speaker grills.
   4. Align the OLED on the other side of the Mega with the screen cutout.
   5. Push the IR receiver as far as you can through the cutout on the side opposite the ports (it won't fully stick out, don't worry)
5. Put the lid on. You might have to tape it shut for sometime for it to sit in place.

**Software**  
Included in this repository are two microcontroller files: index.ino and pitches.h. You will need both.  
1. Import these files into the Arduino IDE.
2. Plug in the Synthesizer to your computer with the USB-B port.
3. Upload the index.ino code to your device. Make sure no other app (hairless-midiserial) is using the device's Serial.

**Extras**  
If you would like to 3D print the case, here are the files: https://www.printables.com/model/1645729-arduino-synthesizer-case  
Here is the link to the overview video of the device: 
