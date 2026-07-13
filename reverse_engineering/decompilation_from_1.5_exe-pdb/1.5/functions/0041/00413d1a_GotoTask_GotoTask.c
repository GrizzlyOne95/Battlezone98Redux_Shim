/*
 * Entry: 00413d1a
 * Name: GotoTask::GotoTask
 * Namespace: GotoTask
 * Signature: GotoTask * GotoTask(GotoTask * this, Craft * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoTask * __thiscall GotoTask::GotoTask(GotoTask *this,Craft *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  AiPath *pAVar3;
  VECTOR_3D *pVVar4;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,(GameObject *)0x0);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 1;
  this->_padding_ = 1;
  pAVar3 = operator_new(0x1c);
  if (pAVar3 == (AiPath *)0x0) {
    pAVar3 = (AiPath *)0x0;
  }
  else {
    pVVar4 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
    pAVar3 = AiPath::AiPath(pAVar3,pVVar4,param_2);
  }
  this->pathPoint = 0;
  this->path = pAVar3;
  this->release = true;
  fVar1 = pAVar3->points[pAVar3->pointCount + -1].x;
  fVar2 = pAVar3->points[pAVar3->pointCount + -1].z;
  this->exact = true;
  this->skipdone = false;
  (this->destPoint).x = fVar1;
  (this->destPoint).y = 0.0;
  (this->destPoint).z = fVar2;
  return this;
}
