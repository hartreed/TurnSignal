
const int xAxis = A0;
const int yAxis = A1;
const int zAxis = A2;
const int slp = A3;
const int light = A4;
const int tilt = A5;
const int rows [] = {13,12,11,10,9,8};
const int red = 4;
const int orange = 5;
const int green = 6;
const int dly = 140;
int ri=0;
int inc=1;
boolean tilted = false;
boolean dark = false;
float x;
float y;
float z;

void setup() {
  pinMode(tilt,INPUT);
  pinMode(light,INPUT);
  for (int i=0;i<6;i++)
  {
    pinMode(rows[i],OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  pinMode(xAxis,INPUT);
  pinMode(yAxis,INPUT);
  pinMode(zAxis,INPUT);
  pinMode(slp,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(orange,OUTPUT);
  pinMode(green,OUTPUT);
  digitalWrite(slp,HIGH);
  Serial.begin(9600);
}

void loop() {
  tilted = digitalRead(tilt)==LOW;
  dark = checkLight()>550;
  
  if(!tilted){
    accel();
  }else{
    setRows(LOW);
  }
  Serial.println(checkLight());
  //Serial.println(tilted);
  delay(dly);
}

void accel() {
  x = analogRead(xAxis);
  y = analogRead(yAxis);
  z = analogRead(zAxis);
  if(x>342){
    sweepLeft();
  }else if(x<328){
    sweepRight();
  }else{
    setRows(LOW);
  }
  //Serial.println(x);
  //Serial.println(y);
  //Serial.println(z);
}
int checkLight() {
  int lgt = analogRead(light);
  if(lgt>560){
    digitalWrite(green,HIGH);
    digitalWrite(orange,LOW);
    digitalWrite(red,LOW);
  }else if(lgt>550) {
    digitalWrite(green,LOW);
    digitalWrite(orange,HIGH);
    digitalWrite(red,LOW);
  }else{
    digitalWrite(green,LOW);
    digitalWrite(orange,LOW);
    digitalWrite(red,HIGH);
  }
  return lgt;
}
void sweepLeft() {
  ri = increment();//Increment row counter
  setRows(LOW);//Shut off all rows
  digitalWrite(rows[ri],HIGH);
}
void sweepRight() {
  ri = decrement();//decrement row counter
  setRows(LOW);//Shut off all rows
  digitalWrite(rows[ri],HIGH);
}
int increment() {
  ri++;
  if(ri>6||ri<3)
  {
    ri=3;
  }
  return ri;
}
int decrement() {
  ri--;
  if(ri<-1||ri>2)
  {
    ri=2;
  }
  return ri;
}
int sweep() {
  if(ri>6)
  {
    inc=-1;
  }else if(ri<0)
  {
    inc=1;
  }
  ri+=inc;
  return ri;
}

void setRows(int val) {
  //Shut everything down, or turn all rows on
  for (int i=0;i<6;i++)
  {
    digitalWrite(rows[i], val);
  }
}
