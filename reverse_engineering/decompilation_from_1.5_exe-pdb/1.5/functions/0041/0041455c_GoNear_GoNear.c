/*
 * Entry: 0041455c
 * Name: GoNear::GoNear
 * Namespace: GoNear
 * Signature: GoNear * GoNear(GoNear * this, Craft * param_1, GameObject * param_2, AiPath * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoNear * __thiscall
GoNear::GoNear(GoNear *this,Craft *param_1,GameObject *param_2,AiPath *param_3,float param_4)

{
  int iVar1;
  
  GotoTask::GotoTask((GotoTask *)this,param_1,param_3,false);
  this->_padding_ = (int)&_vftable_;
  if (param_2 == (GameObject *)0x0) {
    this->_padding_ = 0xd;
  }
  else {
    iVar1 = GameObject::GetHandle(param_2);
    this->_padding_ = iVar1;
    *(undefined1 *)((int)&this->_padding_ + 2) = 1;
    this->wasNear = false;
    this->nearSq = param_4 * param_4;
    this->nearTime = 0.0;
  }
  return this;
}
