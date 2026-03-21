#include <toneAC.h>
#include <Wire.h>
#include <IRremote.hpp>
#include <U8g2lib.h>
#include "pitches.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define cmd0 0x19
#define cmd1 0x45
#define cmd2 0x46
#define cmd3 0x47
#define cmd4 0x44
#define cmd5 0x40
#define cmd6 0x43
#define cmd7 0x07
#define cmd8 0x15
#define up 0x18
#define down 0x52
#define left 0x8
#define right 0x5A
#define ok 0x1C

int note = 0;
int lastMidiNote = -1;
int scaleIndex = 0;
bool midi = false;
int octave = 0;
int majmin = 0;

int activeMIDINotes[8] = {};
int activeSPKRNotes[8] = {};
String activeSCRNNotes[8] = {};
int notesMIDI[24] = { 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };
int notesSPKR[24] = { A4, AS4, B4, C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A5, AS5, B5, C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5 };
String notesSCRN[24] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };
int aMajor = 0;
int asMajor = 1;
int bMajor = 2;
int cMajor = 3;
int csMajor = 4;
int dMajor = 5;
int dsMajor = 6;
int eMajor = 7;
int fMajor = 8;
int fsMajor = 9;
int gMajor = 10;
int gsMajor = 11;
int aMinor = 0;
int asMinor = 1;
int bMinor = 2;
int cMinor = 3;
int csMinor = 4;
int dMinor = 5;
int dsMinor = 6;
int eMinor = 7;
int fMinor = 8;
int fsMinor = 9;
int gMinor = 10;
int gsMinor = 11;
int scaleStarts[24] = { aMajor, asMajor, bMajor, cMajor, csMajor, dMajor, dsMajor, eMajor, fMajor, fsMajor, gMajor, gsMajor, aMinor, asMinor, bMinor, cMinor, csMinor, dMinor, dsMinor, eMinor, fMinor, fsMinor, gMinor, gsMinor };
String scaleNames[24] = { "A Major", "A# Major", "B Major", "C Major", "C# Major", "D Major", "D# Major", "E Major", "F Major", "F# Major", "G Major", "G# Major", "A Minor", "A# Minor", "B Minor", "C Minor", "C# Minor", "D Minor", "D# Minor", "E Minor", "F Minor", "F# Minor", "G Minor", "G# Minor" };

void updateScaleNotes() {
  int start = scaleStarts[scaleIndex];
  bool isMinor = (scaleIndex > 11);
  if (!isMinor) {
    activeSPKRNotes[0] = notesSPKR[start];
    activeSPKRNotes[1] = notesSPKR[start + 2];
    activeSPKRNotes[2] = notesSPKR[start + 4];
    activeSPKRNotes[3] = notesSPKR[start + 5];
    activeSPKRNotes[4] = notesSPKR[start + 7];
    activeSPKRNotes[5] = notesSPKR[start + 9];
    activeSPKRNotes[6] = notesSPKR[start + 11];
    activeSPKRNotes[7] = notesSPKR[start + 12];

    activeMIDINotes[0] = notesMIDI[start];
    activeMIDINotes[1] = notesMIDI[start + 2];
    activeMIDINotes[2] = notesMIDI[start + 4];
    activeMIDINotes[3] = notesMIDI[start + 5];
    activeMIDINotes[4] = notesMIDI[start + 7];
    activeMIDINotes[5] = notesMIDI[start + 9];
    activeMIDINotes[6] = notesMIDI[start + 11];
    activeMIDINotes[7] = notesMIDI[start + 12];

    activeSCRNNotes[0] = notesSCRN[start];
    activeSCRNNotes[1] = notesSCRN[start + 2];
    activeSCRNNotes[2] = notesSCRN[start + 4];
    activeSCRNNotes[3] = notesSCRN[start + 5];
    activeSCRNNotes[4] = notesSCRN[start + 7];
    activeSCRNNotes[5] = notesSCRN[start + 9];
    activeSCRNNotes[6] = notesSCRN[start + 11];
    activeSCRNNotes[7] = notesSCRN[start + 12];
  } else {
    activeSPKRNotes[0] = notesSPKR[start];
    activeSPKRNotes[1] = notesSPKR[start + 2];
    activeSPKRNotes[2] = notesSPKR[start + 3];
    activeSPKRNotes[3] = notesSPKR[start + 5];
    activeSPKRNotes[4] = notesSPKR[start + 7];
    activeSPKRNotes[5] = notesSPKR[start + 8];
    activeSPKRNotes[6] = notesSPKR[start + 10];
    activeSPKRNotes[7] = notesSPKR[start + 12];

    activeMIDINotes[0] = notesMIDI[start];
    activeMIDINotes[1] = notesMIDI[start + 2];
    activeMIDINotes[2] = notesMIDI[start + 3];
    activeMIDINotes[3] = notesMIDI[start + 5];
    activeMIDINotes[4] = notesMIDI[start + 7];
    activeMIDINotes[5] = notesMIDI[start + 8];
    activeMIDINotes[6] = notesMIDI[start + 10];
    activeMIDINotes[7] = notesMIDI[start + 12];

    activeSCRNNotes[0] = notesSCRN[start];
    activeSCRNNotes[1] = notesSCRN[start + 2];
    activeSCRNNotes[2] = notesSCRN[start + 3];
    activeSCRNNotes[3] = notesSCRN[start + 5];
    activeSCRNNotes[4] = notesSCRN[start + 7];
    activeSCRNNotes[5] = notesSCRN[start + 8];
    activeSCRNNotes[6] = notesSCRN[start + 10];
    activeSCRNNotes[7] = notesSCRN[start + 12];
  }
}

