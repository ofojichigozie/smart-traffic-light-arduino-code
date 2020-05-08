/****************************/
/* Junction A Routes LIGHTs */
/****************************/
#define A1_RED_LIGHT 22
#define A1_AMBER_LIGHT 23
#define A1_GREEN_LIGHT 24

#define A2_RED_LIGHT 26
#define A2_AMBER_LIGHT 27
#define A2_GREEN_LIGHT 28

#define A3_RED_LIGHT 30
#define A3_AMBER_LIGHT 31
#define A3_GREEN_LIGHT 32

#define A4_RED_LIGHT 34
#define A4_AMBER_LIGHT 35
#define A4_GREEN_LIGHT 36

/****************************/
/* Junction B Routes LIGHTs */
/****************************/
#define B1_RED_LIGHT 23
#define B1_AMBER_LIGHT 24
#define B1_GREEN_LIGHT 25

#define B2_RED_LIGHT 27
#define B2_AMBER_LIGHT 28
#define B2_GREEN_LIGHT 29

#define B3_RED_LIGHT 31
#define B3_AMBER_LIGHT 32
#define B3_GREEN_LIGHT 33

#define B4_RED_LIGHT 35
#define B4_AMBER_LIGHT 36
#define B4_GREEN_LIGHT 37

/**********************************************************/
/* Junction A IR Sensors (Counting system for busy routes */
/**********************************************************/
#define A_IR1 39
#define A_IR2 40

/**********************************************************/
/* Junction B IR Sensors (Counting system for busy routes */
/**********************************************************/
#define B_IR1 42
#define B_IR2 43

/*********************************************************************************************************************************************************/
/* Variables to hold the number of detected vehicles on busy lanes (A1, A3, B1 and B3). The number of vehicles will determine the GO time on these lanes */
/*********************************************************************************************************************************************************/
uint8_t A1_numOfVehicles = 0;
uint8_t A3_numOfVehicles = 0;
uint8_t B1_numOfVehicles = 0;
uint8_t B3_numOfVehicles = 0;

/*************************************************************************************************************************/
/* These constant DELAY values are for ALL RED and AMBER lights (Stop and Prepare Time). Lane density do not affect them */
/*************************************************************************************************************************/
const int defaultRedLightDelay = 5000;
const int defaultAmberLightDelay = 2000;

/*****************************/
/* Default GO time for lanes */
/*****************************/
const int defaultGreenLightDelay = 5000;

/*********************************************************************************************************************************************/
/* These non-constant DELAY values will determine the GO time for vehicles on a lane. These values are dependent on the density on the lane. */
/*********************************************************************************************************************************************/
int A1_GreenLightDelay = 10000;
int A3_GreenLightDelay = 10000;
int B1_GreenLightDelay = 10000;
int B3_GreenLightDelay = 10000;

/**********************************************/
/* Variables to hold active lane at junctions */
/**********************************************/
uint8_t activeLaneAtA = 1;
uint8_t activeLaneAtB = 1;

/*************************************************/
/* Variables to hold current delays at junctions */
/*************************************************/
int currentDelayAtA = 0;
int currentDelayAtB = 0;

void prepareToStopMovementOnLane(int redLIGHT, int amberLIGHT, int greenLIGHT){
  digitalWrite(redLIGHT, LOW);
  digitalWrite(amberLIGHT, HIGH);
  digitalWrite(greenLIGHT, HIGH);
}

void stopMovementOnLane(int redLIGHT, int amberLIGHT, int greenLIGHT){
  digitalWrite(redLIGHT, HIGH);
  digitalWrite(amberLIGHT, LOW);
  digitalWrite(greenLIGHT, LOW);
}

void prepareToStartMovementOnLane(int redLIGHT, int amberLIGHT, int greenLIGHT){
  digitalWrite(redLIGHT, HIGH);
  digitalWrite(amberLIGHT, HIGH);
  digitalWrite(greenLIGHT, LOW);
}

void startMovementOnLane(int redLIGHT, int amberLIGHT, int greenLIGHT){
  digitalWrite(redLIGHT, LOW);
  digitalWrite(amberLIGHT, LOW);
  digitalWrite(greenLIGHT, HIGH);
}


