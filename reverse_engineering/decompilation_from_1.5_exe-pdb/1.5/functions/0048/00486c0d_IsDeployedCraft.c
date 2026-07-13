/*
 * Entry: 00486c0d
 * Name: IsDeployedCraft
 * Namespace: Global
 * Signature: bool IsDeployedCraft(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsDeployedCraft(_OBJ76 *param_1)

{
  char cVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  p_Var2 = obj_get_root(param_1);
  iVar3 = IsCraft(p_Var2);
  if (iVar3 == 0) {
    return false;
  }
  cVar1 = (**(code **)(*(int *)p_Var2->gameObj + 0x68))();
  return cVar1 == '\0';
}
