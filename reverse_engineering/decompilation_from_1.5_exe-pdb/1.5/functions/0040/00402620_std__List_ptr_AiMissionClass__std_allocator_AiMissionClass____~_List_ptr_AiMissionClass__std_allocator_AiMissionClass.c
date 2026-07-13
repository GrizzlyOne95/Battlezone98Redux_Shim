/*
 * Entry: 00402620
 * Name: std::_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::~_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Namespace: std::_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: void ~_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>(_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
~_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
          (_List_ptr<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
