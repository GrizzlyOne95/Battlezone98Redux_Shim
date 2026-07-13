/*
 * Entry: 004d055e
 * Name: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::~list<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Namespace: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Signature: void ~list<AdjustItem_*,std::allocator<AdjustItem_*>_>(list<AdjustItem_*,std::allocator<AdjustItem_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::
~list<AdjustItem_*,std::allocator<AdjustItem_*>_>
          (list<AdjustItem_*,std::allocator<AdjustItem_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
