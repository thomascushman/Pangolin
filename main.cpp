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
  if(argc > 1)
  {
    for(int i = 1; i < argc; ++i)
    {
      if(parser.OpenFile(argv[i]))
      {
        parser.Play();
        while(parser.Update(osc));
      }
      if(i < argc - 1)
      {
        printf("CHANGING SONGS\n\n");
      }
    }
  }
  else
  {
    printf("PLEASE INPUT A MIDI FILENAME\n");
  }

  //while(menu.Update(osc));
  return 0;
}
