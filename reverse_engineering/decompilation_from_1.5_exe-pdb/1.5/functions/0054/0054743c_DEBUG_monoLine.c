/*
 * Entry: 0054743c
 * Name: DEBUG_monoLine
 * Namespace: Global
 * Signature: void DEBUG_monoLine(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_monoLine(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar4 = &DAT_000b0f00;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(param_1 + 1);
  if (0x50 < iVar3) {
    iVar3 = 0x50;
  }
  DEBUG_monoScroll();
  DEBUG_monoClearLine();
  if (0 < iVar3) {
    do {
      *pcVar4 = *param_1;
      param_1 = param_1 + 1;
      pcVar4 = pcVar4 + 2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}
