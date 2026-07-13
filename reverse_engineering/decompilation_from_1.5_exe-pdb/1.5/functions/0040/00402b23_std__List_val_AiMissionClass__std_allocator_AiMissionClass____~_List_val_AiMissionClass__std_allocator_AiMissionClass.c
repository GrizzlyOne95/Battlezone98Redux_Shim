/*
 * Entry: 00402b23
 * Name: std::_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::~_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Namespace: std::_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: void ~_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>(_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
~_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
          (_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
