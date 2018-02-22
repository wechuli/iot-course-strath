int T , S ;
float c = 0 ; //Global variable declaration

void setup () {
Serial.begin(115200);
}

void loop () {
   int x , y ;
   int z ; //Local variable declaration
   x = 0;
   y = 0; //actual initialization
   z = 10;
   Serial.println(x,y,z);
   delay(2000);
}