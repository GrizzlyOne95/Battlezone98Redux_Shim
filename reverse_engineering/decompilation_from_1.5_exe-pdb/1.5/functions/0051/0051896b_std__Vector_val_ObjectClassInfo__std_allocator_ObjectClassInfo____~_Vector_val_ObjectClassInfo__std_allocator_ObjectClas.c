/*
 * Entry: 0051896b
 * Name: std::_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::~_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: std::_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void ~_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
~_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
          (_Vector_val<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
