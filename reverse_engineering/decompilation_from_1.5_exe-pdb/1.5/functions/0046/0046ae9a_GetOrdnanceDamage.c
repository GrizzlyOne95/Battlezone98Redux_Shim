/*
 * Entry: 0046ae9a
 * Name: GetOrdnanceDamage
 * Namespace: Global
 * Signature: float GetOrdnanceDamage(GameObject * param_1, OrdnanceClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetOrdnanceDamage(GameObject *param_1,OrdnanceClass *param_2)

{
  int in_EAX;
  _OBJ76 *p_Var1;
  int iVar2;
  int unaff_ESI;
  undefined4 local_8;
  
  if (unaff_ESI == 0) {
    return 0.0;
  }
  local_8 = *(float *)(unaff_ESI + 0x54);
  if (*(int *)(unaff_ESI + 0xc) == 0x54524754) {
    local_8 = 1400.0;
  }
  if (in_EAX == 0) {
    iVar2 = *(int *)(unaff_ESI + 0x3c);
  }
  else {
    p_Var1 = (_OBJ76 *)(**(code **)(*(int *)(in_EAX + 0x20) + 0x30))();
    iVar2 = IsBuilding(p_Var1);
    if (iVar2 == 0) {
      iVar2 = *(int *)(unaff_ESI + 0x40);
    }
    else {
      iVar2 = *(int *)(unaff_ESI + 0x44);
    }
  }
  if (iVar2 != 0) {
    local_8 = *(float *)(iVar2 + 0x54) + local_8;
  }
  return local_8;
}
