void setup(){
    Serial.begin(9600);
}
void loop(){
    int number=10;
    do {
        Serial.println("The number is still big");
        number=number+1;
    }while(number<20);///Remeber our infinite loop? This solves the problem as the statement will 
    //become false at one point


//we add here a very long delay for us to see what's happening, otherwise the loop function will keep 
//repeating itself forever and ever -:)

    delay(5000);
}
