#include "MidiParser.hpp"
#include "Oscillator.hpp"
#include "MidiFile.h"
#include "Debug.hpp"

//allocates memory for the midiFile
MidiParser::MidiParser()
  : hasFile_(false)
{
  //midiFile_ = new MidiFile();
}

MidiParser::~MidiParser()
{
  delete midiFile_;
}

//opens the midifile either locally or by absolute path
//returns true or false based on whether it could be opened
bool MidiParser::OpenFile(const char *file)
{
  delete midiFile_;
  midiFile_ = new MidiFile();
  absoluteTicks_ = 0;
  microSecondsPerTick_ = -1;
  
  hasFile_ = midiFile_->read(file) ? true : false;
  if(hasFile_)
  {
    pulsesPerQuarter_ = midiFile_->getTicksPerQuarterNote();
    midiFile_->linkNotePairs();
    midiFile_->joinTracks();
    midiFile_->doTimeAnalysis();
    midiFile_->absoluteTicks();

    //get starting tempo
    for(int i = 0; i < midiFile_->getEventCount(0); ++i)
    {
      if(midiFile_->getEvent(0, i).isTempo() && microSecondsPerTick_ == -1)
      {
        ChangeTempo(midiFile_->getEvent(0, i).getTempoBPM());
        break;
      }
    }
  }
  return hasFile_;
}

void MidiParser::Play(void)
{
  isPlaying_ = true;
  timer.Start(microSecondsPerTick_);
}

bool MidiParser::Update(Oscillator &osc)
{
  if(timer.IsActive())
  {
    timer.Update();
  }
  else
  {
    timer.Start(microSecondsPerTick_);
    if(hasFile_ && isPlaying_)
    {
      ++absoluteTicks_;
      if(absoluteTicks_ >= midiFile_->getTotalTimeInTicks())
      {
        isPlaying_ = false;
      }
      for(int i = 0; i < midiFile_->getEventCount(0); ++i)
      {
        MidiEvent currentEvent = midiFile_->getEvent(0, i);
        if(currentEvent.tick == absoluteTicks_)
        {
          if(IsNoteOn(currentEvent))
          {
            Debug::Print_Stats(Debug::NOTE_ON, currentEvent);
            currentEvent.getDurationInSeconds();
            osc.PlayNote(currentEvent.getKeyNumber(), currentEvent.getChannelNibble(), currentEvent[2], static_cast<long>(currentEvent.seconds * 1000000));
          }
          else if(IsNoteOff(currentEvent))
          {
            Debug::Print_Stats(Debug::NOTE_OFF, currentEvent);
            osc.StopNote(currentEvent.getKeyNumber(), currentEvent.getChannelNibble());
          }
          else if(IsTempo(currentEvent))
          {
            Debug::Print_Stats(Debug::TEMPO_CHANGE, currentEvent);
            ChangeTempo(currentEvent.getTempoBPM());
          }
          else if(IsVolume(currentEvent))
          {
            osc.SetVolume(currentEvent[2], currentEvent.getChannelNibble());
          }
        }
        //don't bother searching through messages that haven't happened yet
        else if(currentEvent.tick > absoluteTicks_)
        {
          break;
        }
      }
    }
  }
    
  return isPlaying_;
}

bool MidiParser::HasFile(void)
{
  return hasFile_;
}

bool MidiParser::IsPlaying(void)
{
  return isPlaying_;
}

void MidiParser::ChangeTempo(double bpm)
{
  microSecondsPerTick_ = static_cast<long>(((60000 / (bpm * pulsesPerQuarter_))) * 1000);
}

bool MidiParser::IsNoteOn(const MidiEvent& event)
{
  return ((event[0] & 0xF0) == 0x90) &&
         ((event[2] & 0xFF) != 0x00);
}

bool MidiParser::IsNoteOff(const MidiEvent& event)
{
  return ((event[0] & 0xF0) == 0x80) ||
         (((event[0] & 0xF0) == 0x90) &&
         ((event[2] & 0xFF) == 0x00));
}

bool MidiParser::IsTempo(const MidiEvent& event)
{
  return ((event[0] & 0xFF) == 0xFF) &&
         ((event[1] & 0xFF) == 0x51);
}

bool MidiParser::IsVolume(const MidiEvent& event)
{
  return ((event[0] & 0xF0) == 0xB0) && 
         ((event[1] & 0x0F) == 0x07);
}
