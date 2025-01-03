#pragma once
#include "Tools.h"

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
  unsigned long deviation_ = 200; //погрешность для стуков
  
};

class ManegerKnock {
public:
  ManegerKnock ():set_knock_(new Knock [10]), capacity_(10)
  {
  }

  ManegerKnock (const ManegerKnock& other) = delete; // копирующий конструктор
  ManegerKnock (ManegerKnock&& other) noexcept{ //перемещающий конструктор
    this->Swap(other.set_knock_);
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    
  }
  ManegerKnock& operator=(const ManegerKnock& other) noexcept = delete; // копирующий оператор присваивания
  ManegerKnock& operator=(ManegerKnock&& other) = delete; //перемещающий оператор присваивания

 //также переопредилим деструктор 
  ~ManegerKnock (){
    delete []  set_knock_;
  } 

  void Swap(Knock* other) noexcept {
    Knock *set_copy = set_knock_;
    set_knock_ = other;
    other = nullptr;
    delete [] set_copy;
    set_copy = nullptr;
  }

  void AddElem(unsigned long time_wait){
    if (size_ < capacity_){
      *(set_knock_ + size_) = Knock(time_wait);
      size_++;
    } else {
      size_t new_capacity = capacity_ * 2;
      Knock *set_new = new Knock[new_capacity];
      for (size_t i = 0; i <capacity_; i++ ){
        *(set_new + i) = *(set_knock_ + i);
      }

      Swap(set_new);
      *(set_knock_ + size_) = Knock(time_wait);
      

      size_++;
      capacity_ = new_capacity;
    }
  }

  void MakeQueueBlink(SwichLed& led, const unsigned long paus){
    for (size_t i = 0; i < size_ ; i++){
      Timer paus_time((set_knock_ + i)->GetTime());
      paus_time.StartTime();
      while (!paus_time.IsFinish()){ //  пауза между стуками 
      }
      BlinkLed(led, paus);
    }
  }

  const Knock& operator[](size_t index) const noexcept {
      return *(set_knock_ + index);
  }

  const size_t GetSize(){
    return size_;
  }

private:
  Knock *set_knock_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

  void BlinkLed(SwichLed& led, const unsigned long paus){
    led.OnLed();
    Timer blink_time(paus);
    blink_time.StartTime();
    while (!blink_time.IsFinish()){ //  пауза между стуками 
    }
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
    if (lhs.GetSize() != rhs.GetSize()){
      return false;
    }
    size_t size = lhs.GetSize();
    for (size_t i = 0; i < size; i++){
      if (lhs[i] != rhs[i]){
        return false;
      }
    }
    return true;
}