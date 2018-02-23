


void triangle(int a, float b, float c){
    if (a==b && b==c){
        Serial.println("This is an equilateral triangle");
        delay(2000);
    }
    else if (a!=b && b!=c){
        Serial.println("This is a scalene triangle");
        delay(2000);
    }
    else{
        Serial.println("This is an isosceles triangle");
        delay(2000);
    }
}

void setup(){
    Serial.begin(9600);
}
void loop(){
triangle(34,34.1,34.1);

}

