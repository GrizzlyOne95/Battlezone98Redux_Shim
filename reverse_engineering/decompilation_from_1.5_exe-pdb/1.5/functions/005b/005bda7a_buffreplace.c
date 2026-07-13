/*
 * Entry: 005bda7a
 * Name: buffreplace
 * Namespace: Global
 * Signature: void buffreplace(LexState * param_1, char param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl buffreplace(LexState *param_1,char param_2,char param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  
  iVar2 = (*(int **)(in_EAX + 0x3c))[1];
  iVar1 = **(int **)(in_EAX + 0x3c);
  while (iVar2 != 0) {
    iVar2 = iVar2 + -1;
    if (*(char *)(iVar1 + iVar2) == (char)param_1) {
      *(char *)(iVar1 + iVar2) = param_2;
    }
  }
  return;
}
