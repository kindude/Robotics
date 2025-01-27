#include "VarSpeedServo.h"  //include the VarSpeedServo library
#include "NewPing.h"        //include the NewPing library
#include <SoftwareSerial.h>
SoftwareSerial hcSerial(12,13); // RX, TX
VarSpeedServo RU;  //Right Upper
VarSpeedServo RL;  //Right Lower
VarSpeedServo LU;  //Left Upper
VarSpeedServo LL;  //Left Lower

NewPing sonar(3,2,200); 
const int vel = 100, vel_Back = 50;               
const int delay_Forward = 750, delay_Back = 1000;    
int vel_Dance1 = 50,    vel_Dance2 = 55,    vel_Dance3 = 60;     
int delay_Dance1 = 300, delay_Dance2 = 750, delay_Dance3 = 200;  

int vel_Dance4 = 70,    vel_Dance5 = 70,    vel_Dance6 = 100;
int delay_Dance4 = 400, delay_Dance5 = 400, delay_Dance6 = 500;
                                                     
const int array_cal[4] = {50,60,115,75}; 
int RU_Degree = 0,LU_Degree = array_cal[2]; //LU_Degree = array_cal[2] + 5;

const int num1 = 6;
const int array_forward[num1][4] =  
{
   {0,-40,0,-20},        
    {30,-40,30,-20},
    {30,0,20,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
    
};

const int num2 = 5; //5 
const int array_turn[num2][4] =  
{     
    {-40,0,-20,0},
    {-40,30,-20,30},      
    {0,30,0,30},
    {30,0,30,0},
    {0,0,0,0},
};
const int array_turn_left[num2][4] =  
{     
    {-40,0,-20,0},
    {-40,30,-20,30},      
    {0,30,0,30},
    {30,0,30,0},
    {0,0,0,0},
};

const int array_turn_right[num2][4] =  
{     
     {-20,0,-40,0},
    {-40,30,-40,30},      
    {0,30,0,30},
    {30,0,30,0},
    {0,0,0,0},
};

const int num_dance1 = 10;
const int array_dance1[num_dance1][4] =
{ 
//slide to the left 0-4
    {0,-20,0,0},  
    {0,-40,0,20},
    {0,-20,0,40},
    {0,0,0,20},
    {0,0,0,0},
    
//slide to the right 5-9
    {0,0,0,20},  
    {0,-20,0,40},
    {0,-40,0,20},
    {0,-20,0,0},
    {0,0,0,0}, 
};

const int num_dance2 = 32;
const int array_dance2[num_dance2][4] =
{ 
//left foot support 0-15
    {20,0,40,0},
    {20,-30,40,-30}, 
    {20,-30,10,-30},
    {20,-30,40,-30}, 
    {20,-30,10,-30},

    {20,-30,40,-30}, 
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-80,40,-30},        
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-30,40,-30},    
    {20,0,40,0},
    {0,0,0,0}, 
     
//right foot support 16-31
    {-40,0,-20,0},
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 

    {-40,40,-20,30}, 
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,80},        
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,30},    
    {-40,0,-20,0},
    {0,0,0,0},
};

const int num_dance3 = 8;        //split step
const int array_dance3[num_dance3][4] =
{ 
    {0,-40,0,0},
    {20,-30,20,20},
    {40,0,40,30},   
    {0,0,0,40},
    {-20,-20,-20,30},
    {-40,-30,-40,0},

    {0,-40,0,0},
    {0,0,0,0},
};

const int num_dance4 = 20;      //in place somersault inwards and accelerate angles
const int array_dance4[num_dance4][4] =
{     
    {0,-20,0,20},   
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},
    
    {0,-40,0,40},
    {0,-50,0,50},
    {0,-60,0,60},
    {0,0,0,0,},
};

const int num_dance5 = 17;
const int array_dance5[num_dance5][4] =
{ 
    {35,0,15,0},    //let both legs touch together
    {35,30,15,30},   
    {-35,30,15,30},   
    {-20,0,15,0},
    {0,0,0,0},

    {0,-40,0,40},    //somersault inwards and rotate legs
    {-30,-40,-20,40},
    {0,-40,0,40},
    {20,-40,30,40},    

    
    {0,-40,0,40},    //going up and down in place and rotate legs
    {20,-40,-20,40},   
    {20,-20,-20,20},
    {20,0,-20,0},   
    {-20,-10,20,10},
    {-10,-30,10,30},

    {0,-40,0,40},
    {0,0,0,0},
};

