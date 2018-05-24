const byte analogPinF = 1;   // Connect AN output of LSA1 to analog pin 0
const byte junctionPulseF = 28; // Connect JPULSE of LSA1 to pin 28
const byte analogPinR = 2;   // Connect AN output of LSA2 to analog pin 1
const byte junctionPulseR = 29; // Connect JPULSE of LSA2 to pin 29
const byte analogPinL = 0;   // Connect AN output of LSA3 to analog pin 2
const byte junctionPulseL = 30; // Connect JPULSE of LSA3 to pin 30

int dirF =  12;              //Forward
int dirB = 4;
int pwmF = 13;
int pwmB = 5;
int dirR =  10; //RIGHT
int dirL = 6;
int pwmR = 11;
int pwmL = 3;


int readValueF, readValueR, readValueL, lsa_F, lsa_R, lsa_L; // Variables to store analog and line position value
unsigned int junctionCount = 0;   // Variable to store junction count value

void setup() {
  pinMode(junctionPulseF, INPUT);
  pinMode(junctionPulseR, INPUT);
  pinMode(junctionPulseL, INPUT);

  pinMode(dirR , OUTPUT);
  pinMode(pwmR , OUTPUT);
  pinMode(dirL , OUTPUT);
  pinMode(pwmL , OUTPUT);
  pinMode(dirF , OUTPUT);
  pinMode(pwmF , OUTPUT);
  pinMode(dirB , OUTPUT);
  pinMode(pwmB , OUTPUT);

  Serial.begin(9600);

  digitalWrite(dirF , LOW);
  digitalWrite(dirR , HIGH);
  digitalWrite(dirB , LOW);
  digitalWrite(dirL , HIGH);

  analogWrite(pwmF , 0);
  analogWrite(pwmR , 0);
  analogWrite(pwmB , 0);
  analogWrite(pwmL , 0);
  
  Serial.begin(9600);

  Serial.println("\nReading LSA values\n");
  Serial.println("LSA_F\tLSA_R\tLSA_L\tDirection");
  
  Forward();
  do {
    readValueF = analogRead(analogPinF);    // Read value from analog pin A0 (of LSA1)
  readValueR = analogRead(analogPinR);    // Read value from analog pin A1 (of LSA1)
  readValueL = analogRead(analogPinL);    // Read value from analog pin A2 (of LSA1)

  lsa_F = ((float)readValueF / 921) * 70; //forward
  lsa_R = ((float)readValueR / 921) * 70; //right
  lsa_L = ((float)readValueL / 921) * 70; //left
  } while (!hasLine(lsa_L));
  Serial.println("test");
  wait();
  rotate();
  Forward();
}

void loop() {
  /*readValueF = analogRead(analogPinF);    // Read value from analog pin A0 (of LSA1)
  readValueR = analogRead(analogPinR);    // Read value from analog pin A1 (of LSA1)
  readValueL = analogRead(analogPinL);    // Read value from analog pin A2 (of LSA1)

  lsa_F = ((float)readValueF / 921) * 70; //forward
  lsa_R = ((float)readValueR / 921) * 70; //right
  lsa_L = ((float)readValueL / 921) * 70; //left

  Serial.print(lsa_F + String("\t") + lsa_R + String("\t") + lsa_L + String("\t"));
  balanceLR();*/
}

void wait() {
  analogWrite(pwmR , 0);
  analogWrite(pwmL , 0);
  analogWrite(pwmF , 0);
  analogWrite(pwmB , 0);
}

void Forward() {
  digitalWrite(dirF , LOW);
  digitalWrite(dirB , LOW);
  analogWrite(pwmR , 0);
  analogWrite(pwmL , 0);
  analogWrite(pwmF , 150);
  analogWrite(pwmB , 150);

  //balanceFB();
}

void balanceFB() {
  if (hasLine(lsa_F) && lsa_F <= 18) { // nudge left
    digitalWrite(dirR , HIGH);
    analogWrite(pwmR , 100);
  } else if (hasLine(lsa_F) && lsa_F >= 53) { // nudge right
    digitalWrite(dirR , LOW);
    analogWrite(pwmR , 100);
  } else {
    analogWrite(pwmR, 0);
  }
}

void rotate() {
  readValueF = analogRead(analogPinF);    // Read value from analog pin A0 (of LSA1)
  readValueR = analogRead(analogPinR);    // Read value from analog pin A1 (of LSA1)
  readValueL = analogRead(analogPinL);    // Read value from analog pin A2 (of LSA1)

  lsa_F = ((float)readValueF / 921) * 70; //forward
  lsa_R = ((float)readValueR / 921) * 70; //right
  lsa_L = ((float)readValueL / 921) * 70; //left

   Serial.println("Before rot");
   digitalWrite(dirR,HIGH);
   digitalWrite(dirL,HIGH);
   digitalWrite(dirF,LOW);
   digitalWrite(dirB,HIGH);

   analogWrite(pwmR,100);
   analogWrite(pwmL,100);
   analogWrite(pwmF,100);
   analogWrite(pwmB,100);
Serial.println("After rot");
   
   while(!(hasLine(lsa_F) && hasLine(lsa_R))) {
    readValueF = analogRead(analogPinF);    // Read value from analog pin A0 (of LSA1)
    readValueR = analogRead(analogPinR);    // Read value from analog pin A1 (of LSA1)
    readValueL = analogRead(analogPinL);    // Read value from analog pin A2 (of LSA1)

    lsa_F = ((float)readValueF / 921) * 70; //forward
    lsa_R = ((float)readValueR / 921) * 70; //right
    lsa_L = ((float)readValueL / 921) * 70; //left
    Serial.println(lsa_F+String("\t")+lsa_R+String("\t")+lsa_L);
   }

   analogWrite(pwmR,0);
   analogWrite(pwmL,0);
   analogWrite(pwmF,0);
   analogWrite(pwmB,0);
}

inline boolean hasLine(int val) {
  return (val > 0) && (val < 70);
}
