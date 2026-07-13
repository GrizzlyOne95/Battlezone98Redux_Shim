/*
 * Entry: 0040340f
 * Name: AiPath::GetLength
 * Namespace: AiPath
 * Signature: float GetLength(AiPath * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall AiPath::GetLength(AiPath *this)

{
  int iVar1;
  VECTOR_2D *pVVar2;
  VECTOR_2D *pVVar3;
  VECTOR_2D VVar4;
  VECTOR_2D local_10;
  float local_8;
  
  local_8 = 0.0;
  if (1 < this->pointCount) {
    pVVar3 = this->points;
    iVar1 = this->pointCount + -1;
    pVVar2 = pVVar3;
    do {
      pVVar2 = pVVar2 + 1;
      VVar4 = Vec2D_Subtract(*pVVar3,*pVVar2);
      local_10.z = VVar4.z;
      pVVar3 = pVVar3 + 1;
      iVar1 = iVar1 + -1;
      local_8 = SQRT(local_10.z * local_10.z + local_10.x * local_10.x) + local_8;
      local_10 = VVar4;
    } while (iVar1 != 0);
  }
  return local_8;
}
