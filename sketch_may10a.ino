int stp = 13;  // connect pin 13 to step
int dir = 12;  // connect pin 12 to dir
int sigpin = 1; // input from potentiometer

float Vin = 0.0;
float Vset = 1.7; // setpt voltage

int off = 0; // distance offset from voltage
int steps = 0; // number of steps per loop
int cycle = 0; // stepper delay (speed = 1/cycle)

void setup() 
{                
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(sigpin, INPUT);

  Serial.begin(9600);

}


void loop() 
{
// READ VOLTAGE
  Vin = analogRead(sigpin) * (5.0 / 1023.0);
  Serial.print("Vin: ");
  Serial.println(Vin);

// SET DIRECTION
  if (Vin < Vset) {
    digitalWrite(dir,LOW);
  }
  else {
    digitalWrite(dir,HIGH);
  }

// CALCULATE OFFSET (STEPS)
  off = abs(Vset-Vin)*100;
//  Serial.print("off: ");
//  Serial.println(off);

// DETERMINE SPEED FROM OFFSET
  if (off>50) {
    cycle = (250 + 37500 / off);                           
    }
   else {
    cycle = 1000;
    }

//  Serial.print("Cycle: ");
//  Serial.println(cycle);

// MOVE TO REDUCE OFFSET
  if (off>25) {
    steps = 10;
  }
  else {
    steps = 0;
  }
  
  for (int i=0; i<steps*5; i++)  
   {
      digitalWrite(stp, HIGH);   
      delayMicroseconds(cycle);               
      digitalWrite(stp, LOW);  
      delayMicroseconds(cycle);   
   }
}
