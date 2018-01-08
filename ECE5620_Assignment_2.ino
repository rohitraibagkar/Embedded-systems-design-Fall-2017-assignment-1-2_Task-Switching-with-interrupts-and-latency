#define led_1 22 /* defining led 1 on pin 22...*/
#define led_2 23 /* defining led 2 on pin 23...*/
#define led_3 24 /* defining led 3 on pin 24...*/
#define led_4 25 /* defining led 4 on pin 25...*/
#define led_5 26 /* defining led 5 on pin 26...*/
#define myPot 0 /* define input analog pin 0 for potentiometer...*/
#define switch_1 53 /* defining switch 1 on pin 53...*/
#define switch_2 52 /* defining switch 2 on pin 54...*/
#define switch_3 51 /* defining switch 3 on pin 51...*/

unsigned long timer[6]; /*  An array of five elements to keep reference start time ... */
int reset = 0; /*  reset bit to reset LED... */
int switchCondition[] = {LOW, LOW, LOW}; /*  an array to keep values of switch conditions... */
unsigned long startTime = 0; /*  another integer to keep reference start time to blink LED in span... */
char message[1000]; /*  array to store message for output... */
char state[100]; /*  array to store the state of the switches... */
int currentVal = 0; /*  stores current value of timer... */
int mapped = 0; /*  stores the mapped value of the A/D output... */
void setup() /*  function to set up pins and communication... */
{
  // put your setup code here, to run once:
  /*  Code to set up pins...*/
  pinMode(led_1, OUTPUT);  /*  LED 1 */
  pinMode(led_2, OUTPUT);  /*  LED 2 */
  pinMode(led_3, OUTPUT);  /*  LED 3 */
  pinMode(led_4, OUTPUT);  /*  LED 4 */
  pinMode(led_5, OUTPUT);  /*  LED 5 */

  pinMode(switch_1, INPUT); /* Switch 1 */
  pinMode(switch_2, INPUT); /* Switch 2 */
  pinMode(switch_3, INPUT); /* Switch 3 */
  Serial.begin(9600); /*  beginning serial communication to print values... */
}

