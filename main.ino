#include <Control_Surface.h>  // Include the library
 
USBMIDI_Interface midi;  // Instantiate a MIDI Interface to use
 
// Instantiate an analog multiplexer
CD74HC4067 muxDigital {
  4,       // Digital input pin
  {0, 1, 2, 3 } // Address pins S0, S1, S2, S3
};

CD74HC4067 muxDigital1 {
  5,       // Digital input pin
  {0, 1, 2, 3 } // Address pins S0, S1, S2, S3
};

CD74HC4067 muxAnalog {
  A5,       // Analog input pin
  {12, 13, 14, 15} // Address pins S0, S1, S2, S3
};

CD74HC4067 muxAnalog2 {
  A4,       // Analog input pin
  {12, 13, 14, 15} // Address pins S0, S1, S2, S3
};

//pin available 6,7,8,9,10,11 , 6,7,8,9 will be use for rotary . 10,11 will be used by sensor
//analog available A1,A2,A3


// Note Release
BEGIN_CS_NAMESPACE

class MyNoteButton : public MIDIOutputElement {
 public:

  MyNoteButton(pin_t pin, MIDIAddress address, uint8_t velocity)
    : button(pin), address(address), velocity(velocity) {}

 public:
  // Initialize: enable the pull-up resistor for the button
  // This method is called once by `Control_Surface.begin()`.
  void begin() final override { button.begin(); }

  // Update: read the button and send MIDI messages when appropriate.
  // This method is called continuously by `Control_Surface.loop()`.
  void update() final override {
    AH::Button::State state = button.update();        // Read the button
    if (state == AH::Button::Falling) {               // if pressed
      Control_Surface.sendNoteOff(address, velocity);  //   → note on
    } else if (state == AH::Button::Rising) {         // if released
      Control_Surface.sendNoteOn(address, velocity); //   → note off
    }
  }
      private:
        AH::Button button;
        const MIDIAddress address;
        uint8_t velocity;
};

END_CS_NAMESPACE

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //

// Transposer that transposes one octave (12 semitones) at a time,
// from 0 to +1 octave.
// Transposer<0, +1> transposer(12);
 
// // Push button on pin 2 to transpose.
// IncrementSelector<2> selector {transposer, 2};
 
// Bankable::NoteButton notebutton {
// //   transposer,       // bank/transposer
// //   3,                // pin
// //   MIDI_Notes::C(4), // address/note
// // };

MyNoteButton button1[] {
  { muxDigital.pin(0),{MIDI_Notes::C(4), Channel_1},0x7F }, 
  { muxDigital.pin(1),{MIDI_Notes::D(4), Channel_1},0x7F },
  { muxDigital.pin(2),{MIDI_Notes::E(4), Channel_1},0x7F },
  { muxDigital.pin(3),{MIDI_Notes::F_(4), Channel_1},0x7F },
  { muxDigital.pin(4),{MIDI_Notes::G(4), Channel_1},0x7F },
  { muxDigital.pin(5),{MIDI_Notes::A(4), Channel_1},0x7F },
  { muxDigital.pin(6),{MIDI_Notes::B(4), Channel_1},0x7F },
  { muxDigital.pin(7),{MIDI_Notes::C(5), Channel_1},0x7F },
  { muxDigital.pin(8),{MIDI_Notes::D(5), Channel_1},0x7F },
  { muxDigital.pin(9),{MIDI_Notes::E(5), Channel_1},0x7F },
  { muxDigital.pin(8),{MIDI_CC::Portamento, Channel_1},0x7F },
  { muxDigital.pin(9),{MIDI_CC::Portamento_Control, Channel_1},0x7F },
  { muxDigital.pin(10),{MIDI_CC::Effects_1, Channel_1},0x7F },
  { muxDigital.pin(11),{MIDI_CC::Effects_2, Channel_1},0x7F },
  { muxDigital.pin(12),{MIDI_CC::Effects_3, Channel_1},0x7F },
  { muxDigital.pin(13),{MIDI_CC::Effects_4, Channel_1},0x7F },
  { muxDigital.pin(14),{MIDI_CC::Effects_5, Channel_1},0x7F },
  { muxDigital.pin(15),{MIDI_CC::Breath_Controller, Channel_1},0x7F },
};

