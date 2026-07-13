/*
 * Entry: 00451600
 * Name: std::_Vector_val<Strip_*,std::allocator<Strip_*>_>::_Vector_val<Strip_*,std::allocator<Strip_*>_>
 * Namespace: std::_Vector_val<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_val<Strip_*,std::allocator<Strip_*>_> * _Vector_val<Strip_*,std::allocator<Strip_*>_>(_Vector_val<Strip_*,std::allocator<Strip_*>_> * this, allocator<Strip_*> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_val<Strip_*,std::allocator<Strip_*>_> * __thiscall
std::_Vector_val<Strip_*,std::allocator<Strip_*>_>::_Vector_val<Strip_*,std::allocator<Strip_*>_>
          (_Vector_val<Strip_*,std::allocator<Strip_*>_> *this,allocator<Strip_*> param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = this;
    this->_padding_ = (int)puVar1;
    return this;
  }
  this->_padding_ = 0;
  return this;
}
