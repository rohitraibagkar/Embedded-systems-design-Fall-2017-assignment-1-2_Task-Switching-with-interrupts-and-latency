# Repository for real-time embedded systems design assignment.

This is repository of complete source code to design and implement real-time embedded systems that utilizes interrupts for task switching. Real-time operation is carried out by task scheduling, multi-tasking and in addition to that, implementing state machine.

This operation is summarized below.

## 1)   Scheduling.

This program synchronizes task of flipping LED state to microcontroller clock. Thus flipping the current state of LEDs is scheduled to a particular delay. This program uses `millis()` function from Arduino library. `millis()` returns current value of time elapsed since microcontroller booted in milliseconds. In the same way, `micros()` return elapsed time in microseconds. `millis()` timer resets after approximately 48 days and `micros()` timer resets after 7 hours.

## 2)   Multitasking.

Since flipping the state of LED is scheduled to synchronized time, microcontroller is free to accomplish other task during this time. Thus we are assigning four more LEDs to flip their state simultaneously. Moreover, we are flashing these five LEDs at different flash rates simultaneously.

While waiting to flip state of five LEDs according to clock signal, microcontroller is free to accomplish other task. We have assigned additional task of receiving data from sensors and printing state on serial port.

## 3)   State Machine.
