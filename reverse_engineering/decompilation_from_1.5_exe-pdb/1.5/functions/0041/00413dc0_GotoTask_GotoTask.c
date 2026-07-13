/*
 * Entry: 00413dc0
 * Name: GotoTask::GotoTask
 * Namespace: GotoTask
 * Signature: GotoTask * GotoTask(GotoTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoTask * __thiscall GotoTask::GotoTask(GotoTask *this,Craft *param_1,GameObject *param_2)

{
  float *pfVar1;
  AiPath *pAVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  VECTOR_3D *pVVar5;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  this->_padding_ = (int)&_vftable_;
  if (param_2 == (GameObject *)0x0) {
    this->path = (AiPath *)0x0;
    this->pathPoint = 0;
    this->_padding_ = 0xd;
    this->_padding_ = 0xd;
    this->release = false;
  }
  else {
    this->_padding_ = 1;
    this->_padding_ = 1;
    pfVar1 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
    (this->destPoint).x = *pfVar1;
    (this->destPoint).y = pfVar1[1];
    (this->destPoint).z = pfVar1[2];
    pAVar2 = operator_new(0x1c);
    if (pAVar2 == (AiPath *)0x0) {
      pAVar2 = (AiPath *)0x0;
    }
    else {
      pVVar5 = &this->destPoint;
      pVVar3 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
      pAVar2 = AiPath::AiPath(pAVar2,pVVar3,pVVar5);
    }
    this->pathPoint = 0;
    this->path = pAVar2;
    this->release = true;
    this->exact = true;
    this->skipdone = false;
    iVar4 = GameObject::GetHandle(param_2);
    this->_padding_ = iVar4;
  }
  return this;
}
