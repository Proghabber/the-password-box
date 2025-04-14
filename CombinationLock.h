#pragma once
#include "ManegerKnock.h"
#include "Tools.h"
#include "Storage.h"
#include "Motor.h"

class CombinationLock {
public:
  CombinationLock(uint8_t& led_1, uint8_t& led_2, uint8_t& signal, GButton&  but, Motor& mot): 
  led_recorder_(led_1), 
  led_repeat_(led_2), 
  signal_unit_(signal), 
  but_save_(but),
  Motor_rod_(mot)
  {
  }

  void DetermineRod(){
    Motor_rod_.SearceRod();
  }

  void WaitingEvent(){
    but_save_.tick();
    if (Motor_rod_.GetPos() && but_save_.isClick()){// если окрыт и кнопка нажата, то слушаем новый пароль ожидаем три секунды и если кнопка зажата вновь ,то сохраняем пароль
      but_save_.tick();
      ManegerKnock pass_new = CreatePass();
      Timer recoder_time(time_listener_);
      recoder_time.StartTime();
      while (!recoder_time.IsFinish()){
        but_save_.tick();
        if (but_save_.isClick()){
          keyhole_.WriteData(pass_new.GetList());
          blinkin_led_Save();
          break;
        }
      }
    }
    if (analogRead(signal_unit_) > volume_){ // даоее просто слушаем пароль и если он совпадает с записаным ,то меняем статус замка
      ManegerKnock pass;
      keyhole_.Read(pass.GetList());
      if (MatchKey(pass)){
        ChengeLock();
      }
    }
    but_save_.resetStates(); // зашита от случайного нажатия
  }

private:
  const int time_listener_ = 3000;
  SwichLed led_recorder_;
  SwichLed led_repeat_;
  Storage keyhole_;
  const byte paus_ = 80;
  const byte volume_ = 90;
  const byte signal_unit_;
  GButton& but_save_;
  Motor& Motor_rod_;

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

  bool MatchKey(ManegerKnock& pass_1){
    ManegerKnock pass_2 = CreatePass();
    if (pass_1 == pass_2){
      return true;
    }  
    Timer wrong_pass(500);
    led_recorder_.OnLed();
    wrong_pass.WaitTime();
    led_recorder_.OffLed();
    return false; 
    
  }

  void blinkin_led_Save(){
    unsigned long count = 0;
    while(count < 3){
      Timer on_time(400);
      led_recorder_.OnLed();
      led_repeat_.OnLed();
      on_time.WaitTime();
      led_recorder_.OffLed();
      led_repeat_.OffLed();
      Timer off_time(400);
      off_time.WaitTime();
    count++;
    }
    
  }

  void ChengeLock(){
      Motor_rod_.Motion();
  }

};