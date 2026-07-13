/*
 * Entry: 0046f76c
 * Name: UserProcess::UserProcess
 * Namespace: UserProcess
 * Signature: UserProcess * UserProcess(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UserProcess * __thiscall UserProcess::UserProcess(UserProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->cycle = 0;
  this->linked = 0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
