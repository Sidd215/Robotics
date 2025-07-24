#include <ps5Controller.h>

int FMpwm=16,FMdir=4;//LMpwm=23,LMdir=22,RMpwm=19,RMdir=21;
int pulsecount=0,interval = 2000;
const int a = 34;
long current = 0,previous = 0;
int ppr = 18062,setpoint = 120;
double z = 180,error,Kp,Ki,Kd,P,I=0;
double dt, last_time;
double rpm;

float ly=ps5.LStickY();


void setup() {
  Serial.begin(115200);
  ps5.begin("88:03:4C:93:FE:13"); //replace with MAC address of your controller
  
 
    while (ps5.isConnected()==0) {
    Serial.println("Connecting...");
    }
  Serial.println("Ready.");
  pinMode(a,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(a),pulsecounter,CHANGE);
  pinMode(FMpwm,OUTPUT);

  pinMode(FMdir,OUTPUT);
      delay(1000);

  }

  
// float mapp(float control){
//   float z;
//   if((-128<=control)&&(control<=-30))
//   {
//     z=map(control,-30,-128,0,225);
//   }
//   else if((30<=control)&&(control<=128))
//   {
//     z=map(control,30,128,0,225);
//   }
//   else
//   z =0;
//   return z;
// }
 
  void forward(){

    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,z);
    delay(150);

    // Serial.println("IAM IN FORWARD");
    
 
  }

 void back(){
    digitalWrite(FMdir,HIGH);
    analogWrite(FMpwm,z);
        delay(150);
    //digitalWrite(LMdir,LOW);
    //analogWrite(LMpwm,z);
    //digitalWrite(RMdir,HIGH);
    //analogWrite(RMpwm,z);
    // Serial.println("IAM IN BACK");
    
  }
  

void stop(){
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,0);
    delay(150);
    //Serial.println("IAM IN STOP");


}

void pidcontrol()
{

  error = setpoint -rpm;

  Kp =10; 
  Ki = 0.0; 
  P = Kp*error;
  I = Ki*(I+error*dt);
  double G = P+I;
  if(G>0){
  z =(int)z+fabs(G);}
  if(G<0)
  {
    z =(int)z-fabs(G); 
  }
  if(z>180)
  {
    z = 180;
  }
        Serial.println(z);
      Serial.print(',');
}

void loop() {
    double now = millis();
  dt = (now - last_time)/1000.00;
  last_time = now;
  current = millis();
    //   Serial.println(setpoint);
    // Serial.print(',');
    //     Serial.println(rpm);
   //      Serial.println(error);
   
   if(current-previous>500)
   {
        // Serial.println(Kp);
      //Serial.print(',');
     Serial.println(setpoint);
      Serial.print(',');
    rpm = ((pulsecount*60*2)/ppr);
    Serial.println(rpm);
    // Serial.println(z);
    pulsecount = 0;
    previous = current;
   }
  //pidcontrol();
  
if (ps5.Square()){
    
    forward();
    pidcontrol();
   
 
  } 
  if (ps5.Cross()) {

    back();
    pidcontrol();

   
  }
  if(ps5.Circle()) {
    stop();
  }
  
  
}

void pulsecounter(){
  pulsecount++;

}