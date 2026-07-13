/*
 * Entry: 0040229a
 * Name: std::_List_nod<AOI_*,std::allocator<AOI_*>_>::~_List_nod<AOI_*,std::allocator<AOI_*>_>
 * Namespace: std::_List_nod<AOI_*,std::allocator<AOI_*>_>
 * Signature: void ~_List_nod<AOI_*,std::allocator<AOI_*>_>(_List_nod<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<AOI_*,std::allocator<AOI_*>_>::~_List_nod<AOI_*,std::allocator<AOI_*>_>
          (_List_nod<AOI_*,std::allocator<AOI_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
