/*
 * Entry: 005b9ca9
 * Name: findlocal
 * Namespace: Global
 * Signature: char * findlocal(lua_State * param_1, CallInfo * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl findlocal(lua_State *param_1,CallInfo *param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  int unaff_EBX;
  int *unaff_ESI;
  lua_State *unaff_EDI;
  Proto *pPVar3;
  CallInfo *unaff_retaddr;
  
  if ((((int *)unaff_ESI[1])[2] == 6) &&
     (iVar1 = *(int *)unaff_ESI[1], *(char *)(iVar1 + 6) == '\0')) {
    pPVar3 = *(Proto **)(iVar1 + 0x10);
  }
  else {
    pPVar3 = (Proto *)0x0;
  }
  if (pPVar3 != (Proto *)0x0) {
    iVar1 = currentpc(unaff_EDI,unaff_retaddr);
    pcVar2 = luaF_getlocalname(pPVar3,(int)param_1,iVar1);
    if (pcVar2 != (char *)0x0) {
      return pcVar2;
    }
  }
  if (unaff_ESI == *(int **)(unaff_EBX + 0x14)) {
    iVar1 = *(int *)(unaff_EBX + 8);
  }
  else {
    iVar1 = unaff_ESI[7];
  }
  if (((int)param_1 <= iVar1 - *unaff_ESI >> 4) && (0 < (int)param_1)) {
    return "(*temporary)";
  }
  return (char *)0x0;
}
