# Repository for real-time embedded systems design assignment.

This is repository of complete source code to design and implement real-time embedded systems that utilizes interrupts for task switching. Real-time operation is carried out by task scheduling, multi-tasking and in addition to that, implementing state machine.

This operation is summarized below.

## 1)   Scheduling.

This program synchronizes task of flipping LED state to microcontroller clock. Thus flipping the current state of LEDs is scheduled to a particular delay. This program uses `millis()` function from Arduino library. `millis()` returns current value of time elapsed since microcontroller booted in milliseconds. In the same way, `micros()` return elapsed time in microseconds. `millis()` timer resets after approximately 48 days and `micros()` timer resets after 7 hours.

## 2)   Multitasking.

Since flipping the state of LED is scheduled to synchronized time, microcontroller is free to accomplish other task during this time. Thus we are assigning four more LEDs to flip their state simultaneously. Moreover, we are flashing these five LEDs at different flash rates simultaneously.

While waiting to flip state of five LEDs according to clock signal, microcontroller is free to accomplish other task. We have assigned additional task of receiving data from sensors and printing state on serial port.

Thus, microcontroller is performing multitasking. As a result of this, response of system is very spontaneous without any buffer delays, making this system fast, efficient and real-time.

## 3)   State Machine.

In this sytem, microcontroller is storing last state of LEDs for its next flipping operation. We have variable to store elapsed time and flipping state accordingly, during every iteration of loop. The output, which is flipping the state of LED (either ON or OFF) is dependent only on the state, and the next state is dependent on the current state (or output), and the input. Hence concept of Finite State machine or particularly speaking, concept of Moore Finite State machine is implemented successfully.

### Mealy Finite State Machine:


		_________________________
		|			|
		|	|\		|
		|------>| \		|
			|  \		|
			|   \___________|------>  Output (Present State)
			|   /
	Input	------->|  /
			| /
			|/


### Moore Finite State Machine

			|\
			| \
			|  \
	Input --------->|   \____________ Output (Present State)
			|   /
			|  /
			| /
			|/
	





# Files in repo::

- Assignment 1 Problem Statement.pdf
- Assignment 2 Problem Statement.pdf
- ECE5620_Assignment_1.ino
- ECE5620_Assignment_2.ino
- README.md

## Assignment 1 Problem Statement.pdf

This file is problem statement for first task.

## Assignment 2 Problem Statement.pdf

This file is problem statement for second task.

## ECE5620_Assignment_1.ino

Complete arduino sketch solution for first task. This sketch contains functions to receive state of pushbutton inputs, flipping LED state at various frequency and various sequences. Task scheduling, multitasking and State Machine is implemented in this sketch.

## ECE5620_Assignment_2.ino

Complete arduino sketch for second task. This sketch contains all the functionalities of sketch `ECE5620_Assignment_1.ino`. In addition to that, this code has functions to receive analog data from sensor and printing state of LEDs.

## README.md

The summary of repo.
