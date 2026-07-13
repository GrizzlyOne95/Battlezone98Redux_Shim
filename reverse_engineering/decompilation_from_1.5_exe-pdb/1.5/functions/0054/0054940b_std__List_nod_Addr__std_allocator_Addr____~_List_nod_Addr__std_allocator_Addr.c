/*
 * Entry: 0054940b
 * Name: std::_List_nod<Addr_*,std::allocator<Addr_*>_>::~_List_nod<Addr_*,std::allocator<Addr_*>_>
 * Namespace: std::_List_nod<Addr_*,std::allocator<Addr_*>_>
 * Signature: void ~_List_nod<Addr_*,std::allocator<Addr_*>_>(_List_nod<Addr_*,std::allocator<Addr_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<Addr_*,std::allocator<Addr_*>_>::~_List_nod<Addr_*,std::allocator<Addr_*>_>
          (_List_nod<Addr_*,std::allocator<Addr_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
