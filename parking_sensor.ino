#include <LiquidCrystal.h> 

#define trigPinL 8        //Ultrasound modules wiring R=Right L=Left
#define echoPinL 9
#define trigPinR 6
#define echoPinR 7


long duration; 
int distance;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buzzer = 10; //buzzer to arduino pin 10

void setup() {
     pinMode(trigPinL, OUTPUT);       //Pinmodes of the HC-SR04 and starting the displays
     pinMode(echoPinL, INPUT);
     pinMode(trigPinR, OUTPUT);
     pinMode(echoPinR, INPUT); 
     Serial.begin(9600);
     lcd.begin(20, 4);
     lcd.print("parking sensor");
     pinMode(buzzer, OUTPUT); // Set buzzer - pin 10 as an output
     
}

void loop() {
    lcd.setCursor(0, 1);
    int distanceL = CDistance(trigPinL,echoPinL);      //Calculating all the distances by calling the function below
    int distanceR = CDistance(trigPinR,echoPinR);
    Serial.println("Left: ");
    Serial.println(distanceL);
    lcd.print("Left: ");
    lcd.print(distanceL);
    
    Serial.println("Right: ");
    Serial.println(distanceR);
    lcd.setCursor(20, 1);
    lcd.print("Right: ");
    lcd.print(distanceR);
    
      
    if(distanceR<10 || distanceL < 10){
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(1000);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec
    }
    

    delay(1000);
}

int CDistance(int a, int b){             //Calculating distance function, it takes two arguments (Trigger and Echo) and it executes the usual process of the HC-SR04
     digitalWrite(a, LOW); 
     delayMicroseconds(2);       
     digitalWrite(a, HIGH);
     delayMicroseconds(10);      
     digitalWrite(a, LOW); 
     duration = pulseIn(b, HIGH); 
     distance = duration*(0.034/2); 
     return distance;                  //Return the distance calculated
}

