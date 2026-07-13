/*
 * Entry: 0046068f
 * Name: KillPilot
 * Namespace: Global
 * Signature: void KillPilot(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl KillPilot(int param_1)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    p_Var2 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
    iVar3 = IsCraft(p_Var2);
    if (iVar3 != 0) {
                    /* WARNING: Could not recover jumptable at 0x004606b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(pGVar1->_padding_ + 0x74))();
      return;
    }
  }
  return;
}
