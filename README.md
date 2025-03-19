# Washer Timer

This project is an esp32-based timer for a dishwasher. It allows the user to select different wash cycles and start a timer for the selected cycle. The remaining time is displayed on a 4-digit 7-segment display.

## Features

- Select different wash cycles: Intensive, Normal, ECO, Glass, Quickwash
- Set delay timers: 2 hours, 4 hours, 8 hours
- Display remaining time on a 4-digit 7-segment display
- Indicate when the wash cycle is finished by displaying "done"

## Hardware Requirements

- esp32-c3 supermini
- TM1637 4-digit 7-segment display

## Hardware for prototyping

- any esp32 board or microcontroller
- 4-digit 7-segment display with TM1637 chip
- Push buttons for selecting wash cycles and delay timers
- Wires and breadboard for connections

## Pin Configuration

- CLK (TM1637 Display): Pin 0
- DIO (TM1637 Display): Pin 1
- Intensive wash button: Pin 2
- Normal wash button: Pin 3
- ECO wash button: Pin 4
- Glass wash button: Pin 5
- Quickwash button: Pin 6
- 2-hour timer button: Pin 7
- 4-hour timer button: Pin 8
- 8-hour timer button: Pin 9
- Start button: Pin 10

## Usage

1. Connect the hardware components as per the pin configuration.
2. Upload the code to the esp32 board.
3. Select the desired wash cycle by pressing the corresponding button.
4. Optionally, set a delay timer by pressing one of the timer buttons.
5. Press the start button to begin the wash cycle.
6. The remaining time will be displayed on the 7-segment display.
7. When the wash cycle is finished, "done" will be displayed.

## Tasks

For detailed tasks and future improvements, refer to [Tasks.md](Tasks.md).

## License

This project is licensed under the MIT License.