/*
 * Entry: 00450eb0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Tidy
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void _Tidy(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Tidy(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  if (this->_Myfirst != (Strip **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Strip **)0x0;
  this->_Mylast = (Strip **)0x0;
  this->_Myend = (Strip **)0x0;
  return;
}
