//This is the example exercise I left in class, I have two LED,s, green and white so I'll use those

//lets start by defining our constants

#define red_led 9
#define green_led 10

void setup(){
    Serial.begin(115200);
    pinMode(red_led,OUTPUT);
    pinMode(green_led,OUTPUT);
}
void loop(){
    float a=450;
    float b=450;
    if(a>b){
        red_on();
        green_off();
    }
    else if(a<b){
        green_on();
        red_off();

    }
    else{
        red_on();
        red_off();
        green_on();
        green_off();
    }

}
void red_on(){
    digitalWrite(red_led,HIGH);
    delay(2000);

}
void red_off(){
   digitalWrite(red_led,LOW);
    delay(1000); 
}
void green_on(){
    digitalWrite(green_led,HIGH);
    delay(2000);

}
void green_off(){
   digitalWrite(green_led,LOW);
    delay(1000); 
}