const int num_dance6 = 32;      
const int array_dance6[num_dance6][4] =
{   
    {0,-40,0,-20},        //go ahead- toe out
    {25,-40,18,-20},
    {25,0,18,0},
    {0,20,0,40},
    {-18,20,-25,40},
    {-18,0,-25,0},
      
    {0,-40,0,-20},        //toe out-piaffe
    {25,-40,18,-20},
    {0,0,0,0},
    {0,20,0,40},
    {-18,20,-25,40},
    {0,0,0,0},

    {0,-40,0,-20},        //toe out-retreat
    {-25,-40,-18,-20},
    {-25,0,-18,0},
    {0,20,0,40},
    {18,20,25,40},
    {18,0,25,0},

    {0,-40,0,-20},        //go ahead
    {30,-40,30,-20},
    {30,0,30,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
  
    {0,-40,0,-20},        //retreat
    {-30,-40,-30,-20},
    {-30,0,-30,0},
    {0,20,0,40},
    {30,20,30,40},
    {30,0,30,0},

    {15,0,15,0},
    {0,0,0,0},
};

//#define CALIBRATION
#define RUN
void Servo_Init()
{
    RU.attach(8);   // Connect the signal wire of the upper-right servo to pin 9 
    RL.attach(9);   // Connect the signal wire of the lower-right servo to pin 10 
    LU.attach(10);   // Connect the signal wire of the upper-left  servo to pin 11 
    LL.attach(11);   // Connect the signal wire of the lower-left  servo to pin 12 
}

void Adjust()                            // Avoid the servo's fast spinning in initialization 
{                                        // RU,LU goes from array_cal[0] - 5 ,array_cal[2] + 5 degrees to array_cal[0],array_cal[2] degrees
    for(RU_Degree = array_cal[0] - 5; RU_Degree <= array_cal[0]; RU_Degree += 1) {
        RU.write(RU_Degree);             // in steps of 1 degree
        LU.write(LU_Degree--);           // tell servo to go to RU_Degreeition, LU_Degreeition in variable 'RU_Degree', 'LU_Degree'         
        delay(15);                       // waits 15ms for the servo to reach the RU_Degreeition
    }
}

bool TooClose()
{
    int tooclose = 0;
    for(int a=0; a<5; a++) {  
        delay(50);
        int din = sonar.ping_in();
        if (din < 7 && din > 0) tooclose++;
    }
    if (tooclose < 5) return 1;   
    return 0;
}

void Forward()
{
    for(int x=0; x<num1; x++) {                    
        RU.slowmove (array_cal[0] + array_forward[x][0] , vel);    
        RL.slowmove (array_cal[1] + array_forward[x][1] , vel);
        LU.slowmove (array_cal[2] + array_forward[x][2] , vel);
        LL.slowmove (array_cal[3] + array_forward[x][3] , vel);
        delay(delay_Forward);
    }
}
void Manual_Forward(){
    
    for(int x=0; x<num1; x++) {                    
        RU.slowmove (array_cal[0] + array_forward[x][0] , vel);    
        RL.slowmove (array_cal[1] + array_forward[x][1] , vel);
        LU.slowmove (array_cal[2] + array_forward[x][2] , vel);
        LL.slowmove (array_cal[3] + array_forward[x][3] , vel);
     
        delay(delay_Forward);
    }
      RU.slowmove (array_cal[0]  , vel_Dance6);   
        RL.slowmove (array_cal[1]  , vel_Dance6);
        LU.slowmove (array_cal[2]  , vel_Dance6);
        LL.slowmove (array_cal[3]  , vel_Dance6);
    
}

void Manual_Right()
{
for(int z=0; z<5; z++) {    
        for(int y=0; y<num2; y++) {                  
            RU.slowmove (array_cal[0] - array_turn_right[y][0] , vel_Back);   
            RL.slowmove (array_cal[1] - array_turn_right[y][1] , vel_Back);
            LU.slowmove (array_cal[2] - array_turn_right[y][2] , vel_Back);
            LL.slowmove (array_cal[3] - array_turn_right[y][3] , vel_Back);
            delay(delay_Back); 
        }
    }
}

void Backward()
{
    for(int z=0; z<4; z++) {    
        for(int y=0; y<num2; y++) {                  
            RU.slowmove (array_cal[0] + array_turn[y][0] , vel_Back);   
            RL.slowmove (array_cal[1] + array_turn[y][1] , vel_Back);
            LU.slowmove (array_cal[2] + array_turn[y][2] , vel_Back);
            LL.slowmove (array_cal[3] + array_turn[y][3] , vel_Back);
            delay(delay_Back); 
        }
    }
}

void Manual_Backward(){
  const int array_cal_0 = array_cal[0] + 10 , array_cal_2 = array_cal[2] - 10;
        for(int z=12; z<18; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 

            RU.slowmove (array_cal[0]  , vel_Dance6);   
            RL.slowmove (array_cal[1]  , vel_Dance6);
            LU.slowmove (array_cal[2]  , vel_Dance6);
            LL.slowmove (array_cal[3]  , vel_Dance6);
}

void Manual_Left(){
  for(int z=0; z<5; z++) {    
        for(int y=0; y<num2; y++) {                  
            RU.slowmove (array_cal[0] + array_turn_left[y][0] , vel_Back);   
            RL.slowmove (array_cal[1] + array_turn_left[y][1] , vel_Back);
            LU.slowmove (array_cal[2] + array_turn_left[y][2] , vel_Back);
            LL.slowmove (array_cal[3] + array_turn_left[y][3] , vel_Back);
            delay(delay_Back); 
        }
    }
}

void Slide_2_Left(int times)
{
    for(int time1 = 0; time1 < times; time1++) { 
        for(int z=0; z<5; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        } 
    }
}

void Slide_2_Right(int times)
{
    for(int time1 = 0; time1 < times; time1++) {
        for(int z=5; z<10; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        }   
    }
}

void Left_Foot_Support()
{
    for(int z=0; z<16; z++) { //z<12
        if ( z > 5 && z < 14) {   //z(1,10)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Right_Foot_Support()
{
    for(int z=16; z<32; z++) { //z<24
        if ( z > 21 && z < 30) {   //z(13,22)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Dancing1_2()
{
    Slide_2_Left(2);
    Left_Foot_Support();
    
    Slide_2_Right(2);
    Right_Foot_Support();
}

void Dancing3(int Times = 1, int Vel = 40, int Delay = 250, int low = 0, int high = 0)
{   
    for(int time3 = 0; time3 < Times; time3++) {
        for(int z=0; z<6; z++) {
            if ( time3 > 1 && time3 < 4) {
            vel_Dance3 = Vel;
            delay_Dance3 = Delay;
            }
            else { 
            vel_Dance3 = 40; 
            delay_Dance3 = 200;
            }                     
            
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        } 
    }
    for(int z=6; z<8; z++) {                     
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        }       
}

void Dancing4()
{  
    for(int z=0; z<num_dance4; z++) {
        if ( z > 17) {
            vel_Dance4 = 10;
            delay_Dance4 = 1500;
            }
        else {
            vel_Dance4 = 40;
            delay_Dance4 = 400;
            }
                 
        RU.slowmove (array_cal[0] + array_dance4[z][0] , vel_Dance4);   
        RL.slowmove (array_cal[1] + array_dance4[z][1] , vel_Dance4);
        LU.slowmove (array_cal[2] + array_dance4[z][2] , vel_Dance4);
        LL.slowmove (array_cal[3] + array_dance4[z][3] , vel_Dance4);
        delay(delay_Dance4); 
    } 
}

void Dancing5()
{   
    for(int x = 0; x < 3; x++) {
        for(int z=0; z<5; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , vel_Dance5);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , vel_Dance5);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , vel_Dance5);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , vel_Dance5);
            delay(delay_Dance5); 
        } 
    }
   
    for(int x = 0; x < 2; x++) {
        for(int z=5; z<9; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 30);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 30);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 30);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 30);
            delay(550); 
        } 
    }
    
    for(int x = 0; x < 3; x++) {
        for(int z=9; z<15; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , vel_Dance5);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , vel_Dance5);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , vel_Dance5);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , vel_Dance5);
            delay(300); 
        } 
    }    
    for(int z=15; z<17; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 10);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 10);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 10);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 10);
            delay(1500); 
        }   
}

