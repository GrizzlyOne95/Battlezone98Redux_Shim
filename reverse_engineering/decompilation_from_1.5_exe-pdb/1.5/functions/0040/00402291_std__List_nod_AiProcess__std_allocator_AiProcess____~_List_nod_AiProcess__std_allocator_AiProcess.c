/*
 * Entry: 00402291
 * Name: std::_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>::~_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>
 * Namespace: std::_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void ~_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>(_List_nod<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>::
~_List_nod<AiProcess_*,std::allocator<AiProcess_*>_>
          (_List_nod<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
