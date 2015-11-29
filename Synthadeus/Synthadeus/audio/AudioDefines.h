////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Definitions for Audio Format                                             //
//   Everett Moser                                                            //
//   11-27-15                                                                 //
//                                                                            //
//   Useful constants to describe the audio format used in the applciation    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

// tuned to C5
#define AUDIO_TUNE_NOTE 60

// the tune note is this frequency
#define AUDIO_TUNE_FREQUENCY 440.f

// sample rate
#define AUDIO_SAMPLE_RATE 44100

// default number of channels
#define AUDIO_CHANNELS 2

// a flag to check wether or not we are using an ASIO device (despite build default)
extern bool isUsingAsio;

// frame size
#define AUDIO_FRAME_SIZE 64

// small 10s buffer
#define AUDIO_BUFFER_SIZE (AUDIO_SAMPLE_RATE * 60)