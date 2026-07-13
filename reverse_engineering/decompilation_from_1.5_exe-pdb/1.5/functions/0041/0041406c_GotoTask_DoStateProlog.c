/*
 * Entry: 0041406c
 * Name: GotoTask::DoStateProlog
 * Namespace: GotoTask
 * Signature: bool DoStateProlog(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoTask::DoStateProlog(GotoTask *this)

{
  GameObject *pGVar1;
  
  if (this->_padding_ == 0xd) {
    return false;
  }
  this->_padding_ = 0;
  pGVar1 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar1;
  pGVar1 = AvoidObject((GameObject *)this->_padding_,pGVar1);
  this->_padding_ = (int)pGVar1;
  return true;
}
