/******************************************************************************
 *  SimpleTimer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class SimpleTimer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_UNIT_SIMPLETIMER_H_
#define EV3_UNIT_SIMPLETIMER_H_

#include "Clock.h"

class SimpleTimer {
 public:
  explicit SimpleTimer(const ev3api::Clock& clock);

  void setTime(uint32_t delay);
  void start();
  void stop();
  bool isTimedOut() const;
  bool isStarted() const;

 private:
  const ev3api::Clock& mClock;
  uint32_t mDelayMs;
  uint32_t mStartTime;
  uint32_t mTargetTime;
};

#endif  // EV3_UNIT_SIMPLETIMER_H_
