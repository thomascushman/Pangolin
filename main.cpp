#include "Menu.hpp"
#include "AudioManager.hpp"
#include <stdio.h>

AudioManager manager;

int main(void)
{
  manager.open(Pa_GetDefaultOutputDevice());
  Menu menu;
  while(menu.Update());
  return 0;
}
