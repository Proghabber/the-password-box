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
  Motor(uint8_t led_high, uint8_t led_low,  uint8_t photo_high, uint8_t photo_low, const uint8_t forward, const uint8_t back, const uint8_t speed):
  driver_(forward, back),
  pin_led_high_(led_high),
  pin_led_low_(led_low),
  pin_photo_high_(photo_high),
  pin_photo_low_(photo_low),
  max_spd_(speed)
  {
  }

  void Motion(){
    if(!position_rod_){
      driver_.SetMotion(true);
      Move(pin_led_high_, pin_photo_high_);
      position_rod_= true;
    } else {
      driver_.SetMotion(false);
      Move(pin_led_low_, pin_photo_low_);
      position_rod_ = false;
    }
  }

  void SearceRod(){
    pin_led_high_.OnLed();
    pin_led_low_.OnLed();
    Timer time_led(150);
    time_led.WaitTime();
    if (analogRead(pin_photo_high_) > analogRead(pin_photo_low_)){
      position_rod_ = true;
    }
    pin_led_high_.OffLed();
    pin_led_low_.OffLed();
  }

  bool GetPos(){
    return !position_rod_;
  }
  
private:
  void StepMove (const uint8_t pin_photo, bool& stop_m, bool& start){ 
    Timer time_go(4);
    Timer time_stop(10);
    int data_p_r = 0;

    if (!stop_m){
      driver_.Motion(max_spd_);
    }
  
    data_p_r = analogRead(pin_photo);
    time_go.WaitTime();
    if (analogRead(pin_photo) - data_p_r > 2 ){
      start = true;   
      }

    driver_.Stop(max_spd_);
    time_stop.WaitTime();
    if  (data_p_r - analogRead(pin_photo)  > 2  && start){
        stop_m = true;
        driver_.Off_power();
    } 
  }

  void Move(SwichLed& led, const uint8_t pin_photo){
    Timer time_led(100);
    bool stop = false;
    bool start_count = false;

    led.OnLed();//зажечь светодиод
    time_led.WaitTime();//подождать пока наберет яркость
  
    while (stop == false){
      StepMove (pin_photo, stop, start_count);
    }

    led.OffLed(); // погосить светодиод
  }

  

  DriverMotor driver_;
  SwichLed pin_led_high_;
  SwichLed pin_led_low_;
  uint8_t pin_photo_high_;
  uint8_t pin_photo_low_;
  const uint8_t max_spd_;
  bool position_rod_ = false;
};
 