void controlTrafficAtJunctionA(){
  
  if(activeLaneAtA == 1 && currentDelayAtA != 0){
    if(currentDelayAtA > defaultAmberLightDelay){
      startMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
    }else if(currentDelayAtA <= defaultAmberLightDelay){
      prepareToStopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      prepareToStartMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
    }

    Serial.println("Movement on lane 1");
    Serial.print("Current delay: "); Serial.println(currentDelayAtA);
    
  }

  if(activeLaneAtA == 2 && currentDelayAtA != 0){
    if(currentDelayAtA > defaultAmberLightDelay){
      startMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
    }else if(currentDelayAtA <= defaultAmberLightDelay){
      prepareToStopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      prepareToStartMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      stopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
    }

    Serial.println("Movement on lane 2");
    Serial.print("Current delay: "); Serial.println(currentDelayAtA);
    
  }

  if(activeLaneAtA == 3 && currentDelayAtA != 0){
    if(currentDelayAtA > defaultAmberLightDelay){
      startMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      stopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
    }else if(currentDelayAtA <= defaultAmberLightDelay){
      prepareToStopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
      prepareToStartMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
      stopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
    }

    Serial.println("Movement on lane 3");
    Serial.print("Current delay: "); Serial.println(currentDelayAtA);
    
  }

  if(activeLaneAtA == 4 && currentDelayAtA != 0){
    if(currentDelayAtA > defaultAmberLightDelay){
      startMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
      stopMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
    }else if(currentDelayAtA <= defaultAmberLightDelay){
      prepareToStopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);
      prepareToStartMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
      stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
      stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
    }

    Serial.println("Movement on lane 4");
    Serial.print("Current delay: "); Serial.println(currentDelayAtA);
    
  }


  if(activeLaneAtA == 1 && currentDelayAtA == 0){
    activeLaneAtA = 2;
    currentDelayAtA = defaultGreenLightDelay + defaultAmberLightDelay;
  }

  if(activeLaneAtA == 2 && currentDelayAtA == 0){
    activeLaneAtA = 3;
    currentDelayAtA = A3_GreenLightDelay + defaultAmberLightDelay;
  }

  if(activeLaneAtA == 3 && currentDelayAtA == 0){
    activeLaneAtA = 4;
    currentDelayAtA = defaultGreenLightDelay + defaultAmberLightDelay;
  }

  if(activeLaneAtA == 4 && currentDelayAtA == 0){
    activeLaneAtA = 1;
    currentDelayAtA = A1_GreenLightDelay + defaultAmberLightDelay;
  }

  currentDelayAtA = currentDelayAtA - 1000;
}

void setup() {

  Serial.begin(9600);
  
  /************************************/
  /* Declare all LIGHT pins as OUTPUT */
  /************************************/
  pinMode(A1_RED_LIGHT, OUTPUT);
  pinMode(A1_AMBER_LIGHT, OUTPUT);
  pinMode(A1_GREEN_LIGHT, OUTPUT);

  pinMode(A2_RED_LIGHT, OUTPUT);
  pinMode(A2_AMBER_LIGHT, OUTPUT);
  pinMode(A2_GREEN_LIGHT, OUTPUT);

  pinMode(A3_RED_LIGHT, OUTPUT);
  pinMode(A3_AMBER_LIGHT, OUTPUT);
  pinMode(A3_GREEN_LIGHT, OUTPUT);

  pinMode(A4_RED_LIGHT, OUTPUT);
  pinMode(A4_AMBER_LIGHT, OUTPUT);
  pinMode(A4_GREEN_LIGHT, OUTPUT);

  pinMode(B1_RED_LIGHT, OUTPUT);
  pinMode(B1_AMBER_LIGHT, OUTPUT);
  pinMode(B1_GREEN_LIGHT, OUTPUT);

  pinMode(B2_RED_LIGHT, OUTPUT);
  pinMode(B2_AMBER_LIGHT, OUTPUT);
  pinMode(B2_GREEN_LIGHT, OUTPUT);

  pinMode(B3_RED_LIGHT, OUTPUT);
  pinMode(B3_AMBER_LIGHT, OUTPUT);
  pinMode(B3_GREEN_LIGHT, OUTPUT);

  pinMode(B4_RED_LIGHT, OUTPUT);
  pinMode(B4_AMBER_LIGHT, OUTPUT);
  pinMode(B4_GREEN_LIGHT, OUTPUT);

  /****************************/
  /* Declare IR pins as INPUT */
  /****************************/
  pinMode(A_IR1, INPUT);
  pinMode(A_IR2, INPUT);
  pinMode(B_IR1, INPUT);
  pinMode(B_IR2, INPUT);

  /******************************************************************/
  /* At start, currentDelays are for GO time on Lane 1 of junctions */
  /******************************************************************/
  currentDelayAtA = A1_GreenLightDelay + defaultAmberLightDelay;
  currentDelayAtB = B1_GreenLightDelay + defaultAmberLightDelay;

  /*****************************************************************************************/
  /* Vehicular movement at Junction A Lane 1 (A1). No movement on other lanes (A2, A3. A4) */
  /*****************************************************************************************/
  startMovementOnLane(A1_RED_LIGHT, A1_AMBER_LIGHT, A1_GREEN_LIGHT);
  stopMovementOnLane(A2_RED_LIGHT, A2_AMBER_LIGHT, A2_GREEN_LIGHT);
  stopMovementOnLane(A3_RED_LIGHT, A3_AMBER_LIGHT, A3_GREEN_LIGHT);
  stopMovementOnLane(A4_RED_LIGHT, A4_AMBER_LIGHT, A4_GREEN_LIGHT);

  Serial.println("Started movement on lane 1");
  Serial.print("Current delay: "); Serial.println(currentDelayAtA);

  /*****************************************************************************************/
  /* Vehicular movement at Junction B Lane 1 (B1). No movement on other lanes (B2, B3. B4) */
  /*****************************************************************************************/
  startMovementOnLane(B1_RED_LIGHT, B1_AMBER_LIGHT, B1_GREEN_LIGHT);
  stopMovementOnLane(B2_RED_LIGHT, B2_AMBER_LIGHT, B2_GREEN_LIGHT);
  stopMovementOnLane(B3_RED_LIGHT, B3_AMBER_LIGHT, B3_GREEN_LIGHT);
  stopMovementOnLane(B4_RED_LIGHT, B4_AMBER_LIGHT, B4_GREEN_LIGHT);

}

void loop() {
  controlTrafficAtJunctionA();
  delay(2000);
}
