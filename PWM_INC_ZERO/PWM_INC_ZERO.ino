// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Continuous PWM increments, followed by return to 0 PWM

// Define inputs
#define PWM_PIN 3
#define INPUT_PIN A0    // Analog input pin
#define R_NTC 100000    // NTC resistance 25 ºC
#define B 3950          // Beta constant
#define VCC 5           // Supply voltage
#define R 1660          // Voltage divider resistance
#define NR_SAMPLES 5    // Number of samples

//Variables
float R_NTC_NOW, V_R, ln, T_NTC, T0, V_NTC, AV_Samples;
int Samples[NR_SAMPLES], i;
long k=1.0, p=1.0, on_time = 300000, off_time = 420000;
float j=1, pwm_value = 0;
unsigned long curr_t;

void setup() { 
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT); 
  T0 = 25 + 273.15;   //Temperature T0 in kelvin
}
void loop() {

  curr_t = millis();   
  Serial.print(curr_t);
  Serial.print("\t"); 
  
  // TEST UPON THE ACTUATOR
  
  if (curr_t<= on_time*k + off_time*(k-1.0))
  {
    pwm_value =  50*(j); 
  }
  else
  { 
    pwm_value = 0;
    if (curr_t>= on_time*k + off_time*k)
    {
      k += 1.0;  
      j += 1;
    }
  }
  analogWrite(PWM_PIN, pwm_value);
  Serial.print(pwm_value);
  Serial.print("\t");
  
  if (curr_t>= on_time*5 + off_time*5)
  {
    Serial.end();
    Serial.println("END"); 
  }
     
  TEMP_ACQ(); 
}

  // TEMPERATURE ACQUISITION

void TEMP_ACQ(){
  // acquire 5 samples
  for (i=0; i< NR_SAMPLES; i++) 
  {
   Samples[i] = analogRead(INPUT_PIN);    // Acquisition analog value of NTC voltage
   delay(10);
  }

  // average of the samples
  AV_Samples = 0;
  for (i=0; i< NR_SAMPLES; i++) 
  {
     AV_Samples += Samples[i];
  }
  AV_Samples /= NR_SAMPLES;               // Average of the acquired value
         
  V_NTC = (5.00 * AV_Samples) / 1023.00;  // Conversion to voltage 
  V_R = VCC - V_NTC;                      // Voltage in resistance
  R_NTC_NOW = V_NTC / (V_R / R);          // Current resistance of NTC

  ln = log(R_NTC_NOW / R_NTC);
  T_NTC = (1 / ((ln / B) + (1 / T0)));    //Temperature from NTC in Kelvin
  T_NTC = T_NTC - 273.15;                 //Conversion to Celsius

  Serial.println(T_NTC);
}
