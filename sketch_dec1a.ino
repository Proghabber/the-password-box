#include "GyverButton.h"
#include "ManegerKnock.h"
#include "Tools.h"

uint8_t ledPin_1 = 2;  // лампочка на запись
uint8_t ledPin_2 = 4;  // лампочка на повтор стуков
uint8_t FonPin_1 = A0;  // микрофон
uint8_t ResetPin_1 = 3;  // кнопка перезагрузки
GButton butt1(ResetPin_1);

void setup() {
 Serial.begin(9600);  // Открываем порт на скорости 9600 бод.
 pinMode(ledPin_1, OUTPUT);
 pinMode(ledPin_2, OUTPUT);
 pinMode(FonPin_1, INPUT);
 pinMode(ResetPin_1, INPUT_PULLUP);
 

}


class CombinationLock {
public:
  CombinationLock(uint8_t led_1, uint8_t led_2): led_recorder_(led_1), led_repeat_(led_2)
  {
  }

  void ListenSound(){
    if (analogRead(FonPin_1) > volume_){
      ManegerKnock pass_1 = CreatePass();
      ManegerKnock pass_2 = CreatePass();
      MatchPass(pass_1, pass_2);
    }
    
    

  }
  
private:
  SwichLed led_recorder_;
  SwichLed led_repeat_;
  const int time_listener_ = 3000;
  const int paus_ = 80;
  const byte volume_ = 90;

  ManegerKnock ListenPass(){
    ManegerKnock knocker;
    Timer listen_time(time_listener_);

    listen_time.StartTime();
    while (!listen_time.IsFinish()){ // начали слушать
      if (analogRead(FonPin_1) > volume_ && listen_time.HowLong() > paus_){ // услышали звук и время паузы не вышло
        if (knocker.GetSize() > 0){
          knocker.AddElem(listen_time.HowLong());
        } else {
          knocker.AddElem(0);
        }
        listen_time.StartTime();     
      }
    }
    return knocker;
  }

  ManegerKnock CreatePass(){
    led_recorder_.OnLed();
    ManegerKnock pass = ListenPass();
    led_recorder_.OffLed();

    pass.MakeQueueBlink(led_repeat_, 100);
    return pass;
  }

  void MatchPass(const ManegerKnock& one, const ManegerKnock& two){
    if (one == two){
      led_recorder_.OnLed();
      led_repeat_.OnLed();
      
    } else {
      Timer wrong_pass(500);
      led_recorder_.OnLed();
      wrong_pass.StartTime();
      while (!wrong_pass.IsFinish()){ //  пауза между стуками 
      }
      led_recorder_.OffLed();
    }
  }
};




CombinationLock lock(ledPin_1, ledPin_2);
void loop() {
  lock.ListenSound();
  
  
}
