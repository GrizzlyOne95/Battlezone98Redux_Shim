/*
 * Entry: 0046075b
 * Name: GetCurHealth
 * Namespace: Global
 * Signature: float GetCurHealth(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetCurHealth(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return -1234.0;
  }
  return pGVar1->curHealth;
}