MyNoteButton button2[] {
  { muxDigital1.pin(0),{MIDI_Notes::C(4), Channel_1},0x7F }, 
  { muxDigital1.pin(1),{MIDI_Notes::D(4), Channel_1},0x7F },
  { muxDigital1.pin(2),{MIDI_Notes::E(4), Channel_1},0x7F },
  { muxDigital1.pin(3),{MIDI_Notes::F_(4), Channel_1},0x7F },
  { muxDigital1.pin(4),{MIDI_Notes::G(4), Channel_1},0x7F },
  { muxDigital1.pin(5),{MIDI_Notes::A(4), Channel_1},0x7F },
  { muxDigital1.pin(6),{MIDI_Notes::B(4), Channel_1},0x7F },
  { muxDigital1.pin(7),{MIDI_Notes::C(5), Channel_1},0x7F },
  { muxDigital1.pin(8),{MIDI_Notes::D(5), Channel_1},0x7F },
  { muxDigital1.pin(9),{MIDI_Notes::E(5), Channel_1},0x7F },
  { muxDigital1.pin(8),{MIDI_CC::Portamento, Channel_1},0x7F },
  { muxDigital1.pin(9),{MIDI_CC::Portamento_Control, Channel_1},0x7F },
  { muxDigital1.pin(10),{MIDI_CC::Effects_1, Channel_1},0x7F },
  { muxDigital1.pin(11),{MIDI_CC::Effects_2, Channel_1},0x7F },
  { muxDigital1.pin(12),{MIDI_CC::Effects_3, Channel_1},0x7F },
  { muxDigital1.pin(13),{MIDI_CC::Effects_4, Channel_1},0x7F },
  { muxDigital1.pin(14),{MIDI_CC::Effects_5, Channel_1},0x7F },
  { muxDigital1.pin(15),{MIDI_CC::Breath_Controller, Channel_1},0x7F },
};

// Create an array of CCPotentiometer objects that send out MIDI Control Change 
// messages when you turn the potentiometers connected to the 8 inputs of the mux.
CCPotentiometer Analog1[] {
  { muxAnalog.pin(0), { MIDI_CC::Channel_Volume, Channel_1 } },
  { muxAnalog.pin(1), { MIDI_CC::Effects_1, Channel_1 } },
  { muxAnalog.pin(2), { MIDI_CC::Effects_2, Channel_2 } },
  { muxAnalog.pin(3), { MIDI_CC::Effects_3, Channel_3 } },
  { muxAnalog.pin(4), { MIDI_CC::Effects_4, Channel_5 } },
  { muxAnalog.pin(5), { MIDI_CC::Effects_5, Channel_6 } },
  { muxAnalog.pin(6), { MIDI_CC::Channel_Volume, Channel_7 } },
  { muxAnalog.pin(7), { MIDI_CC::Channel_Volume, Channel_8 } },
  { muxAnalog.pin(8), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(9), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(10), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(11), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(12), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(13), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(14), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog.pin(15), { MIDI_CC::Effects_5, Channel_8 } },
};

CCPotentiometer Analog2[] {
  { muxAnalog2.pin(0), { MIDI_CC::Channel_Volume, Channel_1 } },
  { muxAnalog2.pin(1), { MIDI_CC::Effects_1, Channel_1 } },
  { muxAnalog2.pin(2), { MIDI_CC::Effects_2, Channel_2 } },
  { muxAnalog2.pin(3), { MIDI_CC::Effects_3, Channel_3 } },
  { muxAnalog2.pin(4), { MIDI_CC::Effects_4, Channel_5 } },
  { muxAnalog2.pin(5), { MIDI_CC::Effects_5, Channel_6 } },
  { muxAnalog2.pin(6), { MIDI_CC::Channel_Volume, Channel_7 } },
  { muxAnalog2.pin(7), { MIDI_CC::Channel_Volume, Channel_8 } },
  { muxAnalog2.pin(8), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(9), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(10), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(11), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(12), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(13), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(14), { MIDI_CC::Effects_5, Channel_8 } },
  { muxAnalog2.pin(15), { MIDI_CC::Effects_5, Channel_8 } },
};


// Instantiate a CCAbsoluteEncoder object
CCAbsoluteEncoder enc {
  {6, 7},       // pins
  MIDI_CC::Portamento, // MIDI address (CC number + optional channel)
  5,            // optional multiplier if the control isn't fast enough
};
CCAbsoluteEncoder enc1 {
  {8, 9},       // pins
  MIDI_CC::Expression_Controller, // MIDI address (CC number + optional channel)
  5,            // optional multiplier if the control isn't fast enough
};

//For sensor

//Pitch bend
PBPotentiometer potentiometer {
  A0,        // Analog pin connected to potentiometer
  Channel_1, // MIDI Channel 1
};


// Similarly, for Pitch Bend
//    PBAbsoluteEncoder enc {
//      {2, 3},    // pins
//      Channel_1, // MIDI channel
//      127,       // large multiplier because Pitch Bend has high resolution
//    };
 
void setup() {
  Control_Surface.begin();  // Initialize the Control Surface
}

void loop() {
  Control_Surface.loop();  // Update the Control Surface
}
