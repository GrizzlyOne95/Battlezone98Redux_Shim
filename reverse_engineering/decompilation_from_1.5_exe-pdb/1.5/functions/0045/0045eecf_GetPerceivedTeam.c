/*
 * Entry: 0045eecf
 * Name: GetPerceivedTeam
 * Namespace: Global
 * Signature: int GetPerceivedTeam(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPerceivedTeam(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return 0;
  }
  return pGVar1->perceivedTeam;
}
