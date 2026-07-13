/*
 * Entry: 005498c2
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::~list<OldNew_*,std::allocator<OldNew_*>_>
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: void ~list<OldNew_*,std::allocator<OldNew_*>_>(list<OldNew_*,std::allocator<OldNew_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::~list<OldNew_*,std::allocator<OldNew_*>_>
          (list<OldNew_*,std::allocator<OldNew_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
