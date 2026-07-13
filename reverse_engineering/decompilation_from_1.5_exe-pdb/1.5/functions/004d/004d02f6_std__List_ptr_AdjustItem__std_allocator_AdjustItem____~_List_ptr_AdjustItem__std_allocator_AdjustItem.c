/*
 * Entry: 004d02f6
 * Name: std::_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>::~_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Namespace: std::_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Signature: void ~_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>(_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>::
~_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_>
          (_List_ptr<AdjustItem_*,std::allocator<AdjustItem_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
