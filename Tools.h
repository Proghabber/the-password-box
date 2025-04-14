#pragma once

class Timer{
public:
  Timer(const unsigned long wait): time_wait_(wait)
  {
  }

  void StartTime(){
      time_tick_ = millis();
  } 

  bool IsFinish(){
    if (long(time_tick_ + time_wait_ - millis()) >= 0){
      return false;
    }
    return true;
  }

  const long HowLong(){
    return long(millis() - time_tick_);
  }

  void WaitTime(){ //ожидаем заданое время
    StartTime();
    while(!IsFinish()){
    }
  }

private:
  const unsigned  time_wait_;
  unsigned long time_tick_ = 0;
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