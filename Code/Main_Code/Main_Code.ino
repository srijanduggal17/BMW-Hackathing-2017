//Declare pin functions on Redboard
#define stp 4
#define dir 7

int delaying = 1;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  Serial.begin(9600); //Open Serial connection for debugging
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
}


void loop() {
    digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
    for(x= 1; x<1600; x++)  //Loop the forward stepping enough times for motion to be visible
    {
      digitalWrite(stp,HIGH); //Trigger one step forward
      delay(delaying);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      delay(delaying);
    }

       digitalWrite(dir, HIGH); //Pull direction pin low to move "forward"
    for(x= 1; x<1600; x++)  //Loop the forward stepping enough times for motion to be visible
    {
      digitalWrite(stp,HIGH); //Trigger one step forward
      delay(delaying);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      delay(delaying);
    }

  
   

  
}

