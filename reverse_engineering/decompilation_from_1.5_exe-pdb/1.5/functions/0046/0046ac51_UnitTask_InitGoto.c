/*
 * Entry: 0046ac51
 * Name: UnitTask::InitGoto
 * Namespace: UnitTask
 * Signature: void InitGoto(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::InitGoto(UnitTask *this)

{
  VECTOR_2D *pVVar1;
  float *pfVar2;
  AiPath *pAVar3;
  float fVar4;
  
  fVar4 = Get_Time();
  this->nextStuck = fVar4 + 5.0;
  pfVar2 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  (this->lastStuck).x = *pfVar2;
  (this->lastStuck).y = pfVar2[1];
  (this->lastStuck).z = pfVar2[2];
  if (this->plan == (AiPath *)0x0) {
    pAVar3 = FindPlan((GameObject *)this->me,(this->gotoPoint).x,(this->gotoPoint).z);
    this->plan = pAVar3;
  }
  this->planPoint = 0;
  this->fixPoint = 0;
  pVVar1 = this->plan->points + this->plan->pointCount + -1;
  (this->goalPoint).x = pVVar1->x;
  fVar4 = Terrain_FindFloor((double)pVVar1->x,(double)pVVar1->z);
  (this->goalPoint).y = fVar4;
  (this->goalPoint).z = pVVar1->z;
  return;
}
