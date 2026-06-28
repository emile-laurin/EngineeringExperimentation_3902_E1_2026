const int LED1_Pin=3; // LED Pin number on Arduino

const int button1_Pin=2; // Button Pin number on Arduino

const int LED2_Pin=5; // LED Pin number on Arduino

const int button2_Pin=4; // Button Pin number on Arduino

int button1_state=0;

int button2_state=0;

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(LED1_Pin, OUTPUT); // Set the LED anode pin as an output

  pinMode(button1_Pin,INPUT); // Set the button pin as an inpit

  pinMode(LED2_Pin, OUTPUT); // Set the LED anode pin as an output

  pinMode(button2_Pin,INPUT); // Set the button pin as an inpit
}


void loop() {

  // Read Button State
  button1_state = digitalRead(button1_Pin);
  button2_state = digitalRead(button2_Pin);

if (button1_state==HIGH)
{
  Serial.println("Button1 is Pressed"); // Print a message to the output
   digitalWrite(LED1_Pin, HIGH); // Turn the LED on
}
if (button1_state==LOW)
{
  Serial.println("Button1 is no longer Pressed"); // Print a message to the output
   digitalWrite(LED1_Pin, LOW); // Turn the LED off
}
if (button2_state==HIGH)
{
  Serial.println("Button2 is Pressed"); // Print a message to the output
   digitalWrite(LED2_Pin, HIGH); // Turn the LED on
}
if (button2_state==LOW)
{
  Serial.println("Button2 is no longer Pressed"); // Print a message to the output
   digitalWrite(LED2_Pin, LOW); // Turn the LED on
}
  delay(100); // Small delay to avoid spamming the serial monitor
}