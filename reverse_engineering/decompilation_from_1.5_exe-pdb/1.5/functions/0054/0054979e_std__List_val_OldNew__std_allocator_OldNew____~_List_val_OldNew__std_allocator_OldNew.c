/*
 * Entry: 0054979e
 * Name: std::_List_val<OldNew_*,std::allocator<OldNew_*>_>::~_List_val<OldNew_*,std::allocator<OldNew_*>_>
 * Namespace: std::_List_val<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: void ~_List_val<OldNew_*,std::allocator<OldNew_*>_>(_List_val<OldNew_*,std::allocator<OldNew_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<OldNew_*,std::allocator<OldNew_*>_>::~_List_val<OldNew_*,std::allocator<OldNew_*>_>
          (_List_val<OldNew_*,std::allocator<OldNew_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
