/*
 * Entry: 004022a3
 * Name: std::_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::~_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Namespace: std::_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: void ~_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>(_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
~_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
          (_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
