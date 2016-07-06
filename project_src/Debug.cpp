#include "../project_inc/Debug.hpp"
#include <ncurses.h>
#include <cstring>

//static const char *message_type[] = { "NOTE ON", "NOTE OFF", "VOLUME CHANGE", "TEMPO CHANGE", };

enum
{
  RED_BLACK = 1,
  BLUE_BLACK,
  YELLOW_BLACK,
  GREEN_BLACK,
  MAGENTA_BLACK,
};

Debug::Stats::Stats()
{
  initscr();
  curs_set(0);
  start_color();
  init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
  init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
  init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
  init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
  init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
  
  for(int i = 0; i < 32; ++i)
  {
    keyNum_[i] = channel_[i] = velocity_[i] = occupied_[i] = 0;
  }
}

Debug::Stats::~Stats()
{
  endwin();
}

void Debug::Stats::AddToStats(int keyNum, int channel, int velocity)
{
  for(int i = 0; i < 32; ++i)
  {
    if(!occupied_[i])
    {
      keyNum_[i] = keyNum;
      channel_[i] = channel;
      velocity_[i] = velocity;
      occupied_[i] = true;
      break;
    }
  }
}

void Debug::Stats::RemoveFromStats(int keyNum, int channel)
{
  for(int i = 0; i < 32; ++i)
  {
    if(occupied_[i])
    {
      if(keyNum_[i] == keyNum && channel_[i] == channel)
      {
        occupied_[i] = false;
        break;
      }
    }
  }
}

void Debug::Stats::Print_Stats()
{
  for(int i = 0; i < 32; ++i)
  {
    if(!occupied_[i])
      continue;
    
    //print key number
    mvprintw(3, 9, "Key Number: ");
    attron(COLOR_PAIR(RED_BLACK));
    mvprintw(3, 21 + i * 3, "%d", keyNum_[i]);
    attroff(COLOR_PAIR(RED_BLACK));
    clrtoeol();
    printw("\n");
    
    //print channel number
    mvprintw(5, 5, "Channel Number: ");
    attron(COLOR_PAIR(BLUE_BLACK));
    mvprintw(5, 21 + i * 3, "%d", channel_[i]);
    attroff(COLOR_PAIR(BLUE_BLACK));
    clrtoeol();
    printw("\n");
    
    //print velocity
    mvprintw(7, 11, "Velocity: ");
    attron(COLOR_PAIR(YELLOW_BLACK));
    mvprintw(7, 21 + i * 3, "%d", velocity_[i]);
    attroff(COLOR_PAIR(YELLOW_BLACK));
    clrtoeol();
    printw("\n");
  }
  
  refresh();
}
