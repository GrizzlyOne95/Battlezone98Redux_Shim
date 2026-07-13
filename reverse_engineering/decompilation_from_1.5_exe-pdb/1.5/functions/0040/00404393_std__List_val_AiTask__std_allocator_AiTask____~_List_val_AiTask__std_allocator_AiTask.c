/*
 * Entry: 00404393
 * Name: std::_List_val<AiTask_*,std::allocator<AiTask_*>_>::~_List_val<AiTask_*,std::allocator<AiTask_*>_>
 * Namespace: std::_List_val<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: void ~_List_val<AiTask_*,std::allocator<AiTask_*>_>(_List_val<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<AiTask_*,std::allocator<AiTask_*>_>::~_List_val<AiTask_*,std::allocator<AiTask_*>_>
          (_List_val<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
