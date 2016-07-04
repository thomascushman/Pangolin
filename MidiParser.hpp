#ifndef MIDIPARSER_HPP
#define MIDIPARSER_HPP

#include "Timer.hpp"

//forward declarations for midi library
class MidiFile;
class MidiEvent;
class Oscillator;

class MidiParser
{
  public:
    MidiParser();
    ~MidiParser();
    bool OpenFile(const char* file);
    void Play(void);
    bool Update(Oscillator &osc);
    bool HasFile(void);
    bool IsPlaying(void);
    
  private:
    void ChangeTempo(double bpm);
    MidiFile *midiFile_;
    bool hasFile_;
    bool isPlaying_;
    int pulsesPerQuarter_;
    long microSecondsPerTick_;
    int absoluteTicks_;
    Timer timer;
    
    bool IsNoteOn(const MidiEvent& event);
    bool IsNoteOff(const MidiEvent& event);
    bool IsTempo(const MidiEvent& event);
    bool IsVolume(const MidiEvent& event);
};



#endif
