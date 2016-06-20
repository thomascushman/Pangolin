#ifndef NOTE_HPP
#define NOTE_HPP

class Note
{
  public:
    Note();
    void Init(float *sine);
    void Play(int noteNum);
    void Stop();
    float GetSample();
    bool IsPlaying();
    
  private:
    int noteNum_;
    bool active_;
    float phase_;
    float samplingIncrement_;
    float *sine_;
};

#endif
