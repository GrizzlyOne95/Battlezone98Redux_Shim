/*
 * Entry: 004808f7
 * Name: AudioMessageMgr::Stop
 * Namespace: AudioMessageMgr
 * Signature: void Stop(AudioMessageMgr * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AudioMessageMgr::Stop(AudioMessageMgr *this,int param_1)

{
  list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this_00;
  AudMsgInfo *pAVar1;
  _Const_iterator<1> _Var2;
  bool bVar3;
  AudMsgInfo **ppAVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  if (param_1 != 0) {
    if (param_1 == this->curSeqNo) {
      MessageDone(this,this->curObj);
    }
    else {
      this_00 = &this->msgList;
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_c,((this->msgList)._Myhead)->_Next,this_00);
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,(this->msgList)._Myhead,this_00);
      bVar3 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
      while (!bVar3) {
        ppAVar4 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::
                  operator*(&local_c);
        pAVar1 = *ppAVar4;
        if (pAVar1->seqNo == param_1) {
          _Var2._Ptr = (_Node *)local_c._padding_;
          _Var2._padding_ = (int)&local_14;
          std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::erase(this_00,_Var2);
          operator_delete(pAVar1);
          return;
        }
        std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator++
                  (&local_c);
        std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::
        _Const_iterator<1>(&local_14,(this->msgList)._Myhead,this_00);
        bVar3 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::
                operator==(&local_c,&local_14);
      }
    }
  }
  return;
}
