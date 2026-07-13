/*
 * Entry: 0040442e
 * Name: AiTask::SaveAll
 * Namespace: AiTask
 * Signature: bool SaveAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiTask::SaveAll(_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  AiTask **ppAVar3;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  int local_8;
  
  bVar1 = ::out(param_1,"[AiTasks]");
  bVar2 = false;
  if (bVar1) {
    local_8 = 0;
    if (tasklist != (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
      std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_18,tasklist->_Myhead->_Next,tasklist);
      local_10._padding_ = local_18._padding_;
      local_10._Ptr = local_18._Ptr;
      while( true ) {
        std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,tasklist->_Myhead,tasklist);
        bVar2 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar2) break;
        ppAVar3 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator*
                            (&local_10);
        if ((char)(*ppAVar3)->_padding_ == '\0') {
          local_8 = local_8 + 1;
        }
        std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator++(&local_10);
      }
    }
    bVar2 = ::out(param_1,&local_8,4,"count");
    if (tasklist != (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
      std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_18,tasklist->_Myhead->_Next,tasklist);
      local_10._padding_ = local_18._padding_;
      local_10._Ptr = local_18._Ptr;
      bVar1 = bVar2;
      while (bVar2 = false, bVar1 != false) {
        std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,tasklist->_Myhead,tasklist);
        bVar2 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar2) {
          return bVar1;
        }
        ppAVar3 = std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator*
                            (&local_10);
        bVar1 = RtimeClass::Save(param_1,(SObject *)*ppAVar3);
        std::list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator++(&local_10);
      }
    }
  }
  return bVar2;
}
