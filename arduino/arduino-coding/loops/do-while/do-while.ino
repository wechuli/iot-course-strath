void setup(){
    Serial.begin(9600);
}
void loop(){
    float number 45.6;
    do {
        Serial.println("The number is still big");
        number=number-10;
    }
    while(number<50);///Remeber our infinite loop? This solves the problem as the statement will become false at one point
}