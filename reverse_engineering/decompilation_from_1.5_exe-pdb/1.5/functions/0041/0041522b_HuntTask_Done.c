/*
 * Entry: 0041522b
 * Name: HuntTask::Done
 * Namespace: HuntTask
 * Signature: bool Done(HuntTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HuntTask::Done(HuntTask *this)

{
  if ((this->_padding_ != 0xd) &&
     ((this->_padding_ == 0 || (*(int *)(this->_padding_ + 0x10) != 3)))) {
    return false;
  }
  return true;
}
