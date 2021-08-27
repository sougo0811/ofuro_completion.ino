//自動で風呂沸かすやつ(照度センサーも付けてみた）
#include <Servo.h>

Servo servo_5;

void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT);
  servo_5.attach(5, 500, 2500);

  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
}

void loop()
{ 
  //タクトスイッチを押す前
  //照度センサー
  //このシステムでは、明るさは0～1023を0～100に変換して使っている
  servo_5.write(1500);  
  Serial.print("現在の照度は、");
  Serial.print(map(analogRead(A0), 0, 1023, 0, 100));
  Serial.println("です。");

  //暗ければ自動でLEDをつける
  if (map(analogRead(A0), 0, 1023, 0, 100) < 50) {
    Serial.println("明るさ：暗い");
    delay(1000);
    digitalWrite(4, LOW);
  } else {
    Serial.println("明るさ：明るい");
    delay(1000);
    digitalWrite(4, HIGH);
  }
  Serial.println("--------------------------------------------------------------");

  //タクトスイッチを押した後
  if (digitalRead(2) == 1) {
    
    //お風呂沸かすと知らせる
    Serial.println("お風呂を沸かします");
    delay(3000);
    
    //蛇口をひねる
    servo_5.write(2000);
    delay(10000); // Wait for 10000 millisecond(s)
    servo_5.write(1500);

    //お湯の量が全体の80％以下のときの処理（お風呂が沸き終わってないときの処理）
    while (map(analogRead(A1), 0, 1023, 0, 100) <= 80) {
    
    //お湯の量が全体の80％以下のとき（お風呂が沸き終わってない）　かつ　明るさが50未満のとき（暗いとき）　の処理
    while (map(analogRead(A1), 0, 1023, 0, 100) <= 80 && map(analogRead(A0), 0, 1023, 0, 100) < 50) {
      
      //お風呂沸かしてるよーってお知らせ
      Serial.println("お風呂を沸かしています");
      delay(1000);
      
      //暗いから電気点滅してあげるやつ
      digitalWrite(4, LOW);
      delay(4000);
      digitalWrite(4, HIGH);
      delay(1000);

      //目が不自由な人でも分るように、音も鳴らしちゃう
      tone(3, 523, 1000);
      delay(1000);

      //今どんくらいお湯貯まっているか教えてくれるやつ
      Serial.print("現在お湯は");
      Serial.print(map(analogRead(A1), 0, 1023, 0, 100));
      Serial.println("％溜まっています");
      Serial.println("--------------------------------------------------------------");
      delay(1000);}

     //お湯の量が全体の80％以下のとき（お風呂が沸き終わってない）　かつ　明るさが50以上のとき（明るいとき）　の処理      
    while (map(analogRead(A1), 0, 1023, 0, 100) <= 80 && map(analogRead(A0), 0, 1023, 0, 100) >= 50) {
      
      //お風呂沸かしてるよーってお知らせ
      Serial.println("お風呂を沸かしています");
      delay(1000);

      //目が不自由な人でも分るように、音も鳴らしちゃう
      tone(3, 523, 1000);
      delay(5000);

      //今どんくらいお湯貯まっているか教えてくれるやつ
      Serial.print("現在お湯は");
      Serial.print(map(analogRead(A1), 0, 1023, 0, 100));
      Serial.println("％溜まっています");
      Serial.println("--------------------------------------------------------------");
      delay(1000);}

    //お湯の量が全体の80％超えたとき（お風呂が沸き終わったら）
    }
    //家でお風呂沸いた時に流れる音楽流しとく
    servo_5.write(1000);
    delay(5000);
    servo_5.write(1500);
    tone(3, 784, 1000);
    delay(300);
    tone(3, 698, 1000);
    delay(300);
    tone(3, 659, 1000);
    delay(500);
    tone(3, 784, 1000);
    delay(300);
    tone(3, 1047, 1000);
    delay(300);
    tone(3, 988, 1000);
    delay(700);
    tone(3, 784, 1000);
    delay(300);
    tone(3, 1175, 1000);
    delay(300);
    tone(3, 1047, 1000);
    delay(500);
    tone(3, 1319, 1500);
    delay(1000);
    tone(3, 1047, 1000);
    delay(300);
    tone(3, 988, 1000);
    delay(300);
    tone(3, 880, 1000);
    delay(700);
    tone(3, 1397, 1000);
    delay(300);
    tone(3, 1175, 1000);
    delay(300);
    tone(3, 1047, 1000);
    delay(500);
    tone(3, 988, 1000);
    delay(500);
    tone(3, 1047, 1000);
    delay(500);
    tone(3, 1047, 1000);
    delay(1000);

    //お風呂沸いたって教えてくれるやつ
    Serial.println("お風呂が沸きました");
    Serial.println("--------------------------------------------------------------");
  } else {
    //スイッチを押してないとき
    Serial.println("スイッチを押してください");
    delay(100);
    
    
  }
  Serial.println("--------------------------------------------------------------");
  delay(1000);

  //おしまい

}
