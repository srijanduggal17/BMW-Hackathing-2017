int rackstep = 2;
int rackdir = 3;

int tapemotor = 8;

int UR5button = 13;

void raiseRack() {
  digitalWrite(rackdir,HIGH);
  for (int x=0; x<1600; x++) {
    digitalWrite(rackstep, HIGH);
    delay(2);
    digitalWrite(rackstep,LOW);
    delay(2);
  }
}

void lowerRack() {
  digitalWrite(rackdir,LOW);
  for (int x=0; x<1600; x++) {
    digitalWrite(rackstep, HIGH);
    delay(2);
    digitalWrite(rackstep,LOW);
    delay(2);
  }
}

void turntape(int delaytime) {
  digitalWrite(tapemotor,HIGH);
  delay(delaytime);
  digitalWrite(tapemotor,LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(rackstep, OUTPUT);
  pinMode(rackdir, OUTPUT);
  digitalWrite(rackstep, LOW);
  digitalWrite(rackdir, LOW);

  pinMode(tapemotor, OUTPUT);
  digitalWrite(tapemotor, LOW);

  pinMode(UR5button, INPUT);

  raiseRack();
  lowerRack();
//  turntape(1000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(UR5button == HIGH)) {
    Serial.println("hello");
  }
}
