//Declare pin functions on Redboard
#define stp 2
#define dir 3

int delaying;
int x;


void movestep(int steps,int rate) {
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

void movedeg(int deg, int rate, int deg_per_step = 1.8, int ustep_per_step = 8) {
  int stepstomove = deg / (deg_per_step);
  movestep(stepstomove, rate); 
}

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  digitalWrite(stp, LOW);
  digitalWrite(dir, HIGH);
  Serial.begin(9600); //Open Serial connection for debugging
}


void loop() {
  movedeg(90,10);
  delay(1000);
  movedeg(-90,10);
  delay(1000);
}



