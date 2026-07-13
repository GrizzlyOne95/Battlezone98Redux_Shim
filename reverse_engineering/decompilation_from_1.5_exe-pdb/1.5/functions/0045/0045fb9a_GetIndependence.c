/*
 * Entry: 0045fb9a
 * Name: GetIndependence
 * Namespace: Global
 * Signature: int GetIndependence(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetIndependence(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if ((pGVar1 != (GameObject *)0x0) && (pGVar1->aiProcess != (AiProcess *)0x0)) {
    return pGVar1->aiProcess[1]._padding_;
  }
  return 0;
}
