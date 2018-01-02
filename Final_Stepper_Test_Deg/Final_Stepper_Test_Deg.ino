//Declare pin functions on Redboard
#define stp 2
#define dir 3

void movestep(int steps) {
  if (steps > 0) {
    digitalWrite(dir, HIGH);
  }

  else {
    digitalWrite(dir, LOW);
  }

  steps = abs(steps);
  
  int steps_remaining = steps;

  while (steps_remaining > 0) {
    digitalWrite(stp, HIGH);
    delay(1);
    digitalWrite(stp, LOW);
    delay(1);
    steps_remaining = steps_remaining - 1;
  }
}

void movedeg(float deg) {
  float stepstomove = (deg/360)*1600;
  movestep(stepstomove);
}

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  digitalWrite(stp, LOW);
  digitalWrite(dir, HIGH);
  Serial.begin(9600); //Open Serial connection for debugging

  movedeg(90);
  delay(1000);
  movedeg(-90);
  delay(1000);
}


void loop() {
}



