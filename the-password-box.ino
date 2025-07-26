#include "GyverButton.h"
#include "CombinationLock.h"
#include "ManegerKnock.h"
#include "Tools.h"
#include "Storage.h"

#include "tests.h"


uint8_t ledPin_1 = 2;       // лампочка на запись желтая
uint8_t ledPin_2 = 3;       // лампочка на повтор стуков зеленая
uint8_t lock_led_level = 4;  // пин светодиода уровня
uint8_t But_save = 6;     // кнопка на запись нового пароля
uint8_t forward_pin = 9;  // mx 1508 A1 пин управления мотором
uint8_t back_pin = 10;    // mx 1508 A2 пин управления мотором


uint8_t FonPin_1 = A0;    // микрофон
uint8_t lock_photo_level = A1;  // пин фоторезистора уровня

GButton butt1(But_save);

Motor motor_lock(lock_led_level, lock_photo_level, forward_pin, back_pin, 250);
CombinationLock lock(ledPin_1, ledPin_2, FonPin_1, butt1, motor_lock);


void setup() {
  Serial.begin(9600);               // Открываем порт на скорости 9600 бод.
  pinMode(ledPin_1, OUTPUT);        // Устанавливаем  как выход
  pinMode(ledPin_2, OUTPUT);        // Устанавливаем  как выход
  pinMode(FonPin_1, INPUT);         // Устанавливаем  как вход
  pinMode(But_save, INPUT_PULLUP);  // Устанавливаем как выход с подтяжкой

  pinMode(forward_pin, OUTPUT);  // Устанавливаем  как выход
  pinMode(back_pin, OUTPUT);     // Устанавливаем  как выход
  digitalWrite(forward_pin, 0);
  digitalWrite(back_pin, 0);
  pinMode(lock_led_level, OUTPUT);  // Устанавливаем светодиод
  pinMode(lock_photo_level, INPUT);      // Устанавливаем фоторезистор

  TestEmptyListKnock(Serial);
  TestAddListKnock(Serial);
  TestMoveConstructor(Serial);
  TestResize(Serial);
  //AlarmPassEvent();
  //TestReadWrite(Serial);
  //lock.DetermineRod();
}

void AlarmPassEvent() {  // если сбился или забыл пароль
  ManegerKnock pass_new;
  Storage keyhole_;
  keyhole_.WriteData(pass_new.GetList());
}



void loop() {
  lock.WaitingEvent();
  //uint8_t forward_pin = 9; // mx 1508 A1 пин управления мотором
  //uint8_t back_pin = 10; // mx 1508 A2 пин управления мотором
  //
  //analogWrite(back_pin, 100);
}
