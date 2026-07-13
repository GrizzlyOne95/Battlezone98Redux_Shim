/*
 * Entry: 00402288
 * Name: std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::~_List_nod<AiPath_*,std::allocator<AiPath_*>_>
 * Namespace: std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: void ~_List_nod<AiPath_*,std::allocator<AiPath_*>_>(_List_nod<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<AiPath_*,std::allocator<AiPath_*>_>::~_List_nod<AiPath_*,std::allocator<AiPath_*>_>
          (_List_nod<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
