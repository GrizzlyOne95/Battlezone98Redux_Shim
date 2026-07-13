/*
 * Entry: 004803a0
 * Name: AudioMessageMgr::~AudioMessageMgr
 * Namespace: AudioMessageMgr
 * Signature: void ~AudioMessageMgr(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AudioMessageMgr::~AudioMessageMgr(AudioMessageMgr *this)

{
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Tidy(&this->msgList);
  operator_delete((void *)(this->msgList)._padding_);
  return;
}
