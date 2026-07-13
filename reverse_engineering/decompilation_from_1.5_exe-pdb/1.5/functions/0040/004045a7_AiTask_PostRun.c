/*
 * Entry: 004045a7
 * Name: AiTask::PostRun
 * Namespace: AiTask
 * Signature: void PostRun(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiTask::PostRun(void)

{
  list<AiTask_*,std::allocator<AiTask_*>_> *this;
  AiTask **ppAVar1;
  
  this = tasklist;
  if (tasklist != (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
    while (this->_Mysize != 0) {
      ppAVar1 = std::list<AiTask_*,std::allocator<AiTask_*>_>::back(this);
      if (*ppAVar1 != (AiTask *)0x0) {
        (**(code **)(*ppAVar1)->_padding_)(1);
      }
    }
  }
  return;
}
