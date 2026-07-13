/*
 * Entry: 004b1d06
 * Name: Team::Init
 * Namespace: Team
 * Signature: void Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team::Init(void)

{
  void *pvVar1;
  Team *pTVar2;
  int iVar3;
  int iVar4;
  Team **ppTVar5;
  undefined4 auStack_30 [10];
  int local_8;
  
  local_8 = rand();
  local_8 = local_8 % 10;
  if (local_8 < 3) {
    local_8 = 3;
  }
  iVar4 = 0;
  if (0 < local_8) {
    do {
      pvVar1 = malloc(0x40);
      auStack_30[iVar4] = pvVar1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < local_8);
  }
  iVar4 = 0;
  ppTVar5 = teamList;
  do {
    pTVar2 = operator_new(0x180);
    *ppTVar5 = pTVar2;
    iVar3 = 0;
    do {
      *(undefined4 *)((int)(*ppTVar5)->teamSlot + iVar3) = 0;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x168);
    (*ppTVar5)->curScrap = 0x33333333;
    (*ppTVar5)->maxScrap = 0;
    (*ppTVar5)->curPilot = 0;
    (*ppTVar5)->maxPilot = 0;
    (*ppTVar5)->dwAllies = 1 << ((byte)iVar4 & 0x1f) | 1;
    (*ppTVar5)->teamNumber = iVar4;
    ppTVar5 = ppTVar5 + 1;
    iVar4 = iVar4 + 1;
  } while ((int)ppTVar5 < 0xb0ce88);
  iVar4 = 0;
  if (0 < local_8) {
    do {
      free((void *)auStack_30[iVar4]);
      iVar4 = iVar4 + 1;
    } while (iVar4 < local_8);
  }
  return;
}
