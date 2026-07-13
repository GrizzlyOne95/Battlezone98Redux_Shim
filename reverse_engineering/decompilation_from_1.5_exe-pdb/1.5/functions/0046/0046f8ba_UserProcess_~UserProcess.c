/*
 * Entry: 0046f8ba
 * Name: UserProcess::~UserProcess
 * Namespace: UserProcess
 * Signature: void ~UserProcess(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UserProcess::~UserProcess(UserProcess *this)

{
  Carrier *this_00;
  
  this->_padding_ = (int)&_vftable_;
  this_00 = *(Carrier **)(this->_padding_ + 0x198);
  if (this_00 != (Carrier *)0x0) {
    Carrier::SetSelected(this_00,0);
  }
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
