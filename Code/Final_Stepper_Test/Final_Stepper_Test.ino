int rackstep = 2;
int rackdir = 3;

int limitswitch = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(rackstep, OUTPUT);
  pinMode(rackdir, OUTPUT);
  pinMode(limitswitch, INPUT);
  
  digitalWrite(rackstep, LOW);
  digitalWrite(rackdir, LOW);
  Serial.begin(9600);

/*
  for (int x=0; x<1600; x++) {
    digitalWrite(rackdir, LOW);
    digitalWrite(rackstep, HIGH);
    delay(1);
    digitalWrite(rackstep,LOW);
    delay(1);
  }

  for (int x=0; x<1600; x++) {
    digitalWrite(rackdir, HIGH);
    digitalWrite(rackstep, HIGH);
    delay(1);
    digitalWrite(rackstep,LOW);
    delay(1);
  }
*/
}

void loop() {
  Serial.println(digitalRead(limitswitch));

  /*
    for (int x=0; x<1600; x++) {
    digitalWrite(rackdir, LOW);
    digitalWrite(rackstep, HIGH);
    delay(1);
    digitalWrite(rackstep,LOW);
    delay(1);
    }*/
}
