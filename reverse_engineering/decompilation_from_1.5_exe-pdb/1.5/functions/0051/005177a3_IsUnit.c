/*
 * Entry: 005177a3
 * Name: IsUnit
 * Namespace: Global
 * Signature: bool IsUnit(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsUnit(GameObject *param_1)

{
  bool bVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  int *piVar4;
  
  piVar4 = &param_1->_padding_;
  p_Var2 = (_OBJ76 *)(**(code **)(*piVar4 + 0x30))();
  iVar3 = IsCraft(p_Var2);
  if (iVar3 != 0) {
    iVar3 = (**(code **)*piVar4)();
    bVar1 = BuildingVehicle(*(ulong *)(iVar3 + 0x20));
    if (!bVar1) {
      iVar3 = (**(code **)*piVar4)();
      if (*(int *)(iVar3 + 0x20) != 0x54555252) {
        iVar3 = (**(code **)(*piVar4 + 0x2c))();
        return iVar3 != 0;
      }
    }
  }
  return false;
}
