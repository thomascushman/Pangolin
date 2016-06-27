//#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"

MidiParser parser;
Oscillator osc;
//Menu menu;

char const *filename[8] = { 
                            "Dark Sun Gwyndolin.mid",
                            "Moonlight_Butterfly_Dark_Sun_Gwyndolin_(Dark_Souls).mid",
                            "smw2_title.mid",
                            "Dark Souls - Great Grey Wolf Sif.mid",
                            "Gwyn_Lord_of_Cinder_Dark_Souls.mid",
                            "legendary-hero.mid",
                            "chpn-p4.mid",
                            "GangnamStyle.mid",
                          };

int main(void)
{
  if(parser.OpenFile(filename[6]))
  {
    parser.Play();
    while(parser.Update(osc));
  }

  //while(menu.Update(osc));
  return 0;
}
