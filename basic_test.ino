/* GP2Y1010AU0F Compact Optical Dust Sensor + Adapter  (GP2Y1010AU0F,DFR0280) [S065] : http://rdiot.tistory.com/114 [RDIoT Demo] */

int measurePin = A0;
int ledPower = 2;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
int B = 9; // OUTPUT PIN blue
int R = 11; // OUTPUT PIN red
int G = 10; // OUTPUT PIN green
 

void setup()
{
  lcd.init();  // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD2004");
  pinMode(ledPower,OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
 
  delay(1000);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("S065:Dust GP2Y1010AU0F");
 
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
  
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 5.0V mapped to 0 - 1023 integer values 
  calcVoltage = voMeasured * (5.0 / 1024); 
  
  dustDensity = (0.17 * calcVoltage - 0.1)*1000; 
  
  lcd.setCursor(0,1);
  lcd.print("Signal=" + (String)voMeasured + " ");
  
  lcd.setCursor(0,2);
  lcd.print("Voltage=" + (String)calcVoltage + " ");
  
  lcd.setCursor(0,3);
  lcd.print("Density=" + (String)dustDensity + "ug/m3 ");
  
  if(dustDensity <= 40)
  {
   // GREEN
   digitalWrite(R, HIGH);
   digitalWrite(G, LOW);
   
  }
  else if(dustDensity <= 80)
  {
   // BLUE
   digitalWrite(G, HIGH);
   digitalWrite(B, LOW);
 
  }
  else if(dustDensity <= 120)
  {
    // RED + GREEN = YELLOW
    digitalWrite(B, HIGH);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
  }
  else
  {
    // RED
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);   
  }
 
  delay(1000);
 
  // all off
  digitalWrite(B, HIGH);
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
}
