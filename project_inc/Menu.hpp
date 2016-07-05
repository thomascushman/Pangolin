#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>

class Oscillator;

class Menu
{
  public:
    Menu();
    ~Menu();
    void Print_Menu() const;
    bool Update(Oscillator& osc);
    
  private:
    enum CHOICES
    {
      PLAY,
      STOP,
      EXIT,
      NUM_CHOICES
    };
  
    int width_ = 0;
    int height_ = 0;
    
    int max_x_ = 0;
    int max_y_ = 0;
    
    int start_x_ = 0;
    int start_y_ = 0;
    
    const char *choices_[NUM_CHOICES] = 
    { 
      "Play",
      "Stop",
      "Exit",
    };
       
    int n_choices_ = NUM_CHOICES;
    int highlight_ = 1;
    int choice_ = 0;
    
    WINDOW *window_ = nullptr;
};

#endif
