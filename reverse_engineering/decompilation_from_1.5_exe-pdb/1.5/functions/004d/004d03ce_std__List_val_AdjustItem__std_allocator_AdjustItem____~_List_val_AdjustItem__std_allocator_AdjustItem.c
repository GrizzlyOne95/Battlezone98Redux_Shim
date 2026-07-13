/*
 * Entry: 004d03ce
 * Name: std::_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>::~_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Namespace: std::_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Signature: void ~_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>(_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>::
~_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>
          (_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
