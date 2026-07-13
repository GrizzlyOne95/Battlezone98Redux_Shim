/*
 * Entry: 00451470
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::~vector<Strip_*,std::allocator<Strip_*>_>
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void ~vector<Strip_*,std::allocator<Strip_*>_>(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::~vector<Strip_*,std::allocator<Strip_*>_>
          (vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  if (this->_Myfirst != (Strip **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Strip **)0x0;
  this->_Mylast = (Strip **)0x0;
  this->_Myend = (Strip **)0x0;
  operator_delete((void *)this->_padding_);
  return;
}
