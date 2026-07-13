/*
 * Entry: 00480556
 * Name: AudioMessageMgr::Save
 * Namespace: AudioMessageMgr
 * Signature: bool Save(AudioMessageMgr * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AudioMessageMgr::Save(AudioMessageMgr *this,_iobuf *param_1)

{
  list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *plVar1;
  char cVar2;
  AudMsgInfo *pAVar3;
  uint uVar4;
  bool bVar5;
  AudMsgInfo **ppAVar6;
  char *pcVar7;
  char (*pacVar8) [14];
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  uint local_c;
  char local_5;
  
  local_c = (this->msgList)._Mysize;
  if (10 < local_c) {
    local_c = 10;
  }
  local_5 = ::out(param_1,(int *)&local_c,4,"size");
  plVar1 = &this->msgList;
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->msgList)._Myhead)->_Next,plVar1);
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_1c,(this->msgList)._Myhead,plVar1);
  bVar5 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator==
                    (&local_14,&local_1c);
  uVar4 = local_c;
  do {
    local_c = uVar4;
    if ((bVar5) || (local_c = uVar4 - 1, (int)uVar4 < 1)) {
      if ((local_5 == '\0') || (bVar5 = ::out(param_1,this->lastMsg,0x10,"lastMsg"), !bVar5)) {
        bVar5 = false;
      }
      else {
        bVar5 = true;
      }
      return bVar5;
    }
    ppAVar6 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator*
                        (&local_14);
    pAVar3 = *ppAVar6;
    pcVar7 = pAVar3->msg;
    pacVar8 = msgNames;
    do {
      cVar2 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      (*pacVar8)[0] = cVar2;
      pacVar8 = (char (*) [14])((int)pacVar8 + 1);
    } while (cVar2 != '\0');
    if ((local_5 == '\0') || (bVar5 = ::out(param_1,&pAVar3->seqNo,4,"seqNo"), !bVar5)) {
LAB_00480625:
      local_5 = '\0';
    }
    else {
      bVar5 = ::out(param_1,msgNames,0xe,"msg");
      local_5 = '\x01';
      if (!bVar5) goto LAB_00480625;
    }
    std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator++(&local_14)
    ;
    std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_1c,(this->msgList)._Myhead,plVar1);
    bVar5 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator==
                      (&local_14,&local_1c);
    uVar4 = local_c;
  } while( true );
}
