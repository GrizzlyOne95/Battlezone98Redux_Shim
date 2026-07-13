/*
 * Entry: 00451f80
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::`scalar_deleting_destructor'
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void * `scalar_deleting_destructor'(vector<Strip_*,std::allocator<Strip_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_scalar_deleting_destructor_
          (vector<Strip_*,std::allocator<Strip_*>_> *this,uint param_1)

{
  if (this->_Myfirst != (Strip **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Strip **)0x0;
  this->_Mylast = (Strip **)0x0;
  this->_Myend = (Strip **)0x0;
  operator_delete((void *)this->_padding_);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
