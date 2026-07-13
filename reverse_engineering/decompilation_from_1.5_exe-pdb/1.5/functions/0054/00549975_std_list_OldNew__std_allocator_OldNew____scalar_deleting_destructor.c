/*
 * Entry: 00549975
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::`scalar_deleting_destructor'
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: void * `scalar_deleting_destructor'(list<OldNew_*,std::allocator<OldNew_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::_scalar_deleting_destructor_
          (list<OldNew_*,std::allocator<OldNew_*>_> *this,uint param_1)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
