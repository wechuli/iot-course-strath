void fun(void){
    Serial.println("Would you look at me, I was declared before the setup() function, and am not even returning anything");

    delay(3000);
}

void setup(){
    Serial.begin(9600);
}
void loop(){
int holder;
holder=result(3,1,0);
fun();
}

int result(int a, int b, int c){
    int c;
    c=a+b+c;
    return c;
}