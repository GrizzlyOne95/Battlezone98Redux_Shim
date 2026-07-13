/*
 * Entry: 005ba526
 * Name: getfuncname
 * Namespace: Global
 * Signature: char * getfuncname(lua_State * param_1, CallInfo * param_2, char * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl getfuncname(lua_State *param_1,CallInfo *param_2,char **param_3)

{
  int in_EAX;
  int iVar1;
  char *pcVar2;
  uint uVar3;
  lua_State *unaff_EBX;
  CallInfo *unaff_retaddr;
  
  if (((((*(int **)(in_EAX + 4))[2] != 6) || (*(char *)(**(int **)(in_EAX + 4) + 6) != '\0')) ||
      (*(int *)(in_EAX + 0x14) < 1)) &&
     (((*(int **)(in_EAX + -0x14))[2] == 6 && (*(char *)(**(int **)(in_EAX + -0x14) + 6) == '\0'))))
  {
    iVar1 = currentpc(unaff_EBX,unaff_retaddr);
    uVar3 = *(uint *)(*(int *)(*(int *)(**(int **)(in_EAX + -0x14) + 0x10) + 0xc) + iVar1 * 4) &
            0x3f;
    if ((uVar3 == 0x1c) || ((uVar3 == 0x1d || (uVar3 == 0x21)))) {
      pcVar2 = getobjname(param_1,param_2,(int)unaff_EBX,(char **)unaff_retaddr);
      return pcVar2;
    }
  }
  return (char *)0x0;
}
