#pragma once
#include "GyverButton.h"
#include "ManegerKnock.h"
#include "Tools.h"
#include "Storage.h"

#line 2 "sketch.ino"
#include <ArduinoUnit.h>




void TestEmptyListKnock(Print& port) {
    port.println("Test EmptyListKnock");
    List<Knock> list;
    assertEqual(list.GetSize(), 0);
    port.println("Done!");
}

void TestAddListKnock(Print& port) {
    port.println("Test AddListKnock");
    List<Knock> list;

    list.AddElem(Knock(100));
    assertEqual(list.GetSize(), 1);  
    assertEqual(list[0].GetTime(), 100);

    list.AddElem(Knock(200));
    assertEqual(list.GetSize(), 2); 
    assertEqual(list[0].GetTime(), 100);
    assertEqual(list[1].GetTime(), 200);
    
    port.println("Done!");
}

List<Knock> CreateListKnock(unsigned long arr[], size_t size){
  List<Knock> one;
  for (size_t i = 0; i < size; i++){
    one.AddElem(Knock(arr[i]));
  }
  return one;
}

void TestMoveConstructor(Print& port) {
    port.println("Test MoveConstructor");

    List<Knock> list_zero = CreateListKnock({}, 0);
    assertEqual(list_zero.GetSize(), 0);
    
    unsigned long arr[]{100, 200, 300, 400};
    List<Knock> list = CreateListKnock(arr, 4);

    assertEqual(list.GetSize(), 4);
    assertEqual(list[0].GetTime(), 100);
    assertEqual(list[1].GetTime(), 200);
    assertEqual(list[2].GetTime(), 300);
    assertEqual(list[3].GetTime(), 400);

    port.println("Done!");
}

void TestResize(Print& port) {
    port.println("Test Resize");

    List<Knock> list; 
    int knock = 100;

    assertEqual(list.GetSize(), 0);
    for (int i = 1; i < 11; i++ ){
      list.AddElem(Knock(i * knock));
    }
    assertEqual(list.GetSize(), 10);

    for (int i = 11; i < 21; i++ ){
      list.AddElem(Knock(i * knock));
    }
    assertEqual(list.GetSize(), 20);
    for (int i = 1; i < 21; i++ ){
      unsigned long elem = i * knock;
      assertEqual(list[i - 1].GetTime(), elem);
    }

    port.println("Done!");
}


void TestReadWrite(Print& port){
  port.println("Test ReadWrite");
  const size_t size = 4;
  List<int> data;

  int arr[]{100, 200, 300, 400};
  for (size_t i = 0; i < size; i++){
    data.AddElem(arr[i]);
  }
  Storage<int> one;
  
  one.WriteData(data);
  List<int> list = one.ReadData();
  assertEqual(list.GetSize(), size);
  for(size_t i = 0; i < list.GetSize(); i++){
    assertEqual(list[i], data[i]);  
  }

  port.println("Done!");
}
