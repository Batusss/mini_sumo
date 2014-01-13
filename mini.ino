#include <Servo.h>

Servo left;
Servo right;

#define MAX 1
#define VOLTS_PER_UNIT .0049F

int buton = 2;
int IRpinLeft = A5;
int IRpinRight= A4;
int IRcolorSJ=A0;
int IRcolorDJ=A1;
int IRcolorSS=A2;
int IRcolorDS=A3;
int a=0;
int SJ=1,DJ=2;
int StS=3,DS=4;

float voltsL,cmL,cm2L;
float voltsR,cmR,cm2R;
float voltsSJ,voltsDJ,voltsSS,voltsDS;
float cmSJ,cm2SJ,cmDJ,cm2DJ,cmSS,cm2SS,cmDS,cm2DS;

void setup()
{
  pinMode(buton, INPUT);
  
  Serial.begin(9600);
  
  left.attach(9);
  right.attach(10);
  left.write(90); 
  right.write(87);
}


void loop()
{
    //1 - SJ
    //2 - DJ
    //3 - SS
    //4 - DS
    int butonState = digitalRead(buton);
    if(butonState == HIGH)
    {
        
      if(a==0){delay(5000); a++;}
      
      float proxSensLeft = analogRead(IRpinLeft);
      float proxSensRight = analogRead(IRpinRight);
      float proxSensSJ = analogRead(IRcolorSJ);
      float proxSensDJ = analogRead(IRcolorDJ);
      float proxSensSS = analogRead(IRcolorSS);
      float proxSensDS = analogRead(IRcolorDS);
      
      voltsSJ = (float)proxSensSJ * VOLTS_PER_UNIT;
      voltsDJ = (float)proxSensDJ * VOLTS_PER_UNIT;
      voltsSS = (float)proxSensSS * VOLTS_PER_UNIT;
      voltsDS = (float)proxSensDS * VOLTS_PER_UNIT;
      voltsL = (float)proxSensLeft * VOLTS_PER_UNIT;
      voltsR = (float)proxSensRight * VOLTS_PER_UNIT;
      
      delay(200);
      
      cmL = 60.495 * pow(voltsL,-1.1904);
      cmR = 60.495 * pow(voltsR,-1.1904);
      cmSJ = 60.495 * pow(voltsSJ,-1.1904);
      cmDJ = 60.495 * pow(voltsDJ,-1.1904);
      cmSS = 60.495 * pow(voltsSS,-1.1904);
      cmDS = 60.495 * pow(voltsDS,-1.1904);
      
      
      if(CheckState(SJ) && CheckState(DJ) && CheckState(StS) && CheckState(DS)) {
          
            if(cmL<=77 && cmR <=77) {
                
                if( ( (int)cmL<cm2L-12 || cmL <= 25) || ((int)cmR<cm2R-12 || cmR <= 25) ) {
                        
                    walk('N',3);
                     
                }
                
                else {
                  
                    walk('R',90); 
                
                }
                   
                   cm2L = (int)cmL;
                   cm2R = (int)cmR;  
          
          }
            
          else {
              
              walk('R',90); 
          
          }
        
      }
      
      else {
         
           if(!CheckState(SJ)) {
             
             walk('N',30);
             walk('D',50);
           
           }
           
           if(!CheckState(DJ)) {
             
             walk('N',30);
             walk('L',50);
           
           }
           
           if(!CheckState(StS)) {
             
             walk('N',180);
             walk('Ed',50);
             delay(400);
           
           }
           
           if(!CheckState(DS)) {
             
             walk('N',170);
             walk('Es',50);
             delay(400);
           
           }
           
           if(!(CheckState(SJ)) && !(CheckState(DJ))) {
             
             walk('N',180);
             walk('Es',50);
             delay(400);
           
           }
           
           if(!(CheckState(StS)) && !(CheckState(DS))) {
             
             walk('N',10);
             walk('Es',50);
             delay(400);
           
           }
           
           if(!(CheckState(SJ)) && !(CheckState(StS))) {
             
             walk('D',80);
           
           }
           
           if(!(CheckState(DJ)) && !(CheckState(DS))) {
             
             walk('L',80);
           
           }
           
           if(!(CheckState(DJ)) && !(CheckState(SJ)) && !(CheckState(StS)) && !(CheckState(DS))) {
             
             left.write(87);
             right.write(90);
           
           }
     }
  }
  
  else {
     
     left.write(87); 
     right.write(89);
  
  }
  
}


void walk(char dir, int spd)
{
  
  if(dir == 'N') {
    
    left.write(spd);
    right.write(spd-3);
  
  }
  
  if(dir == 'L') {
    
    left.write(10+spd);
    right.write(50+spd);
  
  }
  
  if(dir == 'D') {
    
    left.write(50+spd);
    right.write(10+spd);
  
  }
  
  if(dir == 'R') {
    
    left.write(90-70);
    right.write(87-20);
    delay(1000);
    left.write(10);
    right.write(12);
    delay(700);
    left.write(120);
    right.write(172);
    delay(600);
   
  }
  
  if(dir == 'Es') {
    
    left.write(30+spd);
    right.write(50+spd);
  
  }
  
  if(dir == 'Ed') {
    
    left.write(30+spd);
    right.write(60+spd);
  
  }
  
}

int CheckState(char sensor)
{
    switch(sensor)
    {
      case 1:
      {
         if(cmSJ>15) return 0; 
         else return 1;
         break;
      }
      
      case 2:
      {
         if(cmDJ>15) return 0; 
         else return 1;
         break;
      }
      
      case 3:
      {
         if(cmSS>=20) return 0; 
         else return 1;
         break;
      }
      
      case 4:
      {
         if(cmDS>=20) return 0; 
         else return 1;
         break;
      }
      
      default:
      {
        return 0;
      }
    
    }
}
