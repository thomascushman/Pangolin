#include "Menu.hpp"
#include "Oscillator.hpp"
#include "MidiParser.hpp"
#include "Timer.hpp"
#include <stdio.h>

MidiParser parser;
Oscillator osc;
//Menu menu;
Timer timer;

int main(void)
{
  //if(parser.OpenFile("Dark Souls - Great Grey Wolf Sif.mid"))
  //{
  //  parser.Play();
  //  parser.Update();
  //}
  //else
  //{
  //  printf("NO\n");
  //}
  timer.Start();
  for(double i = 1; i < 3; i += 1)
  {
    while(!timer.IsItThatTime(i));
  }
  osc.PlayNote(60);
  getchar();
  //while(menu.Update(osc));
  return 0;
}
