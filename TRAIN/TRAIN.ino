// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: training stage

// Define inputs
#define PWM_PIN 3

// Variables
int count = 1;

void setup() { 
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT); 
}
void loop() {
  
  // TEST UPON THE ACTUATOR
  
  if (count <= 10) 
  {
    analogWrite(PWM_PIN, 225); //205
    delay(3000);
    Serial.println("out on phase");
    analogWrite(PWM_PIN, 0);
    delay(25000);
    Serial.print("completed cycle nr: ");
    Serial.println(count);
    count = count + 1;
  }
  else
  {
    analogWrite(PWM_PIN, 0);
    Serial.println("End of training"); 
    Serial.end();
  }
}
