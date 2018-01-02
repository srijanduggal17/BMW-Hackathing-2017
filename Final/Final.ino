int ur5in = 4;
int motorstep = 9;
int motordir = 8;
int resetbutton = 12;
int dcmotor = 6;

int gripstarted = false;
int gripended = true;

int rollcounter = 0;

int resetmode = true;

void setup() {
  pinMode(ur5in, INPUT);  
  pinMode(resetbutton, INPUT);              
  pinMode(motordir, OUTPUT);     
  pinMode(motorstep, OUTPUT);
  pinMode(dcmotor, OUTPUT);
  digitalWrite(motordir, LOW);
  digitalWrite(motorstep, LOW);
  digitalWrite(dcmotor, LOW);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(resetbutton) == LOW && resetmode == true) {
    Serial.println("reset");
      digitalWrite(motordir, HIGH);
      while (resetmode == true) {
        int counter = 10;
        while (counter > 1) {
          digitalWrite(motorstep, HIGH);
          delayMicroseconds(500);
          digitalWrite(motorstep, LOW);
          delayMicroseconds(500);
          counter -= 1;
        }
        digitalWrite(dcmotor, LOW);
        if (digitalRead(resetbutton) == HIGH) {
          resetmode = false;
        }
      }
      rollcounter = 0;
  }

  if (digitalRead(resetbutton) == LOW && resetmode == false) {
    while (resetmode == false) {
      digitalWrite(dcmotor, HIGH);
      if (digitalRead(resetbutton) == HIGH) {
        resetmode = true;
        digitalWrite(dcmotor, LOW);
      }
    }      
  }
  
  if (digitalRead(ur5in) == LOW && gripstarted == false && gripended == true) {
    Serial.println("pressed");
    int steps_remaining = 1600;
    digitalWrite(dcmotor, LOW);
    while (steps_remaining > 1) {
      digitalWrite(motordir, LOW);
      digitalWrite(motorstep, HIGH);
      delayMicroseconds(500);
      digitalWrite(motorstep, LOW);
      delayMicroseconds(500);
      steps_remaining -= 1;
    }

    int stepsup = 600;
    while (stepsup > 1) {
      digitalWrite(motordir, HIGH);
      digitalWrite(motorstep, HIGH);
      delayMicroseconds(500);
      digitalWrite(motorstep, LOW);
      delayMicroseconds(500);
      stepsup -= 1;
    }

    gripstarted = true;
    gripended = false;
  }

  if (digitalRead(ur5in) == HIGH && gripstarted == true && gripended == false) {
    int stepstopush = 1100;
    while (stepstopush > 1) {
      digitalWrite(dcmotor, HIGH);
      digitalWrite(motordir, HIGH);
      digitalWrite(motorstep, HIGH);
      delayMicroseconds(500);
      digitalWrite(motorstep, LOW);
      delayMicroseconds(500);
      stepstopush -= 1;
    }
    digitalWrite(dcmotor, HIGH);
    rollcounter = 500;

    gripstarted = false;
    gripended = true;
  }

  if (rollcounter != 0) {
    rollcounter -= 1;
    delay(10);
  }
  else {
    digitalWrite(dcmotor, LOW);
  }
}

