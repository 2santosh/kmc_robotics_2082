int led01=9;

int brightness=0;
int fadeValue=10;

void setup() {
  pinMode(led01, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  analogWrite(led01,brightness);
  brightness=brightness+fadeValue;

if(brightness<=0 || brightness>=255){
  fadeValue-fadeValue;
}
delay(40);
}
