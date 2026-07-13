/*
 * Entry: 00507fa5
 * Name: AI_FSMInit
 * Namespace: Global
 * Signature: void AI_FSMInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_FSMInit(void)

{
  char **ppcVar1;
  FSM_ENTRY *pFVar2;
  
  pFVar2 = fsm;
  do {
    pFVar2->variation = 0;
    pFVar2->filename[0] = (char *)0x0;
    ppcVar1 = pFVar2->filename;
    pFVar2->filename[1] = (char *)0x0;
    pFVar2 = pFVar2 + 1;
    ppcVar1[2] = (char *)0x0;
  } while ((int)pFVar2 < 0xc252d0);
  return;
}
