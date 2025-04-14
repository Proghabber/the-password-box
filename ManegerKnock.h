#pragma once
#include "Tools.h"
#include "List.h"

class Knock {
public:
  Knock () 
  {
  }

  Knock (const unsigned long& time): time_wait_(time)
  {
  }

  const unsigned long GetTime(){
    return time_wait_;
  }

  const unsigned long GetDeviation(){
    return deviation_;
  }

private:
  unsigned long time_wait_ = 0;
  unsigned long deviation_ = 100; //погрешность для стуков
  
};


class ManegerKnock {
public:
  ManegerKnock() = default;
  
  ManegerKnock(List<int> list){
    for (byte i = 0; i < list.GetSize(); i++){
      AddElem(list[i]);
    } 
  }
  
  void AddElem(unsigned long time_wait){
    list_.AddElem(Knock(time_wait));
  }

  void MakeQueueBlink(SwichLed& led, const unsigned long paus){
    for (size_t i = 0; i < list_.GetSize(); i++){
      Timer paus_time(list_[i].GetTime());
      paus_time.WaitTime();//  пауза между стукам
      BlinkLed(led, paus);
    }
  }

  const size_t GetSize(){
    return list_.GetSize();
  }

  List<Knock>& GetList(){
    return list_;
  }

private:
  List<Knock> list_;
  
  void BlinkLed(SwichLed& led, const unsigned long paus){
    led.OnLed();
    Timer blink_time(paus);
    blink_time.WaitTime();//  пауза между стукам
    led.OffLed();
  }
};

inline bool operator==(const Knock& lhs, const Knock& rhs){
    if (abs(int(lhs.GetTime() - rhs.GetTime())) < lhs.GetDeviation()){
      return true;
    }
    return false;
}

inline bool operator!=(const Knock& lhs, const Knock& rhs){
    return !(lhs == rhs);
}

inline bool operator==(const ManegerKnock& lhs, const ManegerKnock& rhs){
    if (lhs.GetList() == rhs.GetList()){
      return true;
    }
    return false;
}