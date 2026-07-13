/*
 * Entry: 00507fc3
 * Name: AI_FSMClose
 * Namespace: Global
 * Signature: void AI_FSMClose(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_FSMClose(void)

{
  FSM_ENTRY *pFVar1;
  FSM_ENTRY *pFVar2;
  int iVar3;
  
  pFVar1 = fsm;
  do {
    iVar3 = 3;
    pFVar2 = pFVar1;
    do {
      if (pFVar2->filename[0] != (char *)0x0) {
        free(pFVar2->filename[0]);
        pFVar2->filename[0] = (char *)0x0;
      }
      pFVar2 = (FSM_ENTRY *)(pFVar2->filename + 1);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    pFVar1 = pFVar1 + 1;
  } while ((int)pFVar1 < 0xc252d0);
  return;
}
