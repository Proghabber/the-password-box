#include "GyverButton.h"
#include "CombinationLock.h"
#include "ManegerKnock.h"
#include "Tools.h"
#include "Storage.h"

#include "Tests.h"



uint8_t ledPin_1 = 2;  // лампочка на запись
uint8_t ledPin_2 = 3;  // лампочка на повтор стуков
uint8_t lock_led_high = 4; // пины верхнего и нижнего светодиодов
uint8_t lock_led_low = 5; 
uint8_t But_save = 6;  // кнопка на запись нового пароля
uint8_t forward_pin = 9; // mx 1508 A1 пин управления мотором
uint8_t back_pin = 10; // mx 1508 A2 пин управления мотором


uint8_t FonPin_1 = A0;  // микрофон
uint8_t photo_high = A1;// пины верхнего и нижнего фоторезистора
uint8_t photo_low = A2;

GButton butt1(But_save);

Motor motor_lock(lock_led_high, lock_led_low, photo_high, photo_low, forward_pin, back_pin, 250);
CombinationLock lock(ledPin_1, ledPin_2, FonPin_1, butt1, motor_lock);


void setup() {
  Serial.begin(9600);  // Открываем порт на скорости 9600 бод.
  pinMode(ledPin_1, OUTPUT); // Устанавливаем  как выход
  pinMode(ledPin_2, OUTPUT);// Устанавливаем  как выход
  pinMode(FonPin_1, INPUT);// Устанавливаем  как вход
  pinMode(But_save, INPUT_PULLUP); // Устанавливаем как выход с подтяжкой

  pinMode(forward_pin, OUTPUT);    // Устанавливаем  как выход
  pinMode(back_pin, OUTPUT);    // Устанавливаем  как выход
  pinMode(lock_led_high, OUTPUT);    // Устанавливаем светодиод
  pinMode(lock_led_low, OUTPUT);    // Устанавливаем светодиод
  pinMode(photo_high, INPUT); // Устанавливаем фоторезистор
  pinMode(photo_low, INPUT); // Устанавливаем фоторозистор

TestEmptyListKnock(Serial);
TestAddListKnock(Serial);
TestMoveConstructor(Serial);
TestResize(Serial);
//AlarmPassEvent();
//TestReadWrite(Serial);
lock.DetermineRod();
}

void AlarmPassEvent(){// если сбился или забыли пароль
  ManegerKnock pass_new;
  Storage keyhole_;
  keyhole_.WriteData(pass_new.GetList());
}



void loop() {
  lock.WaitingEvent();
  
  
}
