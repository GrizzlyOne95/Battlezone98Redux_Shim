/*
 * Entry: 0045ce09
 * Name: FindBase
 * Namespace: Global
 * Signature: GameObject * FindBase(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl FindBase(GameObject *param_1)

{
  Team *this;
  int in_EAX;
  GameObject *pGVar1;
  int iVar2;
  
  this = *(Team **)(in_EAX + 0x170);
  pGVar1 = Team::GetSlot(this,1);
  if (((pGVar1 == (GameObject *)0x0) &&
      (pGVar1 = Team::GetSlot(this,2), pGVar1 == (GameObject *)0x0)) &&
     (pGVar1 = Team::GetSlot(this,3), pGVar1 == (GameObject *)0x0)) {
    iVar2 = 0xf;
    do {
      pGVar1 = Team::GetSlot(this,iVar2);
      if (pGVar1 != (GameObject *)0x0) {
        return pGVar1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x19);
    iVar2 = 5;
    do {
      pGVar1 = Team::GetSlot(this,iVar2);
      if (pGVar1 != (GameObject *)0x0) {
        return pGVar1;
      }
      iVar2 = iVar2 + 1;
      pGVar1 = (GameObject *)0x0;
    } while (iVar2 < 0xf);
  }
  return pGVar1;
}
