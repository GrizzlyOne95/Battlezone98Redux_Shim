/*
 * Entry: 0054747c
 * Name: DEBUG_monoMessage
 * Namespace: Global
 * Signature: void DEBUG_monoMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_monoMessage(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = 0;
  if (0 < (int)pcVar2 - (int)(param_1 + 1)) {
    do {
      DEBUG_monoLine(param_1 + iVar3);
      iVar3 = iVar3 + 0x50;
    } while (iVar3 < (int)pcVar2 - (int)(param_1 + 1));
  }
  return;
}
