#include <Servo.h>

const int SERVO = 8;
const int BUTTON_INT=0;

Servo myServo;

int initialAngle = 0;

unsigned long startTime;
float nowTime;

bool flag = 0;
bool interruptFlag = 0;

void setup() {
  myServo.attach(SERVO);
  attachInterrupt(BUTTON_INT, systemFinish, RISING);
  Serial.begin(9600);
}

void loop() {
  system_start();

  headShake();
}

void system_start() {
  String buffer;

  while(Serial.available()) { //시리얼 버퍼가 차있을 때만 읽어옴
    char data = Serial.read();
    if(data == '\n') {
      break;
    }
    else {
      buffer = buffer + data;
    }
    delay(10);
  }

  if(buffer == "Go" || buffer == "go") { //서버에서 스타트 신호를 받았을 때로 바꿀 
    startTime = millis();
    flag = 1;
    interruptFlag = 0;
    Serial.println(buffer);
  }
  
}

void headShake() {
  if(interruptFlag == 1) {
    flag = 0;
  }
  if(flag == 1) {
    //greenlight 시간 랜덤으로 할 것, 음성을 출력할 것 (sd카드 사운드 활용)
    myServo.write(180);
    Serial.println("Green Light!");
    delay(3000);
    myServo.write(0);
    Serial.println("Red Light!");
    delay(3000);

  }
}

void systemFinish() { //버튼 누름을 단 한 번만 인식하도록 만들어야 함, 시스템이 스타트 상태일 때만 인터럽트 발생하게할 것
    Serial.println("intrrupt!"); 
    interruptFlag = 1;
    nowTime = (millis() - startTime) / 1000.0;
    Serial.print("진행 시간 : ");
    Serial.print(nowTime, 1);
    Serial.println("s");

    //경과 시간을 서버로 보내줄 것
}

//움직임을 걸렸을 때 음성 출력
