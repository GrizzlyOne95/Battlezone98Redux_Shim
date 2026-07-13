/*
 * Entry: 005c072b
 * Name: push_captures
 * Namespace: Global
 * Signature: int push_captures(MatchState * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl push_captures(MatchState *param_1,char *param_2,char *param_3)

{
  int in_EAX;
  char *unaff_EBX;
  int iVar1;
  char *unaff_ESI;
  int unaff_EDI;
  int iVar2;
  
  iVar1 = *(int *)(in_EAX + 0xc);
  iVar2 = 0;
  if ((iVar1 == 0) && (param_1 != (MatchState *)0x0)) {
    iVar1 = 1;
  }
  luaL_checkstack(*(lua_State **)(in_EAX + 8),iVar1,"too many captures");
  if (0 < iVar1) {
    do {
      push_onecapture(param_1,unaff_EDI,unaff_ESI,unaff_EBX);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return iVar1;
}
