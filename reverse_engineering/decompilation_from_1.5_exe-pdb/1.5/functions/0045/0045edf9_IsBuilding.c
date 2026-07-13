/*
 * Entry: 0045edf9
 * Name: IsBuilding
 * Namespace: Global
 * Signature: bool IsBuilding(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsBuilding(int param_1)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return false;
  }
  p_Var2 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
  iVar3 = IsBuilding(p_Var2);
  return iVar3 != 0;
}
