# Notes on **washer timer**

## Overview
The washer timer is part of a dishwasher timer project using an esp32-C3 supermini. It controls a segment display and handles various wash cycles and delay timers.

## Current Functionality
- **Pin Definitions**: Defines pins for different wash cycles, start button, and delay timers.
- **Timer Variables**: Manages selected time, timer state, and display intervals.
- **Display Setup**: Initializes and controls a TM1637 segment display.
- **Button Detection**: Detects which wash cycle or delay timer button is pressed.
- **Timer Management**: Starts, updates, and checks the status of the timer.
- **Display Updates**: Shows remaining time and flashes "done" when the cycle is complete.



## To-Do *(software)*
#### ! Remember to mark [x] when done !
1. [ ] **Fix Timer Detection**: Correct the logic for detecting multiple timer buttons pressed simultaneously.
2. [ ] **Enhance Display**: Improve the display logic to handle edge cases and ensure accurate time representation.
3. [ ] **Code Optimization**: Refactor redundant code and improve readability.
4. [ ] **Error Handling**: Add error handling for invalid states or button presses.
5. [ ] **Testing**: Thoroughly test all functionalities to ensure reliability.

## To-Do *(hardware)*
#### ! Remember to mark [x] when done !
1. [ ] **Check washing machine pinouts**: Measure how the washing machine buttons are working and how they are connected etc.
2. [ ] **check where controller gets it's power**
3. [ ] **Build the test setup ready**


## Potential Improvements
- **User Feedback**: Add auditory or visual feedback for button presses.
- **MQTT implementation**: Implement MQTT to send remaining time to home assistant etc.
