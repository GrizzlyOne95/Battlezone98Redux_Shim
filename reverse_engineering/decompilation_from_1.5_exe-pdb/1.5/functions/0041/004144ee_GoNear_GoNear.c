/*
 * Entry: 004144ee
 * Name: GoNear::GoNear
 * Namespace: GoNear
 * Signature: GoNear * GoNear(GoNear * this, Craft * param_1, GameObject * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoNear * __thiscall GoNear::GoNear(GoNear *this,Craft *param_1,GameObject *param_2,float param_3)

{
  Craft *pCVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  
  pCVar1 = param_1;
  if (param_2 != (GameObject *)0x0) {
    pCVar1 = (Craft *)param_2;
  }
  pVVar2 = (VECTOR_3D *)(**(code **)(pCVar1->_padding_ + 0xc))();
  GotoTask::GotoTask((GotoTask *)this,param_1,pVVar2);
  this->_padding_ = (int)&_vftable_;
  if (param_2 == (GameObject *)0x0) {
    this->_padding_ = 0xd;
  }
  else {
    iVar3 = GameObject::GetHandle(param_2);
    this->_padding_ = iVar3;
    *(undefined1 *)((int)&this->_padding_ + 2) = 1;
    this->wasNear = false;
    this->nearSq = param_3 * param_3;
    this->nearTime = 0.0;
  }
  return this;
}
