/*
 * Entry: 00460890
 * Name: GetLastEnemyShot
 * Namespace: Global
 * Signature: float GetLastEnemyShot(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetLastEnemyShot(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return -1e+30;
  }
  return pGVar1->enemyShot;
}
