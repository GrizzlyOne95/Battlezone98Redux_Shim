/*
 * Entry: 00403347
 * Name: AiPath::SetPoints
 * Namespace: AiPath
 * Signature: void SetPoints(AiPath * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiPath::SetPoints(AiPath *this,int param_1)

{
  VECTOR_2D *pVVar1;
  int iVar2;
  int iVar3;
  
  pVVar1 = operator_new__(-(uint)((int)((ulonglong)(uint)param_1 * 8 >> 0x20) != 0) |
                          (uint)((ulonglong)(uint)param_1 * 8));
  if (param_1 < this->pointCount) {
    this->pointCount = param_1;
  }
  iVar2 = 0;
  iVar3 = iVar2;
  if (0 < this->pointCount) {
    do {
      pVVar1[iVar3].x = this->points[iVar3].x;
      iVar2 = iVar3 + 1;
      pVVar1[iVar3].z = this->points[iVar3].z;
      iVar3 = iVar2;
    } while (iVar2 < this->pointCount);
  }
  operator_delete__(this->points);
  this->points = pVVar1;
  this->pointCount = param_1;
  if (iVar2 < param_1) {
    do {
      this->points[iVar2].x = 0.0;
      this->points[iVar2].z = 0.0;
      iVar2 = iVar2 + 1;
    } while (iVar2 < this->pointCount);
  }
  return;
}
