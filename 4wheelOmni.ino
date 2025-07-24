#include <ps5Controller.h>
int FDir = 33, FSpeed = 32, RDir = 27, RSpeed = 26, LDir = 17, LSpeed = 16, BDir = 19 , BSpeed = 18;
//int FDir = 32, FSpeed = 33, RDir = 25, RSpeed = 26, LDir = 18, LSpeed = 19, BDir = 16 , BSpeed = 17;
//int FDir = 32, FSpeed = 33, RDir = 25, RSpeed = 26, LDir = 27, LSpeed = 13, BDir = 23 , BSpeed = 22;
float Lx, Rx, Ly, Ry;
int xyz;

// forward high
// backward low

void setup() {
  Serial.begin(115200);
  ps5.begin("88:03:4C:93:FE:13");

  pinMode(FDir, OUTPUT);
  pinMode(RDir, OUTPUT);
  pinMode(LDir, OUTPUT);
  pinMode(BDir, OUTPUT);
  delay(100);
  
}

void loop() {
readjs();

if(Ly <-30){
while(Ly <-30)
{
  xyz = ps5.R2Value();
  front(xyz);
  Serial.println(Ly);
  readjs();
}
}
else if(Ly > 30){
while(Ly > 30)
{
  xyz = ps5.R2Value();
  back(xyz);
  Serial.println(Ly);
  readjs();
}
}
//ya condition chi garaj nhi, last la stop karaycha
//else if(Lx==-1.00 && Ly==-1.00){
//while( Lx==-1.00 && Ly==-1.00)
//{
//  stop();
//  Serial.println(Ly,Lx);
//  readjs();
//}
//}
else if(Lx > 30){
while(Lx > 30)
{
  xyz = ps5.R2Value();
  right(xyz);
  Serial.println(Lx);
  readjs();
}
}
else if(Lx < -30){
while(Lx < -30)
{
  xyz = ps5.R2Value();
  left(xyz);
  Serial.println(Lx);
  readjs();
}
}
else if(Rx > 30){
while(Rx > 30)
{
  xyz = ps5.R2Value();
 clockwise(xyz);
 Serial.println(Rx);
 readjs();
}
}
else if(Rx < -30){
while(Rx < -30){
  xyz = ps5.R2Value();
  anticlockwise(xyz);
  Serial.println(Rx);
  readjs();  
}  
}
else
{
  stopr();
  Serial.print(Ly);
  Serial.print("   ");
  Serial.println(Lx);
  
}
}

///////////////////////Functions//////////////////////////
void front(int xyz){
  analogWrite(FSpeed, 0);
  analogWrite(RSpeed, xyz);
  analogWrite(LSpeed, xyz);
  analogWrite(BSpeed, 0);
  digitalWrite(RDir, HIGH);
  
  digitalWrite(LDir, HIGH);
  

}
void back(int xyz){
  analogWrite(FSpeed, 0);
  analogWrite(RSpeed, xyz);
  analogWrite(LSpeed, xyz);
  analogWrite(BSpeed, 0);
  digitalWrite(RDir, LOW);
  
  digitalWrite(LDir, LOW);
}

void stopr(){
  analogWrite(FSpeed, 0);
  analogWrite(RSpeed, 0);
  analogWrite(LSpeed, 0);
  analogWrite(BSpeed, 0);
  
}

void clockwise(int xyz){
  analogWrite(FSpeed, xyz);
  analogWrite(RSpeed, xyz);
  analogWrite(LSpeed, xyz);
  analogWrite(BSpeed, xyz);
  digitalWrite(RDir, LOW);
  digitalWrite(BDir, LOW);
  digitalWrite(LDir, HIGH);
  digitalWrite(FDir, HIGH);

}
void anticlockwise(int xyz){
  analogWrite(FSpeed, xyz);
  analogWrite(RSpeed, xyz);
  analogWrite(LSpeed, xyz);
  analogWrite(BSpeed, xyz);
  digitalWrite(RDir, HIGH);
  digitalWrite(BDir, HIGH);
  digitalWrite(LDir, LOW);
  digitalWrite(FDir, LOW);

}
void right(int xyz){
  analogWrite(FSpeed, xyz);
  analogWrite(RSpeed, 0);
  analogWrite(LSpeed, 0);
  analogWrite(BSpeed, xyz);
  digitalWrite(FDir, HIGH);
  
  digitalWrite(BDir, HIGH);

}
void left(int xyz){
  analogWrite(FSpeed, xyz);
  analogWrite(RSpeed, 0);
  analogWrite(LSpeed, 0);
  analogWrite(BSpeed, xyz);
  digitalWrite(FDir, LOW);
  
  digitalWrite(BDir, LOW);
}
void readjs()
{
 Lx = ps5.LStickX();
 Rx = ps5.RStickX();
 Ly = ps5.LStickY();
 Ry = ps5.RStickY();
}