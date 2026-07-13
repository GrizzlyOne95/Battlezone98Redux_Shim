/*
 * Entry: 00460659
 * Name: HopOut
 * Namespace: Global
 * Signature: void HopOut(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HopOut(int param_1)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    p_Var2 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
    iVar3 = IsCraft(p_Var2);
    if (iVar3 != 0) {
      *(undefined4 *)(pGVar1[1]._padding_ + 0xe4) = 1;
    }
  }
  return;
}
