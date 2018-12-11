#include <TimerOne.h>

void clockISR(void);

#define SENSOR_SIZE 250

struct sensor_S {
   long int tim;
   int value;
} sensorTab[SENSOR_SIZE];
int sensorIx;

long int tick;

void setup() {
  // put your setup code here, to run once:
  tick = 0;
  sensorIx = 0;
  Timer1.initialize(1000); 
  Timer1.attachInterrupt(clockISR); // own pseudoclock based on AVR timer
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void clockISR(void) {
  tick++;
}

void dumpTable() {
  int i;
  Serial.println(" ---- dump the table ---- ");
  for(i = 0; i < SENSOR_SIZE; i++) {
    Serial.print("sensorTab[");
    Serial.print(i);
    Serial.print("] = { tid = ");
    Serial.print(sensorTab[i].tim);
    Serial.print(" värde = ");
    Serial.print(sensorTab[i].value);
    Serial.println("}");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(A0);
  Serial.print("Sensor -- tid = ");
  Serial.print(tick);
  Serial.print(" värde = ");
  Serial.println(sensorVal);
  sensorTab[sensorIx].tim = tick;
  sensorTab[sensorIx].value = sensorVal;
  sensorIx++;
  if(sensorIx == SENSOR_SIZE) {
    int i, j;
    // dumpTable();
    int time0 = tick;
    Serial.println(" ---- sort the table ---- ");
	
	
	
	
	
	
	
    for(i = 0; i < SENSOR_SIZE; i++) {
      for(j = 0; j < SENSOR_SIZE - 1; j++) {
        if(sensorTab[i].value > sensorTab[j].value) {
          struct sensor_S temp = sensorTab[i];
          sensorTab[i] = sensorTab[j];
          sensorTab[j] = temp;
        }
      }
    }
    int time1 = tick;
    Serial.print("time to sort (ms): ");
    Serial.println(time1-time0);
    dumpTable();
    delay(10000); // 10 seconds
    sensorIx = 0;
  }
  delay(250); // ¼ second
}
