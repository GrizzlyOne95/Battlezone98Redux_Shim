/*
 * Entry: 00404538
 * Name: AiTask::PostLoadAll
 * Namespace: AiTask
 * Signature: bool PostLoadAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiTask::PostLoadAll(void)

{
  bool bVar1;
  char cVar2;
  AiTask **ppAVar3;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  cVar2 = '\x01';
  bVar1 = true;
  if (tasklist != (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
    std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,tasklist->_Myhead->_Next,tasklist);
    local_c._padding_ = local_14._padding_;
    local_c._Ptr = local_14._Ptr;
    do {
      std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,tasklist->_Myhead,tasklist);
      bVar1 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
      if (bVar1) {
        return (bool)cVar2;
      }
      ppAVar3 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator*
                          (&local_c);
      cVar2 = (**(code **)((*ppAVar3)->_padding_ + 8))();
      std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator++(&local_c);
      bVar1 = false;
    } while (cVar2 != '\0');
  }
  return bVar1;
}