void drawDisplay() {
  // scale font: u8g2_font_6x12_tf
  // note font: u8g2_font_spleen32x64_mf
  String noteText = activeSCRNNotes[note - 1];
  if ((note) == 0) noteText = "-";

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_spleen32x64_mf);
  int noteWidth = u8g2.getStrWidth(noteText.c_str());
  u8g2.drawStr((128 - noteWidth) / 2, 45, noteText.c_str());
  u8g2.setFont(u8g2_font_6x12_tf);
  int scaleWidth = u8g2.getStrWidth(scaleNames[scaleIndex].c_str());
  u8g2.drawStr((128 - scaleWidth) / 2, 62, scaleNames[scaleIndex].c_str());
  if (midi == true) {
    u8g2.drawStr(1, 9, "MIDI");
  };
  u8g2.sendBuffer();
}

void setup() {
  Wire.begin();
  IrReceiver.begin(22, ENABLE_LED_FEEDBACK);

  u8g2.begin();
  u8g2.clearBuffer();

  drawDisplay();

  Serial.begin(115200);

  updateScaleNotes();
}

void loop() {
  if (IrReceiver.decode()) {
    uint8_t cmd = IrReceiver.decodedIRData.command;
    switch (cmd) {
      case cmd0: note = 0; break;
      case cmd1: note = 1; break;
      case cmd2: note = 2; break;
      case cmd3: note = 3; break;
      case cmd4: note = 4; break;
      case cmd5: note = 5; break;
      case cmd6: note = 6; break;
      case cmd7: note = 7; break;
      case cmd8: note = 8; break;
      case right:
        scaleIndex = (scaleIndex + 1) % 24;
        majmin = (scaleIndex > 11) ? 1 : 0;
        updateScaleNotes();
        break;

      case left:
        scaleIndex = (scaleIndex + 23) % 24;
        majmin = (scaleIndex > 11) ? 1 : 0;
        updateScaleNotes();
        break;
      case up:
        octave = octave + 1;
        if (octave > 4) octave = 4;
        break;
      case down:
        octave = octave - 1;
        if (octave < -4) octave = -4;
        break;
      case ok: 
        midi = !midi;
        break;
    };
    if (midi == false) {
      if (note == 0) toneAC();
      else {
        toneAC(activeSPKRNotes[note - 1]);
      }
    } else if (midi == true) {
      int currentMidiNote = -1;
      if (note != 0) {
        currentMidiNote = activeMIDINotes[note - 1] + (12 * octave);
      };
      if (lastMidiNote != -1) {
        Serial.write(0x80);
        Serial.write(lastMidiNote);
        Serial.write(0);
      };
      if (currentMidiNote != -1) {
        Serial.write(0x90);
        Serial.write(currentMidiNote);
        Serial.write(127);
      };
      lastMidiNote = currentMidiNote;
    };
    drawDisplay();
    IrReceiver.resume();
    delay(50);
  };
};