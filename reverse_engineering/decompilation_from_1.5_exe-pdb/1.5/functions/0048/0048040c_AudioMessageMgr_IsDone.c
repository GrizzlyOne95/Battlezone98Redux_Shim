/*
 * Entry: 0048040c
 * Name: AudioMessageMgr::IsDone
 * Namespace: AudioMessageMgr
 * Signature: bool IsDone(AudioMessageMgr * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AudioMessageMgr::IsDone(AudioMessageMgr *this,int param_1)

{
  bool bVar1;
  AudMsgInfo **ppAVar2;
  _Node *p_Var3;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  if (param_1 == 0) {
    bVar1 = true;
  }
  else if (param_1 == this->curSeqNo) {
    bVar1 = false;
  }
  else {
    std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,((this->msgList)._Myhead)->_Next,&this->msgList);
    p_Var3 = (this->msgList)._Myhead;
    while( true ) {
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,p_Var3,&this->msgList);
      bVar1 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
      if (bVar1) break;
      ppAVar2 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator*
                          (&local_c);
      if ((*ppAVar2)->seqNo == param_1) {
        return false;
      }
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator++
                (&local_c);
      p_Var3 = (this->msgList)._Myhead;
    }
    bVar1 = true;
  }
  return bVar1;
}
