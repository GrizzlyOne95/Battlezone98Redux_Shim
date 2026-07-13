/*
 * Entry: 004d031a
 * Name: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Tidy
 * Namespace: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Signature: void _Tidy(list<AdjustItem_*,std::allocator<AdjustItem_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Tidy
          (list<AdjustItem_*,std::allocator<AdjustItem_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
