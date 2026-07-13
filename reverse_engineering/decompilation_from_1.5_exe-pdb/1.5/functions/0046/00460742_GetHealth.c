/*
 * Entry: 00460742
 * Name: GetHealth
 * Namespace: Global
 * Signature: float GetHealth(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetHealth(int param_1)

{
  GameObject *pGVar1;
  float10 fVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return 0.0;
  }
                    /* WARNING: Could not recover jumptable at 0x00460758. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  fVar2 = (float10)(**(code **)(pGVar1->_padding_ + 0x1c))();
  return (float)fVar2;
}
