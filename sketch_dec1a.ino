#include "GyverButton.h"
#include "CombinationLock.h"
#include "Tests.h"


uint8_t ledPin_1 = 2;  // лампочка на запись
uint8_t ledPin_2 = 4;  // лампочка на повтор стуков
uint8_t FonPin_1 = A0;  // микрофон
uint8_t ResetPin_1 = 3;  // кнопка перезагрузки
GButton butt1(ResetPin_1);
CombinationLock lock(ledPin_1, ledPin_2, FonPin_1);

void setup() {
 Serial.begin(9600);  // Открываем порт на скорости 9600 бод.
 pinMode(ledPin_1, OUTPUT);
 pinMode(ledPin_2, OUTPUT);
 pinMode(FonPin_1, INPUT);
 pinMode(ResetPin_1, INPUT_PULLUP);
 

TestEmptyListKnock(Serial);
TestAddListKnock(Serial);
TestMoveConstructor(Serial);
TestResize(Serial);
//TestReadWrite(Serial);



}



void loop() {
  lock.WaitingKey();
  
  
}