void Dancing6()
{   
    const int array_cal_0 = array_cal[0] + 10 , array_cal_2 = array_cal[2] - 10;
    
    for(int x = 0; x < 3; x++) {
        for(int z=0; z<6; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }
   
    for(int x = 0; x < 3; x++) {
        for(int z=6; z<12; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , 40);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , 40);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , 40);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , 40);
            delay(400); 
        } 
    }
    
    for(int x = 0; x < 3; x++) {
        for(int z=12; z<18; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }  
    for(int x = 0; x < 3; x++) {
        for(int z=18; z<24; z++) {                     
            RU.slowmove (array_cal[0] + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal[2] + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }

    for(int x = 0; x < 3; x++) {
        for(int z=24; z<30; z++) {                     
            RU.slowmove (array_cal[0] + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal[2] + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }
    for(int z=30; z<32; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 10);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 10);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 10);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 10);
            delay(1500); 
        }     
}

void setup()  
{
#ifdef CALIBRATION 
    Servo_Init();  
    Adjust();
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
    while(1);
#endif

#ifdef RUN 
    Serial.begin(9600); // hardware serial for the USB-PC
    hcSerial.begin(9600);  // software serial Arduino to HC-06 (9600 is default)
    Servo_Init();
    Adjust(); 
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
#endif
}

void loop() 
{ 
    if (hcSerial.available()) {
    while(hcSerial.available()) { // While there is more to be read, keep reading.
      char readedSymbol = (char)hcSerial.read();
      Serial.print(readedSymbol);
      switch(readedSymbol) {
        case '0':
        Manual_Backward();
        break;
        case '1':
          Manual_Forward();
        break;
    
        case '2':     //left
          Manual_Left();
        break;
        case '3':     //right
         Manual_Right();
        break;
        case '4':     //dancing
        Dancing1_2();
        delay(500);    
        Dancing3(5,20,400);
        delay(500);    
        Dancing4();
        delay(500);    
        Dancing5();
        delay(500);    
        Dancing6();
        break;
        case '5':
        while(1){
        while(TooClose())
        {
          Forward();    
          if((char)hcSerial.read() == '6') return;
        }
        Backward(); 
        if((char)hcSerial.read() == '6') return;
        }
       Break;
       }
    }
  }
}