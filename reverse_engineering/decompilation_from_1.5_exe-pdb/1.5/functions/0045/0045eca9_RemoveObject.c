/*
 * Entry: 0045eca9
 * Name: RemoveObject
 * Namespace: Global
 * Signature: void RemoveObject(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RemoveObject(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0045ecbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(pGVar1->_padding_ + 0x10))();
    return;
  }
  return;
}
