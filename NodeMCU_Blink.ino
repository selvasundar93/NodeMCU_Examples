void setup() {
pinMode(D0,OUTPUT);
pinMode(D4,OUTPUT);
}

void loop() {
digitalWrite(D0,LOW);
digitalWrite(D4,HIGH);
delay(2000);
digitalWrite(D0,HIGH);
digitalWrite(D4,LOW);
delay(2000);
}
