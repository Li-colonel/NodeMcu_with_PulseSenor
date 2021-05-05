/*********************
 pulsesenor类

 ********************/

#ifndef _Pulsesensor_H_
#define _Pulsesensor_H_

#include<Arduino.h>
#include <Ticker.h>

class Pulsesensor{
  
private:
Ticker myTicker;
void interruptSetup();
int pulsePin = A0;
int blinkPin = LED_BUILTIN;
//int fadePin = 5;
//int fadeRate = 0;
volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;
volatile int rate[10];
volatile unsigned long sampleCounter = 0;
volatile unsigned long lastBeatTime = 0;
volatile int P = 512;
volatile int T = 512;
volatile int thresh = 512;
volatile int amp = 100;
volatile boolean firstBeat = true;
volatile boolean secondBeat = false;

public:
void begin();
int readBPM();
};


#endif
