void setup(){
Serial.begin(115200);
}
void loop(){
    int a;
    a=45;
    while(a<56){
        Serial.println("The number is less than 56");//this is ideally an infinite loop
    }
}