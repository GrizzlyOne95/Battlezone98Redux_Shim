/*
 * Entry: 005b9c91
 * Name: getluaproto
 * Namespace: Global
 * Signature: Proto * getluaproto(CallInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Proto * __cdecl getluaproto(CallInfo *param_1)

{
  int iVar1;
  int in_EAX;
  
  if (((*(int **)(in_EAX + 4))[2] == 6) &&
     (iVar1 = **(int **)(in_EAX + 4), *(char *)(iVar1 + 6) == '\0')) {
    return *(Proto **)(iVar1 + 0x10);
  }
  return (Proto *)0x0;
}
