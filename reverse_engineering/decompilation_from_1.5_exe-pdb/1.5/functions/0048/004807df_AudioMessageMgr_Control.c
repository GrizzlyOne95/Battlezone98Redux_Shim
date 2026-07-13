/*
 * Entry: 004807df
 * Name: AudioMessageMgr::Control
 * Namespace: AudioMessageMgr
 * Signature: void Control(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall AudioMessageMgr::Control(AudioMessageMgr *this)

{
  char cVar1;
  AudMsgInfo *pAVar2;
  AudMsgInfo **ppAVar3;
  _gas_object *p_Var4;
  char *pcVar5;
  char *pcVar6;
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((this->playing == false) && ((this->msgList)._Mysize != 0)) {
    ppAVar3 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::front(&this->msgList);
    pAVar2 = *ppAVar3;
    InitGASCtrl(&local_34);
    InitGASPrep(&local_50);
    local_34.eofCallback = AudioMessageDone;
    local_34.flags = 5;
    local_50.pri = 10000;
    p_Var4 = StartGASEvent(pAVar2->msg,(_OBJ76 *)0x0,&local_34,&local_50);
    this->curObj = p_Var4;
    if (p_Var4 == (_gas_object *)0x0) {
      Trace("AudioMessage %s - not played\n");
      operator_delete(pAVar2);
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::pop_front(&this->msgList);
    }
    else {
      pcVar5 = pAVar2->msg;
      pcVar6 = this->lastMsg;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        *pcVar6 = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      this->curObj->user = (long)&msgMgr;
      this->curSeqNo = pAVar2->seqNo;
      this->playing = true;
    }
  }
  return;
}
