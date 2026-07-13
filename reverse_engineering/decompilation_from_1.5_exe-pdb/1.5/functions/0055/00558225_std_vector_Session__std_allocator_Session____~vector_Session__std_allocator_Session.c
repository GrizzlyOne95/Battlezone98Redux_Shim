/*
 * Entry: 00558225
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::~vector<Session_*,std::allocator<Session_*>_>
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: void ~vector<Session_*,std::allocator<Session_*>_>(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::~vector<Session_*,std::allocator<Session_*>_>
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
