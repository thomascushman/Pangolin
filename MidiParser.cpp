#include "MidiParser.hpp"
#include "Oscillator.hpp"
#include "inc/MidiFile.h"
#include "inc/MidiEventList.h"
#include <math.h>

extern Oscillator osc;

//allocates memory for the midiFile
MidiParser::MidiParser()
  : currentEventIndex_(0), hasFile_(false)
{
  midiFile_ = new MidiFile();
  eventList_ = new MidiEventList();
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

        //get tempo
        for(int i = 0; i < midiFile_->getEventCount(0); ++i)
        {
            if(midiFile_->getEvent(0, i).isTempo() && microSecondsPerTick_ == -1)
            {
                microSecondsPerTick_ = 1 + (60000 / (midiFile_->getEvent(0, i).getTempoBPM() * pulsesPerQuarter_));
            }
        }
        //get notes
        for(int i = 0; i < midiFile_->getEventCount(1); ++i)
        {
            if(midiFile_->getEvent(1, i).isNoteOn())
            {
                eventList_->push_back(midiFile_->getEvent(1, i));
            }
        }
    }
    return isRead;
}

void MidiParser::Play(void)
{
    isPlaying_ = true;
}

void MidiParser::Update(void)
{
  if(hasFile_ && isPlaying_)
  {
    ++absoluteTicks_;
    if(absoluteTicks_ >= midiFile_->getTotalTimeInTicks())
    {
      isPlaying_ = false;
      return;
    }
    for(int i = 0; i < midiFile_->getEventCount(1); ++i)
    {
        if(midiFile_->getEvent(1, i).tick == absoluteTicks_)
        {
            printf("HERE\n");
            ++currentEventIndex_;
            //osc.stopAll();
            //int d = static_cast<int>(eventList_->getEvent(currentEventIndex_).getDurationInSeconds() * 1000);
            osc.PlayNote(eventList_->getEvent(currentEventIndex_).getKeyNumber());
            printf("%d", eventList_->getEvent(currentEventIndex_).getKeyNumber());
        }
    }
  }
}

bool MidiParser::HasFile(void)
{
    return hasFile_;
}

bool MidiParser::IsPlaying(void)
{
    return isPlaying_;
}

