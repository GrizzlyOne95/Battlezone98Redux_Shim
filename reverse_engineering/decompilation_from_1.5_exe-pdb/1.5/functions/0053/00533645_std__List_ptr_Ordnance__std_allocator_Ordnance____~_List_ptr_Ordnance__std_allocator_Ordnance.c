/*
 * Entry: 00533645
 * Name: std::_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>::~_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>
 * Namespace: std::_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: void ~_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>(_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>::
~_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_>
          (_List_ptr<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
