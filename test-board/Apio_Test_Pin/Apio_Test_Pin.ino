/* 
Title: Apio Test Pin
 created 2014
 by Ulisse Ruiz <http://www.ruiztech.com>
 modified 29 Dec 2014
 by Alessandro Chelli <http://www.apio.cc>
*/


byte time = 50;
void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
 for(int out = -1; out < 22; out++){
digitalWrite(out, LOW);
delay(time);
}
 delay(2500);

}

// the loop function runs over and over again forever
void loop() {
for(int out = -1; out < 22; out++){
digitalWrite(out, HIGH);
delay(time);
}

delay(2000);

for(int out = -1; out < 22; out++){
digitalWrite(out, LOW);
delay(time);
}

delay(time);




}


