/*
 * Entry: 005576a2
 * Name: std::_Vector_val<Server_*,std::allocator<Server_*>_>::~_Vector_val<Server_*,std::allocator<Server_*>_>
 * Namespace: std::_Vector_val<Server_*,std::allocator<Server_*>_>
 * Signature: void ~_Vector_val<Server_*,std::allocator<Server_*>_>(_Vector_val<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Server_*,std::allocator<Server_*>_>::
~_Vector_val<Server_*,std::allocator<Server_*>_>
          (_Vector_val<Server_*,std::allocator<Server_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
