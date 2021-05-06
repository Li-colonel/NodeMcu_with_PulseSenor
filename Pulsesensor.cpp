#include "Pulsesensor.h"


void Pulsesensor::begin()
{
  pinMode(blinkPin, OUTPUT);
  myTicker.attach_ms(12,std::bind(&Pulsesensor::interruptSetup, this));
}
/*
void pulsesensor::sendData()
{
  if (QS == true)
  {
    sendDataToProcessing('B', BPM);
    sendDataToProcessing('Q', IBI);
    //  fadeVal = 255;
    QS = false;
  }
  //ledFadeToBeat();
  delay(20);
}
*/

int Pulsesensor::readBPM()
{
  return BPM;
}
void Pulsesensor::interruptSetup()
{
  Signal = analogRead(pulsePin);
  sampleCounter += 12;
  int N = sampleCounter - lastBeatTime;

  if (Signal < thresh && N > (IBI / 5) * 3)
  {

    if (Signal < T)
    {

      T = Signal;
    }
  }

  if (Signal > thresh && Signal > P)
  {

    P = Signal;
  }

  if (N > 250)
  {
    if ((Signal > thresh) && (Pulse == false) && (N > ((IBI / 5) * 3)))
    {
      Pulse = true;
      digitalWrite(blinkPin, LOW); //nodemcu的LED_BUILTIN为LOW时亮
      IBI = sampleCounter - lastBeatTime;
      lastBeatTime = sampleCounter;
      if (secondBeat)
      {

        secondBeat = false;

        for (int i = 0; i <= 9; i++)
        {

          rate[i] = IBI;
        }
      }

      if (firstBeat)
      {
        firstBeat = false;

        secondBeat = true;
        
        return;
      }

      word runningTotal = 0;
      for (int i = 0; i <= 8; i++)
      {
        rate[i] = rate[i + 1];
        runningTotal += rate[i];
      }
      rate[9] = IBI;
      runningTotal += rate[9];
      runningTotal /= 10;
      BPM = 60000 / runningTotal;
      QS = true;
    }
  }
  if (Signal < thresh && Pulse == true)
  {
    digitalWrite(blinkPin, HIGH);
    Pulse = false;
    amp = P - T;
    thresh = amp / 2 + T;
    P = thresh;
    T = thresh;
  }

  if (N > 2500)
  {
    thresh = 512;
    P = 512;
    T = 512;
    firstBeat = true;
    secondBeat = false;
    lastBeatTime = sampleCounter;
  }
}
