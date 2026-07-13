/*
 * Entry: 00460806
 * Name: GetCurAmmo
 * Namespace: Global
 * Signature: long GetCurAmmo(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetCurAmmo(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return -0x4d2;
  }
  return pGVar1->curAmmo ^ 0x33333333;
}
