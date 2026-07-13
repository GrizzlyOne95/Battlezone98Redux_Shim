/*
 * Entry: 00460826
 * Name: GetMaxAmmo
 * Namespace: Global
 * Signature: long GetMaxAmmo(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetMaxAmmo(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return -0x4d2;
  }
  return pGVar1->maxAmmo ^ 0x33333333;
}
