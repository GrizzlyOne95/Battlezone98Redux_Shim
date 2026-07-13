/*
 * Entry: 00413eb1
 * Name: GotoTask::ChoosePathPoint
 * Namespace: GotoTask
 * Signature: void ChoosePathPoint(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoTask::ChoosePathPoint(GotoTask *this)

{
  VECTOR_2D *pVVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  AiPath *pAVar5;
  VECTOR_3D *pVVar6;
  int iVar7;
  VECTOR_3D *pVVar8;
  float local_c;
  int local_8;
  
  local_c = 1e+30;
  iVar7 = -1;
  local_8 = -1;
  if (this->path == (AiPath *)0x0) {
    pAVar5 = operator_new(0x1c);
    if (pAVar5 == (AiPath *)0x0) {
      pAVar5 = (AiPath *)0x0;
    }
    else {
      pVVar8 = &this->destPoint;
      pVVar6 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pAVar5 = AiPath::AiPath(pAVar5,pVVar6,pVVar8);
    }
    this->pathPoint = 0;
    this->path = pAVar5;
    this->release = true;
  }
  pAVar5 = this->path;
  if (this->pathPoint < pAVar5->pointCount) {
    do {
      iVar2 = this->pathPoint;
      fVar3 = (float)this->_padding_ - pAVar5->points[iVar2].x;
      fVar4 = (float)this->_padding_ - pAVar5->points[iVar2].z;
      fVar3 = fVar4 * fVar4 + fVar3 * fVar3;
      if (fVar3 < local_c) {
        iVar7 = iVar2;
        local_c = fVar3;
        local_8 = iVar2;
      }
      this->pathPoint = iVar2 + 1;
    } while (iVar2 + 1 < pAVar5->pointCount);
  }
  if (iVar7 == pAVar5->pointCount + -1) {
    this->pathPoint = iVar7;
  }
  else {
    pVVar1 = pAVar5->points + iVar7;
    if (0.0 <= ((float)this->_padding_ - pVVar1->z) * (pVVar1[1].z - pVVar1->z) +
               ((float)this->_padding_ - pVVar1->x) * (pVVar1[1].x - pVVar1->x) +
               (float)this->_padding_ * 0.0) {
      local_8 = local_8 + 1;
    }
    this->pathPoint = local_8;
  }
  return;
}
