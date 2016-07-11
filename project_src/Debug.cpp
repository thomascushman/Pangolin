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
  filename_ = nullptr;
  tempo_ = 0;
}

Debug::Stats::~Stats()
{
  endwin();
}

void Debug::Stats::AddNoteToStats(int keyNum, int channel, int velocity)
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

void Debug::Stats::RemoveNoteFromStats(int keyNum, int channel)
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

void Debug::Stats::SetTempo(double tempo)
{
  tempo_ = tempo;
}

void Debug::Stats::SetFilename(const char* name)
{
  filename_ = name;
}

void Debug::Stats::Print_Stats()
{
  //print filename
  mvprintw(3, 11, "Filename: ");
  attron(COLOR_PAIR(MAGENTA_BLACK));
  mvprintw(3, 23, "%s", filename_);
  attroff(COLOR_PAIR(MAGENTA_BLACK));
  printw("\n");
  
  //print tempo
  mvprintw(5, 14, "Tempo: ");
  attron(COLOR_PAIR(GREEN_BLACK));
  mvprintw(5, 23, "%3.2f", tempo_);
  attroff(COLOR_PAIR(GREEN_BLACK));
  printw("\n");
  
  for(int i = 0; i < 32; ++i)
  {
    if(!occupied_[i])
      continue;
    
    //print key number
    mvprintw(7, 9, "Key Number: ");
    attron(COLOR_PAIR(RED_BLACK));
    mvprintw(7, 21 + i * 4, "%4d", keyNum_[i]);
    attroff(COLOR_PAIR(RED_BLACK));
    clrtoeol();
    printw("\n");
    
    //print channel number
    mvprintw(9, 5, "Channel Number: ");
    attron(COLOR_PAIR(BLUE_BLACK));
    mvprintw(9, 21 + i * 4, "%4d", channel_[i]);
    attroff(COLOR_PAIR(BLUE_BLACK));
    clrtoeol();
    printw("\n");
    
    //print velocity
    mvprintw(11, 11, "Velocity: ");
    attron(COLOR_PAIR(YELLOW_BLACK));
    mvprintw(11, 21 + i * 4, "%4d", velocity_[i]);
    attroff(COLOR_PAIR(YELLOW_BLACK));
    clrtoeol();
    printw("\n");
  }
  
  refresh();
}
