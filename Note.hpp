#ifndef NOTE_HPP
#define NOTE_HPP

#include "ADSR.hpp"

static const int C[9]       = { 12, 24, 36, 48, 60, 72, 84, 96,  108 };
static const int C_Sharp[9] = { 13, 25, 37, 49, 61, 73, 85, 97,  109 };
static const int D[9]       = { 14, 26, 38, 50, 62, 74, 86, 98,  110 };
static const int D_Sharp[9] = { 15, 27, 39, 51, 63, 75, 87, 99,  111 };
static const int E[9]       = { 16, 28, 40, 52, 64, 76, 88, 101, 120 };
static const int F[9]       = { 17, 29, 41, 53, 65, 77, 89, 101, 131 };
static const int F_Sharp[9] = { 18, 30, 42, 54, 66, 78, 90, 101, 142 };
static const int G[9]       = { 19, 31, 43, 55, 67, 79, 91, 101, 153 };
static const int G_Sharp[9] = { 20, 32, 44, 56, 68, 80, 92, 101, 164 };
static const int A[9]       = { 21, 33, 45, 57, 69, 81, 93, 101, 175 };
static const int A_Sharp[9] = { 22, 34, 46, 58, 70, 82, 94, 101, 186 };
static const int B[9]       = { 23, 35, 47, 59, 71, 83, 95, 101, 197 };


class Note
{
  public:
    Note();
    void Init(float *waveform);
    void Play(int noteNum, int velocity, long durationInMicro);
    void Stop();
    float GetSample();
    bool IsPlaying();
    bool IsNote(int noteNum);
    
  private:
    //meta
    bool active_;
    //frequency related
    int noteNum_;
    float phase_;
    float samplingIncrement_;
    float *waveform_;
    //amplitude related
    float velocity_;
    float currentVolume_;
    ADSR adsr_;
};

#endif
