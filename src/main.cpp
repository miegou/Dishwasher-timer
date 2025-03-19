// MIT License (c) 2025 miegou
// See LICENSE file for details.

#include <Arduino.h>
#include <Wire.h>
#include <TM1637Display.h>

#define CLK 0 // Segment display CLK pin
#define DIO 1 // Segment display DIO pin

const int Intensive = 2;    // Intensive wash 140 min
const int Normal = 3;       // Normal wash 120 min
const int ECO = 4;          // ECO wash 180 min
const int Glass = 5;        // Glass wash 75 min
const int Quickwash = 6;    // Quick wash 30 min
const int startButton = 10; // Start button

const int twoHourTimer = 7;   // 2 hour timer
const int fourHourTimer = 8;  // 4 hour timer
const int eightHourTimer = 9; // 8 hour timer

unsigned long selectedTime = 0;   // Chosen time in milliseconds
unsigned long selectedTimer = 0;  // Chosen timer in milliseconds
unsigned long previousMillis = 0; // Previous time in milliseconds
const long interval = 1000;       // Interval in milliseconds
bool colonState = false;          // Colon state

unsigned long startTime = 0;             // When the timer was started
unsigned long remainingMinutes = 0;      // Remaining minutes
unsigned long remainingTimerMinutes = 0; // Remaining timer
bool timerRunning = false;               // Is the timer running

TM1637Display display(CLK, DIO); // Segment display object

// Display "done"
const uint8_t SEG_DONE[] = {
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,         // d
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
    SEG_C | SEG_E | SEG_G,                         // n
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G          // E
};

// Display "t" for timer
const uint8_t SEG_T[] = {
    SEG_D | SEG_E | SEG_F | SEG_G // t
};

// Check if a timer button is pressed
bool timerDetected()
{
  return (digitalRead(twoHourTimer) == LOW ||
          digitalRead(fourHourTimer) == LOW ||
          digitalRead(eightHourTimer) == LOW);
}

// Get the time value of the timer button pressed
unsigned long getDetectedTimerValue()
{
  if (digitalRead(twoHourTimer) == LOW)
  {
    return 2 * 60 * 60 * 1000; // 2 hours in milliseconds
  }
  if (digitalRead(fourHourTimer) == LOW)
  {
    return 4 * 60 * 60 * 1000; // 4 hours in milliseconds
  }
  if (digitalRead(twoHourTimer) == LOW && digitalRead(fourHourTimer) == LOW)
  {
    return 6 * 60 * 60 * 1000; // 6 hours in milliseconds
  }
  if (digitalRead(eightHourTimer) == LOW)
  {
    return 8 * 60 * 60 * 1000; // 8 hours in milliseconds
  }
  return 0; // If no button is pressed
}

// Check which button is pressed
bool inputDetected()
{
  return (digitalRead(Intensive) == LOW ||
          digitalRead(Normal) == LOW ||
          digitalRead(ECO) == LOW ||
          digitalRead(Glass) == LOW ||
          digitalRead(Quickwash) == LOW);
}

// Get the time value of the wash button pressed
unsigned long getTimerValue()
{
  if (digitalRead(Intensive) == LOW)
  {
    return 140 * 60 * 1000; // 140 minutes in milliseconds
  }
  if (digitalRead(Normal) == LOW)
  {
    return 120 * 60 * 1000; // 120 minutes in milliseconds
  }
  if (digitalRead(ECO) == LOW)
  {
    return 180 * 60 * 1000; // 180 minutes in milliseconds
  }
  if (digitalRead(Glass) == LOW)
  {
    return 75 * 60 * 1000; // 75 minutes in milliseconds
  }
  if (digitalRead(Quickwash) == LOW)
  {
    return 1 * 60 * 1000; // 30 minutes in milliseconds, set for 1 minute for testing
  }
  return 0; // If no button is pressed
}

void displayDetectedTimerValue()
{
  remainingTimerMinutes = selectedTimer / 60000;

  int hours = remainingTimerMinutes / 60;
  int minutes = remainingTimerMinutes % 60;

  int displayValue = (hours * 100) + minutes; // Format as HMM (e.g., 1:05 -> 105)
  display.showNumberDecEx(displayValue, 0b01000000, false);
}

// Display the selected time
void displayTimerValue()
{
  remainingMinutes = selectedTime / 60000;

  int hours = remainingMinutes / 60;
  int minutes = remainingMinutes % 60;

  int displayValue = (hours * 100) + minutes; // Format as HMM (e.g., 1:05 -> 105)
  display.showNumberDecEx(displayValue, 0b01000000, false);
}

// Check if the start button is pressed
bool startButtonPressed()
{
  return digitalRead(startButton) == LOW;
}

// Start the timer
void startTimer(unsigned long time)
{
  if (!timerRunning && time > 0)
  {
    startTime = millis();
    selectedTime = time;
    remainingMinutes = selectedTime / 60000;
    timerRunning = true;
    previousMillis = millis(); // Reset blink timer
  }
}

// Update the display when timer is running
void updateTimerDisplay()
{
  unsigned long currentMillis = millis();

  // Blink colon every second
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    colonState = !colonState;

    // Calculate hours and minutes
    int hours = remainingMinutes / 60;
    int minutes = remainingMinutes % 60;

    if (hours > 0)
    {
      // Show time as H:MM format
      int displayValue = (hours * 100) + minutes; // Format as HMM (e.g., 1:05 -> 105)
      display.showNumberDecEx(displayValue, colonState ? 0b01000000 : 0b00000000, false);
    }
    else
    {
      // Show only minutes
      display.showNumberDecEx(minutes, colonState ? 0b01000000 : 0b00000000, false);
    }

    // Reduce time every minute
    if (timerRunning && (millis() - startTime) >= 60000)
    {
      startTime += 60000; // Update start time
      if (remainingMinutes > 0)
      {
        remainingMinutes--;
      }
    }
  }
}

// Check if the timer has finished
bool timerFinished()
{
  return (timerRunning && remainingMinutes == 0);
}

// Display flashing "done" when wash is finished
void washEnded()
{
  while (timerFinished() && !inputDetected())
  {
    display.setSegments(SEG_DONE); // Display "done"
    delay(500);                    // Wait for 0.5 seconds
    display.clear();               // Clear the display
    delay(500);                    // Wait for 0.5 seconds
  }
  // display.setSegments(SEG_DONE); // Display "done"
  // delay(1000);                   // Wait for 2 seconds
  // display.clear();               // Clear the display
}

void setup()
{
  Serial.begin(115200); // Start the serial communication
  Serial.println("Dishwasher timer starting...");

  // Set the pins as inputs with pull-up resistors
  pinMode(Intensive, INPUT_PULLUP);
  pinMode(Normal, INPUT_PULLUP);
  pinMode(ECO, INPUT_PULLUP);
  pinMode(Glass, INPUT_PULLUP);
  pinMode(Quickwash, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  display.setBrightness(0x0f); // Set the brightness to maximum
  display.clear();             // Clear the display
  Wire.begin();                // Initialize the I2C bus
  Wire.setClock(100000);       // Set the I2C clock speed to 100kHz

  Serial.println("Dishwasher timer ready!");
  Serial.println("Waiting for input...");
}

void loop()
{
  if (inputDetected() && !timerRunning)
  {
    selectedTime = getTimerValue();
    displayTimerValue();
  }

  if (startButtonPressed())
  {
    startTimer(selectedTime);
  }

  if (timerRunning)
  {
    updateTimerDisplay();
  }

  if (timerFinished())
  {
    washEnded();
    timerRunning = false;
  }
}