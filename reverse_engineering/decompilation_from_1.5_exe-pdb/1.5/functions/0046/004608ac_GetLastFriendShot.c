/*
 * Entry: 004608ac
 * Name: GetLastFriendShot
 * Namespace: Global
 * Signature: float GetLastFriendShot(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetLastFriendShot(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return -1e+30;
  }
  return pGVar1->friendShot;
}
