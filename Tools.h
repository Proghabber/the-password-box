#pragma once
#include <limits.h>

class Timer{
public:
  Timer(const unsigned long wait): time_wait_(wait)
  {
  }

  void StartTime(){
      time_start_ = millis();
      //если таймер на грани переаолнения, необхолимо учесть что искать конец надо на новом круге отсчета.
      int64_t randge_time = time_start_ + time_wait_;
      if (randge_time > ULONG_MAX){
        time_end_ = randge_time - ULONG_MAX;
        return;
      } 
      time_end_ = randge_time;
  } 

  bool IsFinish(){
    // если таймер переполнился и начал отсчет заново
    if (time_start_ > time_end_){
      if (millis() >= time_end_ && millis() < time_start_){
        return true;
      } else {
        return false;
      }
    }
    //стандартная не граничная ситуация
    if (millis() >= time_end_){
      return true;
    } 
    return false;
  }

  const unsigned long HowLong(){
    // если таймер можкет  переполнился и начать отсчет заново
    if (time_start_ > time_end_ ){
      //но еще не произошло переполнение
      if (millis() >= time_start_){
        return millis() - time_start_;
      } else {
        // если таймер переполнился и начал отсчет заново
        return ULONG_MAX - time_start_ + millis();
      }
    }
    //стандартная не граничная ситуация
    return millis() - time_start_;
    
  }

  void WaitTime(){ //ожидаем заданое время
    StartTime();
    while(!IsFinish()){
    }
  }

private:
  const unsigned long  time_wait_;
  unsigned long time_start_ = 0;
  unsigned long time_end_ = 0;
};

class SwichLed{
public:
  SwichLed(uint8_t pin_led): led_(pin_led)
  {
  }

  void OnLed(){
    digitalWrite(led_, HIGH);
    status_ = false;
  }

  void OffLed(){
    digitalWrite(led_, LOW);
    status_ = true;
  }

  bool GetStatus(){
    return status_;
  }

private:
  const uint8_t led_;
  bool status_ = false;
};