#ifndef MIDIPARSER_HPP
#define MIDIPARSER_HPP

//forward declarations for midi library
class MidiFile;
class MidiEventList;

class MidiParser
{
  public:
    MidiParser();
    ~MidiParser();
    bool OpenFile(const char* file);
    void Play(void);
    void Update(void);
    bool HasFile(void);
    bool IsPlaying(void);
    
  private:
    MidiFile *midiFile_;
    MidiEventList *eventList_;
    int currentEventIndex_;
    bool hasFile_;
    bool isPlaying_;
    int pulsesPerQuarter_;
    double microSecondsPerTick_ = -1;
    int absoluteTicks_ = 0;
};



#endif
