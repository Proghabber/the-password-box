#pragma once

#include<EEPROM.h>
#include "List.h"

template <typename Type>
class Storage {
public:
  List<Type> ReadData(){
    size_type = Readint(0);
    size_list = Readint(1);
    List<Type> ret_list;
    
    for (size_t i = 0; i < size_list; i ++){
      int data = Readint(address);
      ret_list.AddElem(data);
      address += size_type;
    }

    return ret_list;
  }

  bool WriteData(const List<Type>& data){
    size_type = sizeof(Type);
    size_list = data.GetSize();
    if (size_list * size_type > 998){ // нельзя записать больше 1000 байт (998 + 2 для размера массива и размера типа)
                                      // да и динамическая память может не дать это сделать
      return false;
    }
    WriteInt(0, size_type);
    WriteInt(1, size_list);

    for (size_t i = 0; i < size_list; i++){
      WriteInt(address, data[i]);
      address += size_type;
    }
    return true;
  }

private:
  byte size_list = 0; //размер массива данных
  byte size_type = 0; //размер типа данных в байтах
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

