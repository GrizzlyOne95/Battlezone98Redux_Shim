/*
 * Entry: 00413bd7
 * Name: GotoTask::GotoTask
 * Namespace: GotoTask
 * Signature: GotoTask * GotoTask(GotoTask * this, Craft * param_1, AiPath * param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoTask * __thiscall GotoTask::GotoTask(GotoTask *this,Craft *param_1,AiPath *param_2,bool param_3)

{
  float fVar1;
  float *pfVar2;
  AiPath *pAVar3;
  VECTOR_2D VVar4;
  float local_8;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,(GameObject *)0x0);
  this->pathPoint = 0;
  this->exact = param_3;
  this->_padding_ = (int)&_vftable_;
  this->path = param_2;
  this->_padding_ = 1;
  this->_padding_ = 1;
  this->release = false;
  if ((AiPath *)param_1->_padding_ == param_2) {
    this->_padding_ = param_1->_padding_;
  }
  if (param_2 != (AiPath *)0x0) {
    fVar1 = param_2->points[param_2->pointCount + -1].z;
    (this->destPoint).x = param_2->points[param_2->pointCount + -1].x;
    (this->destPoint).y = 0.0;
    (this->destPoint).z = fVar1;
    if ((param_2 != (AiPath *)param_1->_padding_) && (param_2->label == (char *)0x0)) {
      pfVar2 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
      fVar1 = *pfVar2;
      VVar4.z = pfVar2[2];
      VVar4.x = fVar1;
      VVar4 = Vec2D_Subtract(*param_2->points,VVar4);
      local_8 = VVar4.z;
      if (SQRT(local_8 * local_8 + fVar1 * fVar1) < 1.0) {
        pAVar3 = operator_new(0x1c);
        if (pAVar3 == (AiPath *)0x0) {
          pAVar3 = (AiPath *)0x0;
        }
        else {
          pAVar3 = AiPath::AiPath(pAVar3,param_2->label,param_2->pointCount);
        }
        this->_padding_ = (int)pAVar3;
        memcpy(pAVar3->points,param_2->points,param_2->pointCount << 3);
      }
    }
  }
  this->skipdone = false;
  return this;
}
