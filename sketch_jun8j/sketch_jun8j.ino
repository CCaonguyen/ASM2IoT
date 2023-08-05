//ARDUINO TUTORIAL - 2 TRAFFIC LIGHT PROJECT

//Create the variables and assign the pins to them.

int REDPIN=2;
int YELLOWPIN=12;
int GREENPIN=4;
int buzzer = 3;
void setup() {
//Set the pins to output pins using pinMode
pinMode(REDPIN, OUTPUT);
pinMode(YELLOWPIN, OUTPUT);
pinMode(GREENPIN, OUTPUT);
}

void loop() {
//Make the LEDs blink in turn:
//Turn on the red led, and turn off the yellow and green leds.

digitalWrite(REDPIN, HIGH);

digitalWrite(GREENPIN, LOW);
delay(2000);

//Turn on the yellow led, and turn off the red and green leds.

digitalWrite(REDPIN, LOW);\
digitalWrite(YELLOWPIN, HIGH);
digitalWrite(GREENPIN, LOW);
delay(2000);

//Turn on the green led, and turn off the red and yellow leds.

digitalWrite(REDPIN, LOW);

digitalWrite(GREENPIN, HIGH);
delay(2000);
}