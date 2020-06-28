#include <LiquidCrystal_I2C.h>
#include <Wire.h>

byte check[8]={ B00000, B00001, B00010,B00010, B10100, B10100, B01000, B00000};
int m_min = 26;
int m_max = 0;
int redPin= 13;
int bluePin = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
   Serial.begin(9600);
   pinMode(redPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   lcd.init();     // initialize the lcd 
   lcd.backlight();  // finish with backlight on  
    lcd.createChar(0, check);
    
}
void loop()
{
  int val = analogRead(A0);
  Serial.print("데시벨:  ");
  Serial.print(val);
  Serial.print("\n");    

  delay(50); 
    if(val>65){
      digitalWrite(redPin,HIGH);
      digitalWrite(bluePin,LOW);
      Serial.print("큰소리가 감지되었습니다.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Decibel: ");
      lcd.print(val);
      lcd.setCursor(0,1);   
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
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Decibel: ");
      lcd.print(val);
      lcd.setCursor(0,1);   
      lcd.print("Quiet[");
      lcd.write(byte(0));
      lcd.print("]");
      lcd.print("Noise[");
      lcd.print("]");
      delay(1000);
    }
}
