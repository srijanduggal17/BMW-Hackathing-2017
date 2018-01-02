//Declare pin functions on Redboard
#define stpBig 6
#define dirBig 8
#define stpSmall 10
#define dirSmall 12

const int delaying = 1;

const int buttonPin = 2;     // the number of the input from the button
const int UR5Pin =  4;      // the number of the input from the UR5

int stageCounter = 0;
const int additionalSteps = 5; //CHOOSES AMOUNT OF additional Steps after button is pressed
const int maxStepsDown = 10000; //Chooses amount of steps we try to go down before we decide to just go up
int stepCounter = 0; //checks how many steps we have gone down
int countReturnedSteps = 0; //checks how many steps we have gone up
int stageWaiter = -1; //makes sure that the stage doesnt't change prematurely.

void setup() {
    pinMode(stpBig, OUTPUT);
    pinMode(dirBig, OUTPUT);
    pinMode(stpSmall, OUTPUT);
    pinMode(dirSmall, OUTPUT);
    Serial.begin(9600); //Open Serial connection for debugging
    digitalWrite(stpBig, LOW);
    digitalWrite(dirBig, LOW);
    digitalWrite(stpSmall, LOW);
    digitalWrite(dirSmall, LOW);
  
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    // initialize the UR5 pin as an input:
    pinMode(UR5Pin, INPUT);
}


void loop() {
    if (digitalRead(UR5Pin) == HIGH || stageCounter != 0) {
        if (digitalRead(UR5Pin) == HIGH) {
            stageWaiter = 1;
        } else {
            stageWaiter = 0; //stageWaiter might not work exactly like I think it will
        }
        
        stageCounter++;
        stageHandler();
        while (digitalRead(UR5Pin) == stageWaiter) {
          delay(10);
        }
    }
  
}

void stageHandler() {
  int stage = stageCounter % 4;
  if (stage == 1) {
    lowerRack();
    raiseRack(0);
  } else if (stage == 2) {
    raiseRack(1);
  } else if (stage == 3) {
    raiseRackAndChopObject(0);
  } else if (stage == 0) {
    raiseRackAndChopObject(1);
  }
}

void lowerRack() {
    digitalWrite(dirBig, LOW); //Pull direction pin low to move "forward"
    stepCounter = 0;
    countReturnedSteps = 0;
    while (digitalRead(buttonPin) == LOW) {
        moveBigByOneStep();
        stepCounter++;
        if ((stepCounter >= maxStepsDown) || digitalRead(UR5Pin) == LOW) {
          return;
        }
        
    }
    //lower rack by certain amount of additional steps
    for(int x = 0; x < additionalSteps; x++)
    {
        moveBigByOneStep();
    }
    stepCounter += additionalSteps;
}

//HL signifies stage HL COULD MESS UP CAUSE INT
void raiseRack(int HL) {

    digitalWrite(dirBig, HIGH); //Pull direction pin low to move "forward"
    while (countReturnedSteps < stepCounter) {

        moveBigByOneStep();
        countReturnedSteps++;
        if (digitalRead(UR5Pin) == HL) {
            return;
        }
    }
}

//HL signifies stage
void raiseRackAndChopObject(int HL) {
    digitalWrite(dirSmall, HIGH); //IDK IF SHOULD BE HIGH OR LOW Pull direction pin low to move "forward"
    while (true) {
        if (countReturnedSteps < stepCounter) {
            moveBigByOneStep();
            countReturnedSteps++;
        }
        moveSmallByOneStep();
        if (digitalRead(UR5Pin) == HL) {
            return;
        }
    }
}

void moveBigByOneStep() {
    digitalWrite(stpBig,HIGH); //Trigger one step forward
    delay(delaying);
    digitalWrite(stpBig,LOW); //Pull step pin low so it can be triggered again
    delay(delaying);
}

void moveSmallByOneStep() {
    digitalWrite(stpSmall,HIGH); //Trigger one step forward
    delay(delaying);
    digitalWrite(stpSmall,LOW); //Pull step pin low so it can be triggered again
    delay(delaying);
}


