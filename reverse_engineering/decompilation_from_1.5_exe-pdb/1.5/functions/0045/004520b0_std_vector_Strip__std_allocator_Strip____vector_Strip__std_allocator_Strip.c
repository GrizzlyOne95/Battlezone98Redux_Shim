/*
 * Entry: 004520b0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::vector<Strip_*,std::allocator<Strip_*>_>
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: vector<Strip_*,std::allocator<Strip_*>_> * vector<Strip_*,std::allocator<Strip_*>_>(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<Strip_*,std::allocator<Strip_*>_> * __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::vector<Strip_*,std::allocator<Strip_*>_>
          (vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = this;
    this->_padding_ = (int)puVar1;
    this->_Myfirst = (Strip **)0x0;
    this->_Mylast = (Strip **)0x0;
    this->_Myend = (Strip **)0x0;
    return this;
  }
  this->_padding_ = 0;
  this->_Myfirst = (Strip **)0x0;
  this->_Mylast = (Strip **)0x0;
  this->_Myend = (Strip **)0x0;
  return this;
}
