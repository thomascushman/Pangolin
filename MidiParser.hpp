#ifndef MIDIPARSER_HPP
#define MIDIPARSER_HPP

#include "Timer.hpp"

//forward declarations for midi library
class MidiFile;
class MidiEventList;
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
    long microSecondsPerTick_ = -1;
    int absoluteTicks_ = 0;
    Timer timer;
};



#endif
