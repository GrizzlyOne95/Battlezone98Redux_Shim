/*
 * Entry: 0045fb7a
 * Name: SetIndependence
 * Namespace: Global
 * Signature: void SetIndependence(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetIndependence(int param_1,int param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if ((pGVar1 != (GameObject *)0x0) && (pGVar1->aiProcess != (AiProcess *)0x0)) {
    pGVar1->aiProcess[1]._padding_ = param_2;
  }
  return;
}
