/*
 * Entry: 005b6bbf
 * Name: aux_upvalue
 * Namespace: Global
 * Signature: char * aux_upvalue(lua_TValue * param_1, int param_2, lua_TValue * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl aux_upvalue(lua_TValue *param_1,int param_2,lua_TValue **param_3)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  int *in_ECX;
  int *unaff_ESI;
  
  if (in_ECX[2] == 6) {
    iVar1 = *in_ECX;
    if (*(char *)(iVar1 + 6) == '\0') {
      iVar2 = *(int *)(iVar1 + 0x10);
      if ((0 < in_EAX) && (in_EAX <= *(int *)(iVar2 + 0x24))) {
        *unaff_ESI = *(int *)(*(int *)(iVar1 + 0x10 + in_EAX * 4) + 8);
        return (char *)(*(int *)(*(int *)(iVar2 + 0x1c) + -4 + in_EAX * 4) + 0x10);
      }
    }
    else if ((0 < in_EAX) && (in_EAX <= (int)(uint)*(byte *)(iVar1 + 7))) {
      *unaff_ESI = in_EAX * 0x10 + 8 + iVar1;
      return "";
    }
  }
  return (char *)0x0;
}
