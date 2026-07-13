/*
 * Entry: 00450620
 * Name: PathPlan::GetLength
 * Namespace: PathPlan
 * Signature: float GetLength(PathPlan * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall PathPlan::GetLength(PathPlan *this)

{
  PathPoint *pPVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  float local_14;
  
  fVar2 = 0.0;
  local_14 = 0.0;
  uVar5 = 1;
  if (1 < (uint)((int)(this->points)._Mylast - (int)(this->points)._Myfirst >> 4)) {
    iVar4 = 0x10;
    do {
      if ((uint)((int)(this->points)._Mylast - (int)(this->points)._Myfirst >> 4) <= uVar5) {
        _invalid_parameter_noinfo();
      }
      pfVar6 = (float *)((int)&(((this->points)._Myfirst)->point).x + iVar4);
      if ((uint)((int)(this->points)._Mylast - (int)(this->points)._Myfirst >> 4) <= uVar5 - 1) {
        _invalid_parameter_noinfo();
      }
      pPVar1 = (this->points)._Myfirst;
      fVar2 = *(float *)((int)&pPVar1[-1].point.x + iVar4) - *pfVar6;
      fVar3 = *(float *)((int)pPVar1 + iVar4 + -0xc) - pfVar6[1];
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x10;
      fVar2 = SQRT(fVar3 * fVar3 + fVar2 * fVar2) + local_14;
      local_14 = fVar2;
    } while (uVar5 < (uint)((int)(this->points)._Mylast - (int)(this->points)._Myfirst >> 4));
  }
  return fVar2;
}
