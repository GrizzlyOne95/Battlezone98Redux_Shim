/*
 * Entry: 004803b5
 * Name: AudioMessageMgr::Insert
 * Namespace: AudioMessageMgr
 * Signature: int Insert(AudioMessageMgr * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AudioMessageMgr::Insert(AudioMessageMgr *this,char *param_1)

{
  AudioMessageMgr *pAVar1;
  AudioMessageMgr *local_8;
  
  local_8 = this;
  pAVar1 = operator_new(8);
  if (pAVar1 == (AudioMessageMgr *)0x0) {
    pAVar1 = (AudioMessageMgr *)0x0;
  }
  else {
    pAVar1->_padding_ = 0;
    pAVar1->_padding_ = 0;
  }
  pAVar1->_padding_ = (int)param_1;
  pAVar1->_padding_ = this->seqNo;
  this->seqNo = this->seqNo + 1;
  local_8 = pAVar1;
  std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::push_back
            (&this->msgList,(AudMsgInfo **)&local_8);
  return pAVar1->_padding_;
}
