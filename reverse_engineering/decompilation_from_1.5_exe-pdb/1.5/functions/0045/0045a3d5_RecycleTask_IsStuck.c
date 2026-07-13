/*
 * Entry: 0045a3d5
 * Name: RecycleTask::IsStuck
 * Namespace: RecycleTask
 * Signature: bool IsStuck(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecycleTask::IsStuck(RecycleTask *this)

{
  float fVar1;
  bool bVar2;
  VECTOR_3D *pVVar3;
  float *pfVar4;
  float fVar5;
  
  pVVar3 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  bVar2 = OnBlocked(pVVar3);
  if (bVar2) {
    return true;
  }
  fVar5 = Get_TimeLocal();
  if (fVar5 < this->nextStuck + EXTRA_STUCK_TIME) {
    return false;
  }
  pfVar4 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  fVar5 = *pfVar4 - (this->lastStuck).x;
  fVar1 = pfVar4[2] - (this->lastStuck).z;
  CleanStuck(this);
  return fVar1 * fVar1 + fVar5 * fVar5 < 25.0;
}
