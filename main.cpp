#include "Menu.hpp"
#include "Oscillator.hpp"
#include <stdio.h>

Oscillator manager;

int main(void)
{
  manager.open(Pa_GetDefaultOutputDevice());
  Menu menu;
  while(menu.Update());
  return 0;
}
