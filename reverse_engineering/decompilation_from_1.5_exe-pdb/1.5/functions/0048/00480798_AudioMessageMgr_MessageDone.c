/*
 * Entry: 00480798
 * Name: AudioMessageMgr::MessageDone
 * Namespace: AudioMessageMgr
 * Signature: int MessageDone(AudioMessageMgr * this, _gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AudioMessageMgr::MessageDone(AudioMessageMgr *this,_gas_object *param_1)

{
  AudMsgInfo **ppAVar1;
  
  StopGASEvent(this->curObj);
  this->curObj = (_gas_object *)0x0;
  this->curSeqNo = 0;
  ppAVar1 = std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::front(&this->msgList);
  operator_delete(*ppAVar1);
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::pop_front(&this->msgList);
  this->playing = false;
  return 0;
}
