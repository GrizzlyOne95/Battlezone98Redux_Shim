/*
 * Entry: 004808a6
 * Name: AudioMessageMgr::PostRun
 * Namespace: AudioMessageMgr
 * Signature: void PostRun(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AudioMessageMgr::PostRun(AudioMessageMgr *this)

{
  AudMsgInfo *pAVar1;
  AudMsgInfo **ppAVar2;
  _gas_object *p_Var3;
  
  if ((this->msgList)._Mysize != 0) {
    do {
      ppAVar2 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::front(&this->msgList);
      pAVar1 = *ppAVar2;
      p_Var3 = FindGASObjectByName(pAVar1->msg);
      if (p_Var3 != (_gas_object *)0x0) {
        StopGASEvent(p_Var3);
      }
      operator_delete(pAVar1);
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::pop_front(&this->msgList);
    } while ((this->msgList)._Mysize != 0);
  }
  this->playing = false;
  this->seqNo = 1;
  this->lastMsg[0] = '\0';
  return;
}
