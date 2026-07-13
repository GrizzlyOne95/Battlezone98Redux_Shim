/*
 * Entry: 0040260e
 * Name: std::_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>::~_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>
 * Namespace: std::_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void ~_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>(_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>::
~_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_>
          (_List_ptr<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
