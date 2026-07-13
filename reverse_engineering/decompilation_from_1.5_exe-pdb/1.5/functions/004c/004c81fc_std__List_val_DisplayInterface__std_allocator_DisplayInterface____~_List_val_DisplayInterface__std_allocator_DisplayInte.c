/*
 * Entry: 004c81fc
 * Name: std::_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::~_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Namespace: std::_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: void ~_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>(_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
~_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
          (_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
