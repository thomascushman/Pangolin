#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include "Debug.hpp"

MidiParser parser;
Oscillator osc;
Debug::Stats stats;

int main(int argc, char* argv[])
{
  if(argc > 2)
  {
    if(static_cast<WAVEFORM>(atoi(argv[1])) < NUM_WAVES)
    {
      osc.ChangeWaveform(static_cast<WAVEFORM>(atoi(argv[1])));
    }
    else
    {
      printf("NUMBER TOO HIGH. IGNORING YOU AND PLAYING SQUARE WAVE\n");
    }
    for(int i = 2; i < argc; ++i)
    {
      if(parser.OpenFile(argv[i]))
      {
        parser.Play();
        while(true)
        {
          if(!parser.Update(osc))
          {
            break;
          }
        }
      }
      else
      {
        printf("INVALID MIDI NAME\n");
      }
    }
  }
  else
  {
    printf("PLEASE INPUT A NUMBER AND A MIDI FILENAME\n");
  }
  return 0;
}
