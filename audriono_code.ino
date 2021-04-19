//== Led's ==
#define Rled 2
#define Yled 3
#define Gled 4
#define Rled2 5
#define Gled2 6
#define autoLight 11
//== Data Outputs ==
#define trigPin 9
#define buzzer 8
//== Data Inputs ==
#define echoPin 10
#define photocell A0
#define door 7
//== Software Var's ==
#define delaytime 100 

void setup() {
Serial.begin(9600); 
Serial.println("CEIS101 Course Project Module Final Project");
Serial.println("Name: Matthew Cote");

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Rled, OUTPUT);
pinMode(Yled, OUTPUT);
pinMode(Gled, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(autoLight, OUTPUT); 
pinMode(door, INPUT_PULLUP);  
pinMode(Rled2, OUTPUT);
pinMode(Gled2, OUTPUT);
}

void loop() {
//=== Automated Light === 
int value=analogRead(photocell); // Read the value from the light sensor to determine condition  

//=== Door Sensor Int ===
int value2=digitalRead(door); 

//Serial.println(value); //uncomment this line and open serial plotter to see the effect of light intensity on the sensor

if (value > 450) {  
 digitalWrite(autoLight, HIGH); 
 Serial.println("The automated light is ON");
} 
else { 
digitalWrite(autoLight, LOW); 
}  
//=== Door Sensor ===
if(value2 == 0) {// Door closed, no security threat
digitalWrite(Rled2, LOW);  
digitalWrite(Gled2, HIGH);
} 
else{ // Door open, security threat
Serial.println("Door is open. Security Alert! ");
digitalWrite(Rled2, HIGH);  
digitalWrite(Gled2, LOW); 
delay(delaytime); 
digitalWrite(Rled2, LOW);  
delay(delaytime);   
}  // end of else 
//==== Distance Sensor === 
long duration, distance, inches;

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Read the echo signal
duration = pulseIn(echoPin, HIGH); // Read duration for roundtrip distance
distance = (duration /2) * 0.0135 ; // Convert duration to one way distance in units of inches

if (distance <= 12) {  // Outer IF statement units of inches
  if (distance <=6){   // Alert range condition
    Serial.println("Alert! Possible Intruder."); 
    digitalWrite(Rled, HIGH); // Alert green LED on
    digitalWrite(Yled, LOW);
    digitalWrite(Gled, LOW);
    } 
  if (distance <12 and distance > 6){  // Warning range condition
  digitalWrite(Rled, LOW);
  digitalWrite(Yled, HIGH);  // Warning yellow LED on
  digitalWrite(Gled, LOW);
  }  

//==================== Beeping Rate Code Start ======
digitalWrite(buzzer,HIGH);
for (int i= distance; i>0; i--)
delay(10);

digitalWrite(buzzer,LOW);
for (int i= distance; i>0; i--)
delay(10);
//==================== Beeping Rate Code End =======
}
 else{ //Safe range condition 
  digitalWrite(Rled, LOW);
  digitalWrite(Yled, LOW);
  digitalWrite(Gled, HIGH);  // Safe distance green LED on
  digitalWrite(buzzer, LOW);
}// end of outer IF statement

delay(100); //pause program to stabilize ultrasonic sensor readings

Serial.println(value2); 
Serial.println(distance);
} //end of loop
