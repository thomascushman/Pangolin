#ifndef NOTE_HPP
#define NOTE_HPP

namespace Pitch
{
  const int C[9]       = { 12, 24, 36, 48, 60, 72, 84, 96,  108 };
  const int C_Sharp[9] = { 13, 25, 37, 49, 61, 73, 85, 97,  109 };
  const int D[9]       = { 14, 26, 38, 50, 62, 74, 86, 98,  110 };
  const int D_Sharp[9] = { 15, 27, 39, 51, 63, 75, 87, 99,  111 };
  const int E[9]       = { 16, 28, 40, 52, 64, 76, 88, 101, 120 };
  const int F[9]       = { 17, 29, 41, 53, 65, 77, 89, 101, 131 };
  const int F_Sharp[9] = { 18, 30, 42, 54, 66, 78, 90, 101, 142 };
  const int G[9]       = { 19, 31, 43, 55, 67, 79, 91, 101, 153 };
  const int G_Sharp[9] = { 20, 32, 44, 56, 68, 80, 92, 101, 164 };
  const int A[9]       = { 21, 33, 45, 57, 69, 81, 93, 101, 175 };
  const int A_Sharp[9] = { 22, 34, 46, 58, 70, 82, 94, 101, 186 };
  const int B[9]       = { 23, 35, 47, 59, 71, 83, 95, 101, 197 };
};
using namespace Pitch;

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
