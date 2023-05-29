
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, HIGH);
  digitalWrite(D4, LOW);
  delay(100);           
  digitalWrite(D0, LOW); 
  digitalWrite(D4, HIGH); 
  delay(100);           
