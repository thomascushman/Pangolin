#include "MidiParser.hpp"
#include "Oscillator.hpp"
#include "inc/MidiFile.h"
#include "inc/MidiEventList.h"

//allocates memory for the midiFile
MidiParser::MidiParser()
  : /*currentEventIndex_(0),*/ hasFile_(false)
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
  bool isRead = midiFile_->read(file) ? true : false;
  if(isRead)
  {
    midiFile_->linkNotePairs();
    midiFile_->doTimeAnalysis();
    midiFile_->absoluteTicks();
    pulsesPerQuarter_ = midiFile_->getTicksPerQuarterNote();
    hasFile_ = true;

    //get starting tempo
    for(int i = 0; i < midiFile_->getEventCount(0); ++i)
    {
      if(midiFile_->getEvent(0, i).isTempo() && microSecondsPerTick_ == -1)
      {
        microSecondsPerTick_ = static_cast<long>(((60000 / (midiFile_->getEvent(0, i).getTempoBPM() * pulsesPerQuarter_))) * 1000);
        break;
      }
    }
  }
  return isRead;
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
      for(int i = 0; i < midiFile_->getEventCount(1); ++i)
      {
        if(midiFile_->getEvent(1, i).tick == absoluteTicks_)
        {
          if(midiFile_->getEvent(1, i).isNoteOn())
          {
            printf("%d\n", midiFile_->getEvent(1, i).getKeyNumber());
            osc.PlayNote(midiFile_->getEvent(1, i).getKeyNumber());
          }
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

