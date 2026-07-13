/*
 * Entry: 005576ab
 * Name: std::_Vector_val<Session_*,std::allocator<Session_*>_>::~_Vector_val<Session_*,std::allocator<Session_*>_>
 * Namespace: std::_Vector_val<Session_*,std::allocator<Session_*>_>
 * Signature: void ~_Vector_val<Session_*,std::allocator<Session_*>_>(_Vector_val<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Session_*,std::allocator<Session_*>_>::
~_Vector_val<Session_*,std::allocator<Session_*>_>
          (_Vector_val<Session_*,std::allocator<Session_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
