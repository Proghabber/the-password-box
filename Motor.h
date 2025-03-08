#pragma once
#include "Tools.h"

class Motor {
public:
  Motor(const uint8_t led_high, const  uint8_t led_low, const uint8_t photo_high, const uint8_t photo_low, const uint8_t forward, const uint8_t back, const uint8_t speed):
  pin_led_high_(led_high),
  pin_led_low_(led_low),
  pin_photo_high_(photo_high),
  pin_photo_low_(photo_low),
  pin_forward_(forward),
  pin_back_(back),
  max_spd_(speed)
  {
    pin_led_high_.OffLed();//погасить светодиод
    pin_led_low_.OffLed();//погасить светодиод
  }

  void Motion(){
    if(!position_rod_){
      Move(pin_led_high_, pin_photo_high_, pin_forward_, pin_back_);
      position_rod_= true;
    } else {
      Move(pin_led_low_, pin_photo_low_, pin_back_, pin_forward_);
      position_rod_ = false;
    }
  }

private:
  void Move(SwichLed& led, const uint8_t pin_photo, const uint8_t forward, const uint8_t back){
    Timer time_led(10);
    Timer time_push(100);
    led.OnLed();//зажечь светодиод
    time_led.WaitTime();//подождать пока наберет яркость
    analogWrite(back, LOW);// подать низкое напряжение на логику обратного движения
    analogWrite(forward, max_spd_);// подать высокое напряжение на логику прямого движения
    while (analogRead(pin_photo) < 800){
    } 
    time_push.WaitTime();// основательно подпереть замок
    analogWrite(forward, LOW); // остановить двиготель
    led.OffLed(); // погосить светодиод
  }

  SwichLed pin_led_high_;
  SwichLed pin_led_low_;
  uint8_t pin_forward_;
  uint8_t pin_back_;
  uint8_t pin_photo_high_;
  uint8_t pin_photo_low_;
  const uint8_t max_spd_;
  bool position_rod_ = false;
};
 
