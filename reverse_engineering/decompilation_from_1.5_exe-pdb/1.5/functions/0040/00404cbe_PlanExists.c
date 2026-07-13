/*
 * Entry: 00404cbe
 * Name: PlanExists
 * Namespace: Global
 * Signature: bool PlanExists(float param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PlanExists(float param_1,float param_2,float param_3,float param_4)

{
  uint uVar1;
  PathPlan *pPVar2;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_1c.x = param_1;
  local_1c.y = 1000.0;
  local_1c.z = param_2;
  local_10.x = param_3;
  local_10.y = 1000.0;
  local_10.z = param_4;
  SetPathingType(0,0);
  pPVar2 = FindPath2(&local_1c,&local_10);
  if (pPVar2 != (PathPlan *)0x0) {
    uVar1 = pPVar2->flags;
    (**(code **)pPVar2->_padding_)(1);
    return uVar1 == 0;
  }
  return false;
}
