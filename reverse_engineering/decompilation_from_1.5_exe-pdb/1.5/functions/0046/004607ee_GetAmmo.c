/*
 * Entry: 004607ee
 * Name: GetAmmo
 * Namespace: Global
 * Signature: float GetAmmo(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetAmmo(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return 0.0;
  }
  return pGVar1->ammoRatio;
}
