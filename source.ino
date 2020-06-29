#include <LiquidCrystal_I2C.h>         //LCD 디스플레이어 사용을 위한 헤더파일 선언
#include <Wire.h>                      //LCD 통신을 위하여 헤더파일 선언

byte check[8]={ B00000, B00001, B00010,B00010, B10100, B10100, B01000, B00000};           //LCD에 특수문자(체크표시)출력을 위한 배열
int m_min = 26;
int m_max = 0;
int redPin= 13;
int bluePin = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
   Serial.begin(9600);                        //시리얼 통신
   pinMode(redPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   lcd.init();                   
   lcd.backlight();           //lcd 배경 불 켜기
    lcd.createChar(0, check);
    
}
void loop()
{
  int val = analogRead(A0);         // 사운드센서로부터 입력받은 값을 val 변수에 저장함.
  Serial.print("데시벨:  ");        
  Serial.print(val);               // 시리얼 모니터에 현재 데시벨이 얼마정도인지 계속 출력함.
  Serial.print("\n");    

  delay(50); 
    if(val>65){                    // 데시벨이 공간마다 기준이 다르지만 65이상을 기준으로 잡고 하였다.
      digitalWrite(redPin,HIGH);          //65 이상일때 빨간 LED가 켜짐.
      digitalWrite(bluePin,LOW);          //65 이상일때 파란 LED는 꺼짐.
      Serial.print("큰소리가 감지되었습니다.");         // 일정 데시벨 이상으로 넘어갔을때 시리얼통신으로 출력문을 출력함.
      lcd.clear();                                    //LCD 초기화
      lcd.setCursor(0,0);                             //LCD 1번째 줄에 Decibel을 적음
      lcd.print("Decibel: ");
      lcd.print(val);
      lcd.setCursor(0,1);                             //lcd 2번째 줄에 Quiet Noise를 적고 65이상일때 Noise 중괄호안에 체크표시를 출력하는 byte를 넣음.
      lcd.print("Quiet[");
      lcd.print("]");
      lcd.print("Noise[");
      lcd.write(byte(0));
      lcd.print("]");
      delay(1000);
    }
    else if(val<65 && val>=0 ){
      digitalWrite(bluePin,HIGH);
      digitalWrite(redPin,LOW);
      lcd.clear();                                    //LCD 초기화
      lcd.setCursor(0,0);
      lcd.print("Decibel: ");                         //LCD 1번째 줄에 Decibel을 적음
      lcd.print(val);
      lcd.setCursor(0,1);           
      lcd.print("Quiet[");                            //lcd 2번째 줄에 65이하일때 quite 중괄호안에 체크표시를 출력하는 byte를 넣음.
      lcd.write(byte(0));
      lcd.print("]");
      lcd.print("Noise[");
      lcd.print("]");
      delay(1000);
    }
}
