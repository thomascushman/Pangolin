//#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
//Menu menu;


//"chpn-p4.mid"
//"Dark Souls - Great Grey Wolf Sif.mid"
//"Dark Sun Gwyndolin.mid"
//"Gwyn_Lord_of_Cinder_Dark_Souls.mid"
//"Moonlight_Butterfly_Dark_Sun_Gwyndolin_(Dark_Souls).mid"
//"legendary-hero.mid"
//"GangnamStyle.mid"

#define filename "Gwyn_Lord_of_Cinder_Dark_Souls.mid"

int main(void)
{
  //osc.PlayNote(C[4]);
  if(parser.OpenFile(filename))
  {
    parser.Play();
    while(parser.Update(osc));
  }
  //getchar();
  //while(menu.Update(osc));
  return 0;
}
