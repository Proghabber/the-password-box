#pragma once
#include "ManegerKnock.h"
#include "Tools.h"
#include "Storage.h"

class CombinationLock {
public:
  CombinationLock(uint8_t led_1, uint8_t led_2, uint8_t signal): led_recorder_(led_1), led_repeat_(led_2), signal_unit_(signal)
  {
  }

  void WaitingKey(){
    if (analogRead(signal_unit_) > volume_){
      ManegerKnock pass_1 = CreatePass();
      ManegerKnock pass_2 = CreatePass();
      if (pass_1 == pass_2){
        led_recorder_.OnLed();
        led_repeat_.OnLed();
      }
      Timer wrong_pass(500);
      led_recorder_.OnLed();
      wrong_pass.StartTime();
      while (!wrong_pass.IsFinish()){ 
      }
      led_recorder_.OffLed();
      }
    
    

  }
  
private:
  const int time_listener_ = 3000;
  SwichLed led_recorder_;
  SwichLed led_repeat_;
  Storage<int> keyhole_;
  const byte paus_ = 80;
  const byte volume_ = 90;
  const byte signal_unit_;

  ManegerKnock ListenPass(){
    ManegerKnock knocker;
    Timer listen_time(time_listener_);

    listen_time.StartTime();
    while (!listen_time.IsFinish()){ // начали слушать
      if (analogRead(signal_unit_) > volume_ && listen_time.HowLong() > paus_){ // услышали звук и время паузы не вышло
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

};