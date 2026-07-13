/*
 * Entry: 0040e1a8
 * Name: std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::~_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>
 * Namespace: std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: void ~_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>(_List_nod<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::
~_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>
          (_List_nod<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
