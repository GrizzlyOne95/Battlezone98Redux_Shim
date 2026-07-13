/*
 * Entry: 0048072c
 * Name: AudioMessageMgr::AudioMessageMgr
 * Namespace: AudioMessageMgr
 * Signature: AudioMessageMgr * AudioMessageMgr(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AudioMessageMgr * __thiscall AudioMessageMgr::AudioMessageMgr(AudioMessageMgr *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  this->_padding_ = (int)&_vftable_;
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::
  list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>(&this->msgList);
  return this;
}
