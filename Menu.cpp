#include "Menu.hpp"
#include "AudioManager.hpp"

extern AudioManager manager;

Menu::Menu()
{
  initscr();   // startup ncurses
  clear();     // clear the screen
  noecho();    // silence user input
  cbreak();    // Line buffering disabled. pass on everything
  curs_set(0); // invisible cursor
  getmaxyx(stdscr, max_y_, max_x_);       // get the number of rows and columns
  
  width_ = max_x_ - 4;
  height_ = max_y_ - 2;
  
  start_x_ = (max_x_/ 2) - (width_/ 2);   // x coordinate of top right corner
  start_y_ = (max_y_/ 2) - (height_/ 2);  // y coordinate of top right corner
  
  window_ = newwin(height_, width_, start_y_, start_x_); // create new window
  keypad(window_, TRUE); // make sure arrow keys work
  refresh();             // print to monitor 
  Print_Menu();
}

Menu::~Menu()
{
  clrtoeol();      // clear the current line
  refresh();       // print to monitor
  delwin(window_); // free window memory
  endwin();        // end curses mode
}

void Menu::Print_Menu() const
{
  int x = (width_ / 2) - 2, y = 2; //coordinates to print menu options at
  box(window_, 0, 0);              //create a box around the window
  for(int i = 0; i < n_choices_; ++i)
  { 
    if(highlight_ == i + 1) // High light the present choice
    { 
      wattron(window_, A_REVERSE); 
      mvwprintw(window_, y, x, "%s", choices_[i]);
      wattroff(window_, A_REVERSE);
    }
    else
      mvwprintw(window_, y, x, "%s", choices_[i]);
    y += 2;
  }
  wrefresh(window_);
}

bool Menu::Update()
{
  int inputChar = wgetch(window_);
  switch(inputChar)
  { 
    case KEY_UP:
      if(highlight_ == 1)
        highlight_ = n_choices_;
      else
        --highlight_;
      break;
    case KEY_DOWN:
      if(highlight_ == n_choices_)
        highlight_ = 1;
      else 
        ++highlight_;
      break;
    case 10:
      choice_ = highlight_;
      break;
    default:
      refresh();
      break;
  }
  Print_Menu();
  if(choice_ != 0 && inputChar == 10) // User chose something 
  {
    switch(choice_ - 1)
    {
      case PLAY:
        manager.start();
        return 1;
        
      case STOP:
        manager.stop();
        return 1;
        
      case EXIT:
        manager.close();
        return 0;
      default:
        mvprintw(max_y_ - 1, 0, "You chose choice %d with choice string %s\n", choice_, choices_[choice_ - 1]);
        return 0;
    }
  }
  else return 1;
}
