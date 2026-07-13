/*
 * Entry: 00518dda
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::~vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void ~vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
~vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
