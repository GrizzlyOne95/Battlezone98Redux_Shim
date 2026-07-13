/*
 * Entry: 00549951
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::`scalar_deleting_destructor'
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: void * `scalar_deleting_destructor'(list<Addr_*,std::allocator<Addr_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::_scalar_deleting_destructor_
          (list<Addr_*,std::allocator<Addr_*>_> *this,uint param_1)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
