//#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
//Menu menu;

int main(void)
{
  //osc.PlayNote(C[4]);
  if(parser.OpenFile("Dark Souls - Great Grey Wolf Sif.mid"))
  {
    parser.Play();
    while(parser.Update(osc));
  }
  //getchar();
  //while(menu.Update(osc));
  return 0;
}
