//Let's build a simple if conditional
int a =67;
int b = 78;
void setup(){
    Serial.begin(115200);
}
void loop(){
    if(b>a){
        Serial.println("b is more than a");
    }

    
    else{
        Serial.println("a is more than b");
    }
}
