
#define LED_1 13
#define LED_2 12
#define LED_3 11
#define LED_4 10
#define PIN_POT A0

int active = 0;
int update = 1;
int pause = 1000;
int lastTime = 0;
int currPause = 0;

void updatePinStatus(int pin, int mode);
void check();

void setup() {
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  pinMode(LED_4,OUTPUT);

  digitalWrite(LED_1,HIGH);
}

void loop() {

  int value = analogRead(PIN_POT);

  pause = map(value, 0, 1023, 25 ,1) * 100;

  int currTime = millis();
  currPause = currPause + currTime - lastTime;
  lastTime = currTime;

  if( currPause >= pause && value >= 10){
    check();
    currPause = 0;
  }

}

void check(){
  updatePinStatus(active,LOW);
  active = active+update;
  if ( active >= 5){
    active = 3;
    update = -update;
  }
  if ( active <=0 ){
    active = 2;
    update = - update;
  }
  updatePinStatus(active,HIGH);
}

void updatePinStatus(int pin, int mode){
  switch (pin){
    case 1:
      digitalWrite(LED_1,mode);
      break;
    case 2:
      digitalWrite(LED_2,mode);
      break;
    case 3:
      digitalWrite(LED_3,mode);
      break;
    case 4: 
      digitalWrite(LED_4,mode);
      break;
    default :
     break;
  }
}
