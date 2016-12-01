//============================C博士===========================
//  智能小车黑线循迹
//============================================================

int Left_motor_go=9;             // 左电机前进(IN1)
int Left_motor_back=5;           // 左电机后退(IN2)
int Right_motor_go=10;           // 右电机前进(IN3)
int Right_motor_back=11;         // 右电机后退(IN4)

const int SensorRight = 3;   	   // 右循迹红外传感器(P3.2 OUT1)
const int SensorLeft = 4;        // 左循迹红外传感器(P3.3 OUT2)

int SL;                          // 左循迹红外传感器状态
int SR;                          // 右循迹红外传感器状态

void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go,OUTPUT);     // PIN 5 (PWM)
  pinMode(Left_motor_back,OUTPUT);   // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);    // PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);  // PIN 11 (PWM)

  pinMode(SensorRight, INPUT);       // 定义右循迹红外传感器为输入
  pinMode(SensorLeft, INPUT);        // 定义左循迹红外传感器为输入
}


//=======================智能小车的基本动作=========================
// 前进
void goStraight()
{
  // 右电机前进 
  analogWrite(Right_motor_go,60);   //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  // 左电机前进
  analogWrite(Left_motor_go,60);    //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,0);
}

//刹车，停车
void brake()
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);

}


//左转(左轮不动，右轮前进)
void turnLeft()
{
  //右电机前进
  analogWrite(Right_motor_go,60); 
  analogWrite(Right_motor_back,0);  //PWM比例0~255调速
   //左轮不动
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);   //PWM比例0~255调速
  
}


//右转(右轮不动，左轮前进)
void turnRight()
{
 //右轮不动
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);  //PWM比例0~255调速
 //左电机前进
  analogWrite(Left_motor_go,60); 
  analogWrite(Left_motor_back,0);   //PWM比例0~255调速

}


void loop()
{ 
  SL = digitalRead(SensorLeft);      //数字读出 LOW 表明此传感器在白色区域，传感器指示灯亮；数字读出 HIGH 表明此传感器在黑色区域，传感器指示灭
  SR = digitalRead(SensorRight);     //数字读出 LOW 表明此传感器在白色区域，传感器指示灯亮；数字读出 HIGH 表明此传感器在黑色区域，传感器指示灭  
  if (SL == LOW&&SR==LOW)
    goStraight();                    //调用前进函数
  else if (SL == HIGH & SR == LOW)   // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    turnLeft();
  else if (SR == HIGH & SL == LOW)   // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    turnRight();
  else                               // 都是黑色, 停止
  brake();
  
}


