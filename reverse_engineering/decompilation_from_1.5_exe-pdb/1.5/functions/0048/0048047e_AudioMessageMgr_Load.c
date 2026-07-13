/*
 * Entry: 0048047e
 * Name: AudioMessageMgr::Load
 * Namespace: AudioMessageMgr
 * Signature: bool Load(AudioMessageMgr * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AudioMessageMgr::Load(AudioMessageMgr *this,_iobuf *param_1)

{
  bool bVar1;
  AudMsgInfo *pAVar2;
  int local_18;
  AudMsgInfo *local_14;
  int local_10;
  char (*local_c) [14];
  char local_5;
  
  local_5 = ::in(param_1,&local_18,4);
  local_10 = 0;
  if (0 < local_18) {
    local_c = msgNames;
    do {
      pAVar2 = operator_new(8);
      if (pAVar2 == (AudMsgInfo *)0x0) {
        pAVar2 = (AudMsgInfo *)0x0;
      }
      else {
        pAVar2->msg = (char *)0x0;
        pAVar2->seqNo = 0;
      }
      local_14 = pAVar2;
      if ((local_5 == '\0') || (bVar1 = ::in(param_1,&pAVar2->seqNo,4), !bVar1)) {
LAB_00480503:
        local_5 = '\0';
      }
      else {
        bVar1 = ::in(param_1,local_c,0xe);
        local_5 = '\x01';
        if (!bVar1) goto LAB_00480503;
      }
      pAVar2->msg = *local_c;
      std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::push_back(&this->msgList,&local_14);
      local_c = local_c + 1;
      local_10 = local_10 + 1;
      this->seqNo = pAVar2->seqNo + 1;
    } while (local_10 < local_18);
  }
  if ((local_5 == '\0') || (bVar1 = ::in(param_1,this->lastMsg,0x10), !bVar1)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}
