volatile int encoderValue = 0;
unsigned long startTime;
int slotSensor = 2;

int motLeftForward = 10;
int motLeftBack = 12;
int motLeftVelo = 11;


int motRightForward = 8;
int motRightBack = 9;
int motRightVelo = 5;

void count(void);

void setup(){
  Serial.begin(9600);

  pinMode(slotSensor, INPUT);

  pinMode(motLeftForward, OUTPUT);
  pinMode(motLeftBack, OUTPUT);
  pinMode(motLeftVelo, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(slotSensor), count, CHANGE);
}

void loop() {
  delay(3000);
  
  Serial.println("0, 0");
  startTime = millis();
  
  digitalWrite(motLeftForward, HIGH);
  digitalWrite(motLeftBack, LOW);
  analogWrite(motLeftVelo, 100);
  
  digitalWrite(motRightForward, HIGH);
  digitalWrite(motRightBack, LOW);
  analogWrite(motRightVelo, 100);
  while(1){
    if(encoderValue > 100) {
        digitalWrite(motLeftForward, LOW);
        digitalWrite(motLeftBack, LOW);
        analogWrite(motLeftVelo, 0);
        
        digitalWrite(motRightForward, LOW);
        digitalWrite(motRightBack, LOW);
        analogWrite(motRightVelo, 0);
    }
  }
}

void count() {
  static unsigned long lastTime;
  unsigned long timeNow = millis();

  if (timeNow - lastTime < 2) return;

  encoderValue++;
  Serial.print(timeNow - startTime); Serial.print(", "); Serial.println(encoderValue);
  lastTime = timeNow;
}