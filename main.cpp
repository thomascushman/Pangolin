#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
Menu menu;

int main(void)
{
  if(parser.OpenFile("Dark Souls - Great Grey Wolf Sif.mid"))
  {
    parser.Play();
    parser.Update();
  }
  else
  {
    printf("NO\n");
  }
  while(menu.Update());
  return 0;
}
