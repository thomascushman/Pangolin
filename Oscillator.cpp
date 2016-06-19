#include "Oscillator.hpp"
#include <math.h>
#include <stdio.h>

// PUBLIC METHODS

Oscillator::Oscillator()
  : stream_(nullptr)
{
  Pa_Initialize();
  /* initialise sinusoidal wavetable */
  for( int i=0; i < TABLE_SIZE; i++ )
  {
                //amplitude * Math.Sin((2 * Math.PI * n * frequency) / sampleRate)
    sine[i] = (float) (0.1f * sin( 27.50f * ((double)i/(double)SAMPLE_RATE * M_PI * 2.0 )));
  }
  
  for(int i = 0; i < 32; ++i)
  {
    notes[i].init(sine);
    notes[i].play(48 + i);
  }
  
  for(int i = 0; i < 32; i += 2)
  {
    notes[i].stop();
  }
}


//opens the stream for output
bool Oscillator::open(PaDeviceIndex index)
{
  PaStreamParameters outputParameters;
  outputParameters.device = index;
  
  if (outputParameters.device == paNoDevice) 
  {
    return false;
  }

  outputParameters.channelCount = 1;       /* mono output */
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  PaError err = Pa_OpenStream(
    &stream_,
    NULL, /* no input */
    &outputParameters,
    SAMPLE_RATE,
    FRAMES_PER_BUFFER,
    paClipOff,      /* we won't output out of range samples so don't bother clipping them */
    &Oscillator::paCallback,
    this            /* Using 'this' for userData so we can cast to Sine* in paCallback method */
    );

  if (err != paNoError)
  {
    /* Failed to open stream to device !!! */
    return false;
  }

  err = Pa_SetStreamFinishedCallback( stream_, &Oscillator::paStreamFinished );

  if (err != paNoError)
  {
    Pa_CloseStream( stream_ );
    stream_ = 0;

    return false;
  }

  return true;
}

//closes the output stream
bool Oscillator::close()
{
  if (stream_ == 0)
    return false;

  PaError err = Pa_CloseStream( stream_ );
  stream_ = 0;

  return (err == paNoError);
}

bool Oscillator::start()
{
  if (stream_ == 0)
    return false;

  PaError err = Pa_StartStream( stream_ );

  return (err == paNoError);
}

//stops the output stream
bool Oscillator::stop()
{
  if (stream_ == 0)
    return false;

  PaError err = Pa_StopStream( stream_ );

  return (err == paNoError);
}

//PRIVATE METHODS

/* The instance callback, where we have access to every method/variable in object of class Sine */
int Oscillator::paCallbackMethod(const void *inputBuffer, 
                     void *outputBuffer,
                     unsigned long framesPerBuffer,
                     const PaStreamCallbackTimeInfo* timeInfo,
                     PaStreamCallbackFlags statusFlags)
{
  float *out = (float*)outputBuffer;

  (void) timeInfo; /* Prevent unused variable warnings. */
  (void) statusFlags;
  (void) inputBuffer;

  for(unsigned long i = 0; i < framesPerBuffer; i++)
  {
    (*out) = 0;
    for(int i = 0; i < 32; ++i)
    {
      (*out) += notes[i].getSample();
    }
    ++out;
  }
  
  return paContinue;
}

/* This routine will be called by the PortAudio engine when audio is needed.
    ** It may called at interrupt level on some machines so don't do anything
    ** that could mess up the system like calling malloc() or free().
    */
int Oscillator::paCallback(const void *inputBuffer, 
                      void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData)
{
  /* Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since 
      we called Pa_OpenStream with 'this' for userData */
  return ((Oscillator*)userData)->paCallbackMethod(inputBuffer, 
                                                     outputBuffer,
                                                     framesPerBuffer,
                                                     timeInfo,
                                                     statusFlags);
}

void Oscillator::paStreamFinishedMethod()
{
  printf("");
}

/*
  * This routine is called by portaudio when playback is done.
  */
void Oscillator::paStreamFinished(void* userData)
{
  return ((Oscillator*)userData)->paStreamFinishedMethod();
}