//Notice I am using Serial.begin and Serial.println alot,
//Thats because we have not yet connected any sensors and this is the 
//best way to see what's happening with our code 
#define no 6
int count;

void setup(){
    Serial.begin(9600);

}
void loop(){
    for(count=0;count<=no;count++){  // count must be initialized before we can start using it
        Serial.println(count);//You should see the count printed 6 times with increasing
        delay(1000);
    }
}
