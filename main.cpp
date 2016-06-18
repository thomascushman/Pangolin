#include "Menu.hpp"
#include "AudioManager.hpp"

int main(void)
{
  AudioManager manager;
  manager.open(Pa_GetDefaultOutputDevice());
  manager.start();
  Menu menu;
  while(menu.Update());
  return 0;
}
