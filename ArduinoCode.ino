int blue[3] = {9, 10, 11};
int red[3] = {6, 5, 3};

int curTemp, newTemp;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 3; i++){
    pinMode(blue[i], OUTPUT);
    pinMode(red[i], OUTPUT);
  }

  curTemp = 0;
  newTemp = 0;

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  String input;
  while (Serial.readString()){
    input = Serial.readString();
    float temp = input.toFloat();
    Serial.println(input);

    if(input != ""){
      newTemp = temp;
      if(newTemp != curTemp){
        resetLED();
      
        if(temp <= 65){
          analogWrite(blue[0], min(255,tempLimit(65, temp)));
          if(temp <= 50){
            analogWrite(blue[1], min(255,tempLimit(50, temp)));
            if(temp <= 35)
              analogWrite(blue[2], min(255,tempLimit(35, temp)));
          }
        }
        if(temp >= 65){
          analogWrite(red[0], min(255,tempLimit(65, temp)));
          if(temp >= 80){
            analogWrite(red[1], min(255,tempLimit(80, temp)));
            if(temp >= 95)
              analogWrite(red[2], min(255,tempLimit(95, temp)));
          }
        }
        curTemp = newTemp;
      }
    }
  }
}

int tempLimit(int max, int temp){
  float output = abs(max - temp);
  output = output / 15;
  output *= 255;
  return output + 1;
}

void resetLED()
{
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(blue[i], 0);
      digitalWrite(red[i], 0);
    }
}
