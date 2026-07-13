/*
 * Entry: 004b971c
 * Name: test_for_cheat
 * Namespace: Global
 * Signature: int test_for_cheat(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl test_for_cheat(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(param_1 + 1);
  pcVar4 = cheat_buf + 0xe;
  pcVar2 = param_1 + iVar3 + -1;
  while( true ) {
    if (iVar3 == 0) {
      return 1;
    }
    if (*pcVar4 != *pcVar2) break;
    iVar3 = iVar3 + -1;
    pcVar2 = pcVar2 + -1;
    pcVar4 = pcVar4 + -1;
  }
  return 0;
}
