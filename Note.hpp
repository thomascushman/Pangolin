#ifndef NOTE_HPP
#define NOTE_HPP

class Note
{
  public:
    Note();
    void init(float *sine);
    void play(int noteNum);
    void stop();
    float getSample();
    
  private:
    int noteNum_;
    bool active_;
    float phase_;
    float samplingIncrement_;
    float *sine_;
};

#endif
