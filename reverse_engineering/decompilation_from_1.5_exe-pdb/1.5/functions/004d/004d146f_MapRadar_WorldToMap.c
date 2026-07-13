/*
 * Entry: 004d146f
 * Name: MapRadar::WorldToMap
 * Namespace: MapRadar
 * Signature: tagPOINT WorldToMap(MapRadar * this, VECTOR_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagPOINT __thiscall MapRadar::WorldToMap(MapRadar *this,VECTOR_3D param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  long in_EDX;
  tagPOINT tVar4;
  float in_stack_00000010;
  undefined4 local_c;
  
  fVar3 = (float)Float2Int;
  iVar1 = (this->screenConst).y;
  fVar2 = this->screenScale;
  local_c = SUB84((double)(param_1.y * this->screenScale + (float)(this->screenConst).x + fVar3),0);
  *(undefined4 *)param_1.x = local_c;
  param_1.z = SUB84((double)(((float)iVar1 - in_stack_00000010 * fVar2) + fVar3),0);
  *(float *)((int)param_1.x + 4) = param_1.z;
  tVar4.y = in_EDX;
  tVar4.x = (long)param_1.x;
  return tVar4;
}
