// taken from https://docs.arduino.cc/built-in-examples/digital/Debounce

struct Led {
  int pin;
  bool state;
};

struct PushButton {
  int pin;
  bool state, prevState;
  unsigned long lastDebounceTime, debounceDelay;
};

Led led = {3, false};
PushButton button = {4, false, false, 0, 50};

void setup() {
  pinMode(led.pin, OUTPUT);
  pinMode(button.pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(button.pin);
  
  if (reading != button.prevState) button.lastDebounceTime = millis(); // reset the lastDebounce time

  if ((millis() - button.lastDebounceTime) > button.debounceDelay) { // if the button was pressed for longer than the debounce time
    if (reading != button.state) { // if the state changes
      button.state = reading;
      if (button.state == HIGH) { // only toggle if the new state is HIGH
        led.state = !led.state;
      }
    }
  }
  
  digitalWrite(led.pin, led.state);
  button.prevState = reading;
}
