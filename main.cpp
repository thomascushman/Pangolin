//#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
//Menu menu;

char const *filename[7] = { 
                            "Dark Sun Gwyndolin.mid",
                            "Moonlight_Butterfly_Dark_Sun_Gwyndolin_(Dark_Souls).mid",
                            "Dark Souls - Great Grey Wolf Sif.mid",
                            "Gwyn_Lord_of_Cinder_Dark_Souls.mid",
                            "legendary-hero.mid",
                            "chpn-p4.mid",
                            "GangnamStyle.mid",
                          };

int main(void)
{
  if(parser.OpenFile(filename[5]))
  {
    parser.Play();
    while(parser.Update(osc));
  }
  //getchar();
  //while(menu.Update(osc));
  return 0;
}
