/* Complete USB Joystick Example
   Teensy becomes a USB joystick with 16 or 32 buttons and 6 axis input

   You must select Joystick from the "Tools > USB Type" menu

   Pushbuttons should be connected between the digital pins and ground.
   Potentiometers should be connected to analog inputs 0 to 5.

   This example code is in the public domain.

   Documentation for the methods used to pass analog input and digital values to the Joystick class:

   To send button actions, just use Joystick.button, with the button number to change (1 to 32), and either pressed (1) or not pressed (0).
      Joystick.button(num, 1);      // Press button "num" (1 to 32)
      Joystick.button(num, 0);      // Release button "num" (1 to 32)
   There are six functions to control the Joystick's 6 axes. Each takes a number from 0 to 1023, where 512 is the center or resting position.
      Joystick.X(value);            // "value" is from 0 to 1023
      Joystick.Y(value);            //   512 is resting position
      Joystick.Z(value);
      Joystick.Zrotate(value);
      Joystick.sliderLeft(value);
      Joystick.sliderRight(value);
   The hat switch can be moved in 45 degree increments. Use -1 to return the hat to center resting position.
      Joystick.hat(angle);          // "angle" is 0,45,90,135,180,225,270,315,-1
   
*/

// Configure the number of buttons.  Be careful not
// to use a pin for both a digital button and analog
// axis.  The pullup resistor will interfere with
// the analog voltage.
const int numButtons = 10;  // less than 13, otherwise it overlaps with Analog inputs

// Disable test features, enabling this turns on serial output and hat simulation
// #define JS_TEST_MODE

byte allButtons[numButtons];
#ifdef JS_TEST_MODE
byte prevButtons[numButtons];
int angle=0;
#endif

void setup()
{
  // you can print to the serial monitor while the joystick is active!
#ifdef JS_TEST_MODE
  Serial.begin(9600);
#endif
  // configure the joystick to manual send mode.  This gives precise
  // control over when the computer receives updates, but it does
  // require you to manually call Joystick.send_now().
  Joystick.useManualSend(true);
  for (int i=0; i<numButtons; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
#ifdef JS_TEST_MODE
  Serial.println("Begin Complete Joystick Test");
#endif

  // initialize joystick hat input to not pressed.
  Joystick.hat(-1);
}

void loop()
{
  // read 6 analog inputs and use them for the joystick axis
  Joystick.X(analogRead(0));
  Joystick.Y(analogRead(1));
  Joystick.Z(analogRead(2));
  Joystick.Zrotate(analogRead(3));
  Joystick.sliderLeft(analogRead(4));
  Joystick.sliderRight(analogRead(5));
  
  // read digital pins and use them for the buttons
  for (int i=0; i<numButtons; i++)
  {
    if (digitalRead(i))
    {
      // when a pin reads high, the button is not pressed
      // the pullup resistor creates the "on" signal
      allButtons[i] = 0;
    }
    else
    {
      // when a pin reads low, the button is connecting to ground.
      allButtons[i] = 1;
    }
    Joystick.button(i + 1, allButtons[i]);
  }

#ifdef JS_TEST_MODE
  // make the hat switch automatically move in a circle
  angle = angle + 1;
  if (angle >= 360) angle = 0;
  Joystick.hat(angle);
#endif
  
  // Because setup configured the Joystick manual send,
  // the computer does not see any of the changes yet.
  // This send_now() transmits everything all at once.
  Joystick.send_now();
  
#ifdef JS_TEST_MODE
  // check to see if any button changed since last time
  boolean anyChange = false;
  for (int i=0; i<numButtons; i++)
  {
    if (allButtons[i] != prevButtons[i])
      anyChange = true;
    prevButtons[i] = allButtons[i];
  }
  
  // if any button changed, print them to the serial monitor
  if (anyChange) {
    Serial.print("Buttons: ");
    for (int i=0; i<numButtons; i++) {
      Serial.print(allButtons[i], DEC);
    }
    Serial.println();
  }
#endif
  
  // a brief delay, so this runs "only" 200 times per second
  delay(5);
}
