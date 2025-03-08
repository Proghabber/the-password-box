#pragma once

#include<EEPROM.h>
#include "List.h"

class Storage {
public:
  void Read(List<Knock>& data){
    size_list = Readint(1);
    for (size_t i = 0; i < size_list; i ++){
      data.AddElem(Knock(Readint(address)));
      address += size_type;
    }
    address = 2;
  }

  bool WriteData(List<Knock>& data){
    size_list = data.GetSize();
    if (size_list * size_type > 998){ // нельзя записать больше 1000 байт (998 + 2 для размера массива и размера типа)
                                      // да и динамическая память может не дать это сделать
      return false;
    }
    WriteInt(0, size_type);
    WriteInt(1, size_list);
    address = 2;
    for (size_t i = 0; i < size_list; i++){
      WriteInt(address, data[i].GetTime());
      address += size_type;
    }
    address = 2;
    return true;
  }

private:
  byte size_list = 0; //размер массива данных
  const byte size_type = 2; //размер типа данных в байтах
  byte address = 2;  //адрес для записи

  unsigned int Readint(byte pos){
    int data = 0;
    EEPROM.get(pos, data);
    return data;
  }

  void WriteInt(byte pos, int data){
    EEPROM.put(pos, data);
  }

};

