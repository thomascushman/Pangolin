//#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include "Debug.hpp"

MidiParser parser;
Oscillator osc;
//Menu menu;

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
        while(parser.Update(osc));
      }
      else
      {
        printf("INVALID MIDI NAME\n");
      }
      
      if(i < argc - 1)
      {
        printf("CHANGING SONGS\n\n");
      }
    }
  }
  else
  {
    printf("PLEASE INPUT A NUMBER AND A MIDI FILENAME\n");
  }

  //while(menu.Update(osc));
  return 0;
}
