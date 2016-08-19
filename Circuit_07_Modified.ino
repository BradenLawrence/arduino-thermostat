const int temperaturePin = 0;
const int dialPin = 1;
const int hotPin = 9;

float voltage, degreesC, degreesF;
int highestTemp, lowestTemp, prevTemp;

void setup()
{ 
  Serial.begin(9600);
  pinMode(hotPin, OUTPUT);

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;

  highestTemp = degreesF;
  lowestTemp = degreesF;
  prevTemp = degreesF;
}


void loop()
{
  int dialValue, lightValue;

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;
 
  //Serial.print("voltage: ");
  //Serial.print(voltage);
  //Serial.print("  deg C: ");
  //Serial.print(degreesC);
  //Serial.print("deg F: ");
  //Serial.println(degreesF);

 // if((degreesF > prevTemp*1.25)||(degreesF < prevTemp*0.75)){
    //The thermoresistor sometimes spikes in value, which can throw off our highestTemp.
    //This function ensures that the any given temperature reading cannot be more than 10% hotter or cooler than the last one.
    //degreesF = prevTemp;
 // } else {
    prevTemp = degreesF;
 // }

  if(degreesF > highestTemp){
    highestTemp = degreesF;
  } else if (degreesF < lowestTemp) {
    lowestTemp = degreesF;
  }

  dialValue = analogRead(dialPin);
  dialValue = map(dialValue, 0, 1023, lowestTemp, highestTemp);
  dialValue = constrain(dialValue, lowestTemp, highestTemp);

  if(dialValue < degreesF){
    lightValue = ((degreesF-dialValue)/(highestTemp - dialValue))*255;
    analogWrite(hotPin, lightValue);
  } else {
    analogWrite(hotPin, 0);
  }
  Serial.print("Temp: ");
  Serial.print(degreesF);
  Serial.print("  Low: ");
  Serial.print(lowestTemp);
  Serial.print("  Hi: ");
  Serial.print(highestTemp);
  Serial.print("  Dial value: ");
  Serial.println(dialValue);
  

  delay(500);

}


float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
  
}
