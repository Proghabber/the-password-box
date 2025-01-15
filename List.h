#pragma once

template <typename Type>
class List {
public:
  List ():set_knock_(new Type [10]), capacity_(10)
  {
  }

  List (const List& other) = delete; // копирующий конструктор
  List (List&& other) noexcept{ //перемещающий конструктор
    this->Swap(other.set_knock_);
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    
  }
  List& operator=(const List& other) noexcept = delete; // копирующий оператор присваивания
  List& operator=(List&& other) = delete; //перемещающий оператор присваивания

 //также переопредилим деструктор 
  ~List (){
    delete []  set_knock_;
  } 

  void Swap(Type* other) noexcept {
    Type *set_copy = set_knock_;
    set_knock_ = other;
    other = nullptr;
    delete [] set_copy;
    set_copy = nullptr;
  }

  bool AddElem(Type elem){
    if (size_ < capacity_){
      *(set_knock_ + size_) = elem;
      size_++;
    } else {
      byte new_capacity = capacity_ * 2;
      if (new_capacity > max_size_){
        return false;
      }
      Type *set_new = new Type[new_capacity];
      for (byte i = 0; i <capacity_; i++ ){
        *(set_new + i) = *(set_knock_ + i);
      }
      Swap(set_new);
      *(set_knock_ + size_) = elem;
      size_++;
      capacity_ = new_capacity;
    }
    return true;
  }

  const Type& operator[](byte index) const noexcept {
      return *(set_knock_ + index);
  }

  const byte GetSize(){
    return size_;
  }

private:
  Type *set_knock_ = nullptr;
  byte size_ = 0;
  byte capacity_ = 0;
  const byte max_size_ = 20;

};

template <typename Type>
inline bool operator==(const List<Type>& lhs, const List<Type>& rhs){
    if (lhs.GetSize() != rhs.GetSize()){
      return false;
    }
    for (size_t i = 0; i < lhs.GetSize(); i++){
      if (lhs[i] != rhs[i]){
        return false;
      }
    }
    return true;
}