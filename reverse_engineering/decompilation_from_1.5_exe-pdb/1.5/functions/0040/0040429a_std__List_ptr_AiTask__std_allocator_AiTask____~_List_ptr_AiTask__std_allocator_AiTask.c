/*
 * Entry: 0040429a
 * Name: std::_List_ptr<AiTask_*,std::allocator<AiTask_*>_>::~_List_ptr<AiTask_*,std::allocator<AiTask_*>_>
 * Namespace: std::_List_ptr<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: void ~_List_ptr<AiTask_*,std::allocator<AiTask_*>_>(_List_ptr<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AiTask_*,std::allocator<AiTask_*>_>::~_List_ptr<AiTask_*,std::allocator<AiTask_*>_>
          (_List_ptr<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
