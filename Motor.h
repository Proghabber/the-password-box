#pragma once
#include "Tools.h"


class DriverMotor {
public:
  DriverMotor(const uint8_t forward, const uint8_t back): 
  forward_pin_(forward), 
  back_pin_(back)
  {
  }

  void Motion (const uint8_t speed){
    if (rotation_){
      analogWrite(forward_pin_, speed);
      analogWrite(back_pin_, 0);
    } else {
      analogWrite(forward_pin_, 0);
      analogWrite(back_pin_, speed);
    }
  }

  void Stop (const uint8_t speed){
    analogWrite(forward_pin_, speed);
    analogWrite(back_pin_, speed);

  }

  void SetMotion(bool rotation){
      rotation_ = rotation;
  }

  void Off_power(){
    analogWrite(forward_pin_, 0);
    analogWrite(back_pin_, 0);
  }


private:
  const uint8_t forward_pin_;
  const uint8_t back_pin_;
  bool rotation_ = true;

};

class Motor {
public:
  Motor(uint8_t pin_led_level, uint8_t pin_photo_level, const uint8_t forward, const uint8_t back, const uint8_t speed):
  driver_(forward, back),
  led_level_(pin_led_level),
  photo_level_(pin_photo_level),
  
  max_spd_(speed)
  {
  }

  void Motion(){
    Move();
    if(!position_rod_){
      driver_.SetMotion(true);
      position_rod_= true;
      return;
    }
    driver_.SetMotion(false);
    position_rod_ = false;
  }

  bool GetPos(){
    return !position_rod_;
  }
  
private:
  void StepMove(){ 
    Timer time_go(time_go_);
    Timer time_stop(time_stop_);
    driver_.Motion(max_spd_);
    time_go.WaitTime();
    driver_.Stop(max_spd_);
    driver_.Off_power();
    time_stop.WaitTime();
  }

  void Move(){
    Timer time_led(100);
    led_level_.OnLed();//зажечь светодиод
    time_led.WaitTime();//подождать пока наберет яркость
    int stay = analogRead(photo_level_);
    int tab = 0; 
    bool stop = false; 
    while(true){
      //Serial.println(tab);
      StepMove();
      if (tab && stay - analogRead(photo_level_) > 1){
        stop = true;
        stay = analogRead(photo_level_);
        tab--;
      } else if(analogRead(photo_level_) - stay > 1){
        stay = analogRead(photo_level_);
        tab ++;
      }
      if (tab <= 1 && stop) {
          break;
        }
    }
    driver_.Stop(max_spd_);
    driver_.Off_power();
    led_level_.OffLed(); // погасить светодиод
  }

  

  DriverMotor driver_;
  SwichLed led_level_;
  uint8_t photo_level_;
  const uint8_t max_spd_;
  const uint8_t time_led_;
  const uint8_t time_go_ = 5;
  const uint8_t time_stop_ = 50;
  bool position_rod_ = true;

};
 
