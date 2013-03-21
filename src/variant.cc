#include <stencet/variant.h>

namespace stencet {
  /*Variant::Variant(bool _managed)  {
    this->managed = _managed;
    }*/
  Variant::Variant()  {
    this->managed = true;
  }


  int Variant::asInt() const {
    switch(type){
    case 3:
      return (int) Get<3>();
    case 4:
      return (int) Get<4>();
    case 5: 
      return (int) Get<5>();
    default:
      assert(false);
    }
  }
  void Variant::asString(std::string& str) const {
    if(type == 2){
      str = this->as<std::string>();
      return;
    }
    std::stringstream ss;
    switch(type){
    case 3:
      ss << Get<3>();
      break;
    case 4:
      ss << Get<4>();
      break;
    case 5: 
      ss << Get<5>();
      break;
    default:
      assert(false);
      return;
    }
    str = ss.str();
  }

  Variant& Variant::operator[](const std::string& name){
    assert(at(name));
    return *at(name);
  }

  Variant& Variant::operator[](size_t i){
    return *at(i);
  }

  bool Variant::hasValue(const std::string& name) {
    MapT& map = this->as<MapT>();
    return map.find(name) != map.end();
  }

  Variant* Variant::at(const std::string& name){
    //    assert(type != Literal);
    //    type = Object;
    //    return &internal_map[name];
    return &this->as<MapT>()[name];
  }

  Variant* Variant::at(size_t idx) {
    ListT& list = this->as<ListT>();
    if( (int)idx == -1 ) {      
      idx = list.size();
      list.push_back( Variant() );     
    }
    assert(idx < size());
    return &list[idx];
  }
  /*
  Variant& Variant::operator=(const Variant& v){
    type = v.type;
    internal = v.internal;
    internal_map = v.internal_map;
    internal_list = v.internal_list;
    return *this;
  }
  */
  size_t Variant::size() const {   
    switch(type){
    case 0: return this->as<MapT>().size();
    case 1: return this->as<ListT>().size();
    case 2: return this->as<std::string>().size();
    default:
      return 0;
    }
  }
  ViewModel::Type Variant::getType() const {
    return (ViewModel::Type)this->type;
  }
  void* Variant::operator new(size_t size){
    Variant* storage = (Variant*)malloc(size);
    *(storage) = Variant();
    storage->managed = false;
    return storage;
  }
  void Variant::operator delete(void* ptr){
    free(ptr);
  }
} 
