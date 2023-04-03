
#define enA 10 //H_bridge Pins
#define in1 6  //H_bridge Pins
#define in2 7  //H_bridge Pins
#define in3 8  //H_bridge Pins
#define in4 9  //H_bridge Pins
#define enB 11 //H_bridge Pins

#define R_S A2 //IR Sensor pins
#define M_S A1 //IR Sensor pins
#define L_S A0 //IR Sensor pins

#define trig 3 //ultrasonic pins
#define echo 2 //ultrasonic pins

float duration, distance; //for ultrasonic distance calculation

void setup() {
  pinMode(R_S, INPUT);
  pinMode(M_S, INPUT);
  pinMode(L_S, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, 200); //speed range 0 - 255
  analogWrite(enB, 200); //speed range 0 - 255

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  delay(1200);
}

void loop() 
{
 

  ultrasonic();

  if (distance <= 15) 
        
	Stop();
  
  else 
	  
    IR_Read();
  

}


/********Functions********/

void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0342 / 2;  //distance cm
  delay(10);
}

void IR_Read() {

  int Left = digitalRead(L_S);
  int Middle = digitalRead(M_S);
  int Right = digitalRead(R_S);

  if ((Right == 1) && (Middle == 0) && (Left == 1)) { forward(); } //right & left on ground & middle on black go forward   

  if ((Right == 0) && (Middle == 0) && (Left == 1)) { turnRight(); } //right & middle on black  & left on ground go turnRight

  if ((Right == 0) && (Middle == 1) && (Left == 1)) { turnRight(); } //right on black & middle & left on ground go turnRight

  if ((Right == 1) && (Middle == 0) && (Left == 0)) { turnLeft(); } //right on ground & left & middle on black go turnLeft

  if ((Right == 1) && (Middle == 1) && (Left == 0)) { turnLeft(); } //right & middle on ground & left on black go turnLeft

  if ((Right == 0) && (Middle == 0) && (Left == 0)) { Stop(); } //3 sensors on black car stop
}

void forward() {
  digitalWrite(in1, HIGH);  //Right Motor forward Pin
  digitalWrite(in2, LOW);   //Right Motor backward Pin
  digitalWrite(in3, HIGH);  //Left Motor forward Pin
  digitalWrite(in4, LOW);   //Left Motor backward Pin
}

void Backward() {
  digitalWrite(in1, LOW);   //Right Motor forward Pin
  digitalWrite(in2, HIGH);  //Right Motor backward Pin
  digitalWrite(in3, LOW);   //Left Motor forward Pin
  digitalWrite(in4, HIGH);  //Left Motor backward Pin
}

void turnRight() {
  digitalWrite(in1, LOW);   //Right Motor forward Pin
  digitalWrite(in2, LOW);   //Right Motor backward Pin
  digitalWrite(in3, HIGH);  //Left Motor forward Pin
  digitalWrite(in4, LOW);   //Left Motor backward Pin
}

void turnLeft() {
  digitalWrite(in1, HIGH);  //Right Motor forward Pin
  digitalWrite(in2, LOW);   //Right Motor backward Pin
  digitalWrite(in3, LOW);   //Left Motor forward Pin
  digitalWrite(in4, LOW);   //Left Motor backward Pin
}

void Stop() {
  digitalWrite(in1, LOW);  //Right Motor forward Pin
  digitalWrite(in2, LOW);  //Right Motor backward Pin
  digitalWrite(in3, LOW);  //Left Motor forward Pin
  digitalWrite(in4, LOW);  //Left Motor backward Pin
}


