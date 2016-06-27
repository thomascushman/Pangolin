#include "MidiParser.hpp"
#include "Oscillator.hpp"
#include "inc/MidiFile.h"
#include "inc/MidiEventList.h"
#include "Debug.hpp"

//allocates memory for the midiFile
MidiParser::MidiParser()
  : hasFile_(false)
{
  midiFile_ = new MidiFile();
}

MidiParser::~MidiParser()
{
  delete midiFile_;
}

//opens the midifile either locally or by absolute path
//returns true or false based on whether it could be opened
bool MidiParser::OpenFile(const char *file)
{
  hasFile_ = midiFile_->read(file) ? true : false;
  if(hasFile_)
  {
    midiFile_->joinTracks();
    midiFile_->absoluteTicks();
    pulsesPerQuarter_ = midiFile_->getTicksPerQuarterNote();

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
          if(currentEvent.isNoteOn())
          {
            Debug::Print_Stats(Debug::NOTE_ON, currentEvent);
            osc.PlayNote(currentEvent.getKeyNumber(), currentEvent.getChannelNibble(), currentEvent[2]);
          }
          else if(currentEvent.isNoteOff())
          {
            Debug::Print_Stats(Debug::NOTE_OFF, currentEvent);
            osc.StopNote(currentEvent.getKeyNumber(), currentEvent.getChannelNibble());
          }
          else if(currentEvent.isTempo())
          {
            Debug::Print_Stats(Debug::TEMPO_CHANGE, currentEvent);
            ChangeTempo(currentEvent.getTempoBPM());
          }
          else if(currentEvent.isController() && (currentEvent[1] & 0xFF) == 7)
          {
            //static int i = 1;
            //printf("VOLUME CHANGE %d\n", i++);
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
