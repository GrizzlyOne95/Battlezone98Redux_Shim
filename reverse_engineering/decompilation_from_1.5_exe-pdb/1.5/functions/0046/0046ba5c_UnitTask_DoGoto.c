/*
 * Entry: 0046ba5c
 * Name: UnitTask::DoGoto
 * Namespace: UnitTask
 * Signature: void DoGoto(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoGoto(UnitTask *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  VECTOR_2D *pVVar4;
  bool bVar5;
  float *pfVar6;
  int iVar7;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  char local_5;
  
  if (this->plan->pointCount + -1 <= this->planPoint) goto LAB_0046bc4a;
  pfVar6 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  pVVar4 = this->plan->points;
  local_1c.x = pVVar4[this->planPoint].x;
  local_1c.z = pVVar4[this->planPoint].z;
  fVar2 = *pfVar6;
  fVar3 = pfVar6[2];
  local_1c.y = 0.0;
  local_10 = local_1c.x;
  local_c = local_1c.z;
  if (this->switchDist * this->switchDist <=
      (fVar3 - local_1c.z) * (fVar3 - local_1c.z) + (fVar2 - local_1c.x) * (fVar2 - local_1c.x)) {
LAB_0046bb1f:
    iVar7 = this->planPoint;
    if (0 < iVar7) {
      pVVar4 = this->plan->points;
      local_10 = pVVar4[iVar7 + -1].x;
      local_c = pVVar4[iVar7 + -1].z;
      if (0.0 <= (fVar3 - local_1c.z) * (local_1c.z - local_c) + -local_1c.y * local_1c.y +
                 (fVar2 - local_1c.x) * (local_1c.x - local_10)) goto LAB_0046bc3f;
    }
    if (((this->avoidObj == (GameObject *)0x0) ||
        (pfVar6 = (float *)(**(code **)(this->avoidObj->_padding_ + 0xc))(),
        fVar1 = this->avoidObj->collisionRadius,
        fVar1 * fVar1 <=
        (pfVar6[2] - local_1c.z) * (pfVar6[2] - local_1c.z) +
        (*pfVar6 - local_1c.x) * (*pfVar6 - local_1c.x))) &&
       (local_5 = OnBlocked(&local_1c), !(bool)local_5)) {
      pVVar4 = this->plan->points;
      local_10 = pVVar4[this->planPoint + 1].x;
      local_c = pVVar4[this->planPoint + 1].z;
      iVar7 = (**(code **)(this->me->_padding_ + 4))();
      bVar5 = IsStraightPlan(fVar2,fVar3,local_10,local_c,iVar7);
      if (bVar5) {
        pVVar4 = this->plan->points + this->planPoint;
        pVVar4->x = fVar2;
        local_5 = '\x01';
        pVVar4->z = fVar3;
      }
      if (local_5 == '\0') goto LAB_0046bc4a;
    }
  }
  else {
    iVar7 = (**(code **)(this->me->_padding_ + 4))();
    bVar5 = IsStraightPlan(fVar2,fVar3,local_1c.x,local_1c.z,iVar7);
    if (!bVar5) goto LAB_0046bb1f;
  }
LAB_0046bc3f:
  this->planPoint = this->planPoint + 1;
  this->fixPoint = this->planPoint;
LAB_0046bc4a:
  if (this->fixPoint == this->planPoint) {
    this->fixPoint = this->fixPoint + 1;
  }
  (**(code **)(this->_padding_ + 0x30))();
  return;
}
