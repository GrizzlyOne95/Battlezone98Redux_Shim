/*
 * Entry: 005166d1
 * Name: FindSendPoints::FindSendPoints
 * Namespace: FindSendPoints
 * Signature: FindSendPoints * FindSendPoints(FindSendPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FindSendPoints * __thiscall FindSendPoints::FindSendPoints(FindSendPoints *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->row = -1;
  this->col = -1;
  this->i = -1;
  sendPoints = (long *)0x0;
  this->_padding_ = (int)&_vftable_;
  loadedAIP = true;
  return this;
}
