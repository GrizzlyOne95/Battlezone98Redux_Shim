/*
 * Entry: 005581c5
 * Name: std::vector<Server_*,std::allocator<Server_*>_>::~vector<Server_*,std::allocator<Server_*>_>
 * Namespace: std::vector<Server_*,std::allocator<Server_*>_>
 * Signature: void ~vector<Server_*,std::allocator<Server_*>_>(vector<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Server_*,std::allocator<Server_*>_>::~vector<Server_*,std::allocator<Server_*>_>
          (vector<Server_*,std::allocator<Server_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
