#ifndef apio_included
#define apio_included
#include <Arduino.h>
#include <XBee.h>


struct output{
	int pin;
	int valore;
};
typedef struct output Output;

struct input{
	int pin;
	int valore;
};
typedef struct input Input;

int rit=0;
Output * onoff(Output * luce, String valore){
	
if(valore.toInt()==1){
                luce[0].valore=255;
digitalWrite(luce[0].pin,HIGH);
              } else {
                luce[0].valore=0;
digitalWrite(luce[0].pin,LOW);
              }

return luce;
}

Output * gioco(Output * luce, String valore){
	
if(valore.toInt()==1){
rit=100;
    analogWrite(luce[0].pin, luce[0].valore);
    delay(rit);
    analogWrite(luce[0].pin, 0);
    delay(rit);
} else if (valore.toInt()==2){
    rit=50;
    analogWrite(luce[0].pin, luce[0].valore);
    delay(rit);
    analogWrite(luce[0].pin, 0);
    delay(rit);
} else if (valore.toInt()==3){
    rit=30;
    analogWrite(luce[0].pin, luce[0].valore);
    delay(rit);
    analogWrite(luce[0].pin, 0);
    delay(rit);
} else if (valore.toInt()==0){
    rit=0;
    analogWrite(luce[0].pin,luce[0].valore);
}

return luce;
}

Output * intensita(Output * luce, String valore){
int intervallo = valore.toInt() - luce[0].valore;
float passo = intervallo / 100;
if ( intervallo > 0) {
    while (luce[0].valore<valore.toInt()){
        analogWrite(luce[0].pin, luce[0].valore);
        delay(10);
        luce[0].valore=luce[0].valore+passo;
    }
} else {
    while (luce[0].valore>valore.toInt()){
        analogWrite(luce[0].pin, luce[0].valore);
        delay(10);
        luce[0].valore=luce[0].valore+passo;
    }
}

return luce;
}


#endif
