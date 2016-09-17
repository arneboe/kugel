#pragma once

//all times in ms
#define WAIT_MS(timeMs, accumulatorMs, timePassedMs) \
  accumulatorMs += timePassedMs; \
  if(accumulatorMs > timeMs) \
  { \
    accumulatorMs = 0; \
  } \
  else \
  { \
    return; \
  }
