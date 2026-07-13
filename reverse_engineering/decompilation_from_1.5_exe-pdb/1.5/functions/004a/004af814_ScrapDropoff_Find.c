/*
 * Entry: 004af814
 * Name: ScrapDropoff_Find
 * Namespace: Global
 * Signature: int ScrapDropoff_Find(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ScrapDropoff_Find(GameObject *param_1)

{
  uint uVar1;
  DropoffInfo *pDVar2;
  
  if (param_1 != (GameObject *)0x0) {
    uVar1 = 0;
    pDVar2 = dropoffList;
    do {
      if (pDVar2->dropObj == (ScrapDropoff *)param_1) {
        pDVar2->refCount = pDVar2->refCount + 1;
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      pDVar2 = pDVar2 + 1;
    } while (uVar1 < 0x14);
  }
  return -1;
}
