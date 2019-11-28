// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Motor revolution counter

// Define inputs
#define TS  4     // top sensor
#define MS  12    // middle sensor
#define BS  2     // bottom sensor

// Variables
int rev = 0;
int cond = false;
int T = 0;
int M = 0;
int B = 0;

void setup()
{
  pinMode(TS, INPUT);
  pinMode(MS, INPUT);
  pinMode(BS, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // Sensor readings 
  T = digitalRead(TS);
  M = digitalRead(MS);
  B = digitalRead(BS);

  if ( ( T == LOW ) && ( M == LOW ) && ( B == LOW ) ) 
  {
    cond = true;
  }

  // Condition to identify one revolution
  if ( ( cond == true ) && ( T == HIGH ) && ( M == HIGH ) && ( B == HIGH ) )
  {
    rev += 1;
    cond = false;  
    Serial.print("Nr. of revolutions: ");
    Serial.println(rev);
  }
}
