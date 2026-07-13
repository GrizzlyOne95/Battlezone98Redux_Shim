/*
 * Entry: 004d14ac
 * Name: MapRadar::MapToWorld
 * Namespace: MapRadar
 * Signature: VECTOR_2D MapToWorld(MapRadar * this, tagPOINT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_2D __thiscall MapRadar::MapToWorld(MapRadar *this,tagPOINT param_1)

{
  int iVar1;
  float fVar2;
  float in_EDX;
  VECTOR_2D VVar3;
  int in_stack_0000000c;
  
  fVar2 = 1.0 / this->screenScale;
  iVar1 = (this->screenConst).y;
  *(float *)param_1.x = (float)(param_1.y - (this->screenConst).x) * fVar2;
  *(float *)(param_1.x + 4) = fVar2 * (float)(iVar1 - in_stack_0000000c);
  VVar3.z = in_EDX;
  VVar3.x = (float)param_1.x;
  return VVar3;
}
