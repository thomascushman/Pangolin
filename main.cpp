#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
Menu menu;
Timer timer;

int main(void)
{
  if(parser.OpenFile("Dark Souls - Great Grey Wolf Sif.mid"))
  {
    parser.Play();
    while(parser.Update());
  }

  while(menu.Update(osc));
  return 0;
}
