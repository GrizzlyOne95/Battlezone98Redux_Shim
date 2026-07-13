/*
 * Entry: 0045eeb8
 * Name: GetTeamNum
 * Namespace: Global
 * Signature: int GetTeamNum(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTeamNum(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x0045eecc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar2 = (**(code **)(pGVar1->_padding_ + 4))();
  return iVar2;
}