void loop() /*  function to run continiously... */
{
  mapped = map(analogRead(0), 0, 1023, 200, 1000); /*  ... */
  int switchCondition[] = {digitalRead(51), digitalRead(52), digitalRead(53)}; /*  reading switchconditions ... */
  if (!digitalRead(51) && !digitalRead(52) && !digitalRead(53)) /*  checking if all switches are open... */
  {
    Open_Open_Open(100); /*  functios to blink all LEDs is being called... */
    sprintf(message, "SW 3 : Off \t SW 2 : Off \t SW 1 : Off \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (!digitalRead(51) && !digitalRead(52) && digitalRead(53)) /*  else checking if switch 1 is closed... */
  {
    sequential_blinking(mapped, 100); /*  calling function to blink LEDs in sequence with 1 flash/second... */
    sprintf(message, "SW 3 : Off \t SW 2 : Off \t SW 1 : On \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (!digitalRead(51) && digitalRead(52) && !digitalRead(53)) /*  else checking if switch 2 is closed... */
  {
    sequential_blinking(mapped, 50); /*  calling function to blink LEDs in sequence with 2 flash/second... */
    sprintf(message, "SW 3 : Off \t SW 2 : On \t SW 1 : Off \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (!digitalRead(51) && digitalRead(52) && digitalRead(53)) /*  else checking if switch 1 & 2 is closed... */
  {
    sequential_blinking(mapped, 33); /*  calling function to blink LEDs in sequence with 4 flash/second... */
    sprintf(message, "SW 3 : Off \t SW 2 : On \t SW 1 : On \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (digitalRead(51) && !digitalRead(52) && !digitalRead(53)) /*  else checking if switch 3 is closed... */
  {
    blinking_collision(mapped, 100); /*  calling function to blink LEDs in collision manner with 1 flash/second... */
    sprintf(message, "SW 3 : On \t SW 2 : Off \t SW 1 : Off \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (digitalRead(51) && !digitalRead(52) && digitalRead(53)) /*  else checking if switch 3 & 1 is closed... */
  {
    blinking_collision(mapped, 50); /*  calling function to blink LEDs in collision manner with 2 flash/second... */
    sprintf(message, "SW 3 : On \t SW 2 : Off \t SW 1 : On \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (digitalRead(51) && digitalRead(52) && !digitalRead(53)) /*  else checking if switch 3 & 2 is closed... */
  {
    blinking_collision(mapped, 33); /*  calling function to blink LEDs in collision manner with 4 flash/second... */
    sprintf(message, "SW 3 : On \t SW 2 : On \t SW 1 : Off \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  else if (digitalRead(51) && digitalRead(52) && digitalRead(53)) /*  else checking if switch 3 & 2 & 1 is closed... */
  {
    closed_closed_closed(mapped/2); /*  Blinking all LEDs at different flash rates... */
    sprintf(message, "SW 3 : On \t SW 2 : On \t SW 1 : On \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
    display_state(message, 1000, 5);
  }
  //sprintf(message, "SW 3 : Closed \t SW 2 : Closed \t SW 1 : Closed \t A/D Output : %d \t Mapped output : %d", analogRead(0), mapped);
  //sprintf(message, "SW 1 : %d, Current Value is : %d, Voltage is : %d", digitalRead(53), analogRead(0), (char)digitalRead(53));
  //Serial.println(message);
  //delay(1000);
  //display_state(message, 500, 5);
}

void Open_Open_Open(int interval) /*  function to blink all LEDs at same time && same rate... */
{
  my_LED_blinker(led_1, interval, 0); /*  calling function to blink LED 1... */
  my_LED_blinker(led_2, interval, 1); /*  calling function to blink LED 2... */
  my_LED_blinker(led_3, interval, 2); /*  calling function to blink LED 3... */
  my_LED_blinker(led_4, interval, 3); /*  calling function to blink LED 4... */
  my_LED_blinker(led_5, interval, 4); /*  calling function to blink LED 5... */
}

void closed_closed_closed(float interval) /*  function to blink all the LEDs at same time && different rate... */
{
  my_LED_blinker(led_1, interval, 0); /*  calling function to blink LED 1 @ 1 flash per second... */
  my_LED_blinker(led_2, interval/2, 1); /*  calling function to blink LED 2 @ 2 flashes per second... */
  my_LED_blinker(led_3, interval/3, 2); /*  calling function to blink LED 3 @ 3 flashes per second... */
  my_LED_blinker(led_4, interval/4, 3); /*  calling function to blink LED 4 @ 4 flashes per second... */
  my_LED_blinker(led_5, interval/5, 4); /*  calling function to blink LED 5 @ 5 flashes per second... */
}

void sequential_blinking(int interval, int frequency ) /*  function to blink LEDs in sequence with interval and frequency as input... */
{
  if (((long) millis() - startTime) > 8 * interval) /*  checking if time elapsed is greater than interval... */
  {
    startTime = millis(); /*  if yes, then resetting millis()... */
  }
  else if (((long) millis() - startTime) <= 8 * interval) /*  else checking if time elapsed is less than interval... */
  {
    blinking_in_span(led_1, 0000, interval, frequency, 0); /*  blink LED 1 in given span with given frequency... */
    blinking_in_span(led_2, interval, 2 * interval, frequency, 1); /*  blink LED 2 in given span with given frequency... */
    blinking_in_span(led_3, 2 * interval, 3 * interval, frequency, 2); /*  blink LED 3 in given span with given frequency... */
    blinking_in_span(led_4, 3 * interval, 4 * interval, frequency, 3); /*  blink LED 4 in given span with given frequency... */
    blinking_in_span(led_5, 4 * interval, 5 * interval, frequency, 4); /*  blink LED 5 in given span with given frequency... */
    blinking_in_span(led_4, 5 * interval, 6 * interval, frequency, 3); /*  blink LED 4 in given span with given frequency... */
    blinking_in_span(led_3, 6 * interval, 7 * interval, frequency, 2); /*  blink LED 3 in given span with given frequency... */
    blinking_in_span(led_2, 7 * interval, 8 * interval, frequency, 1); /*  blink LED 1 in given span with given frequency... */
  }
}

void blinking_collision(int interval, int frequency) /*  function to blink LED in collision manner with interval and frequency as inputs... */
{
  if (((long) millis() - startTime) > 4 * interval) /*  checking if time elapsed is greater than interval span provided... */
  {
    startTime = millis(); /*  if yes then reset the timer... */
  }
  else if (((long) millis() - startTime) <= 4 * interval) /*  else if time elapsed is within interval span... */
  {
    blinking_in_span(led_1, 0000, interval, frequency, 0); /*  blink LED 1 in given span with given frequency... */
    blinking_in_span(led_5, 0000, interval, frequency, 4); /*  blink LED 5 in given span with given frequency... */
    blinking_in_span(led_2, interval, 2 * interval, frequency, 1); /*  blink LED 2 in given span with given frequency... */
    blinking_in_span(led_4, interval, 2 * interval, frequency, 3); /*  blink LED 4 in given span with given frequency... */
    blinking_in_span(led_3, 2 * interval, 3 * interval, frequency, 2); /*  blink LED 3 in given span with given frequency... */
    blinking_in_span(led_2, 3 * interval, 4 * interval, frequency, 1); /*  blink LED 2 in given span with given frequency... */
    blinking_in_span(led_4, 3 * interval, 4 * interval, frequency, 3); /*  blink LED 4 in given span with given frequency... */
  }
}

void Reset_LED()
{
  digitalWrite(22, LOW); /*  turning LED 1 off... */
  digitalWrite(23, LOW); /*  turning LED 2 off... */
  digitalWrite(24, LOW); /*  turning LED 3 off... */
  digitalWrite(25, LOW); /*  turning LED 4 off... */
  digitalWrite(26, LOW); /*  turning LED 5 off... */
  reset = false; /*  reset bit is set to zero... */
}

void my_LED_blinker(int led_num, int interval, int array) /*  function to blink LED at particular flashrate  with LED number, interval and array as inputs... */
{
  if (((long) millis() - timer[array]) >= interval) /*  checking if time elapsed is greater than interval... */
  {
    timer[array] = millis(); /*  if yes then store current elapsed time in given array... */
    digitalWrite(led_num, !digitalRead(led_num)); /*  && invert the state of current LED... */
  }
  //Serial.println(millis()); /*  printing time elapsed on serial monitor... */
}

void blinking_in_span(int led_num, int start_span, int end_span, int interval, int array) /* function of arguments 'led number, start time, end time, blinking interval, starter of timer' */
{
  if ((((long) millis() - startTime) > start_span) && (((long) millis() - startTime) <= end_span)) /*  checking if time elapsed is within span provided... */
  {
    my_LED_blinker(led_num, interval, array); /*  if yes then blink LED at given interval... */
  }
}

void display_state(char* message,int interval, int array) /*  function display message in intervals... */
{
  if (((long) millis() - timer[array]) >= interval) /*  checking whether elapsed time is greater than interval ... */
  {
    timer[array] = millis(); /*  if yes then store current elapsed time in given array... */
    Serial.println(message); /*  print message on monitor... */
  }
}

