/*
 * Entry: 005b9d0b
 * Name: lua_getlocal
 * Namespace: Global
 * Signature: char * lua_getlocal(lua_State * param_1, lua_Debug * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_getlocal(lua_State *param_1,lua_Debug *param_2,int param_3)

{
  int iVar1;
  CallInfo *pCVar2;
  char *pcVar3;
  int unaff_ESI;
  CallInfo *unaff_EDI;
  
  iVar1 = param_2->i_ci;
  pCVar2 = param_1->base_ci;
  pcVar3 = findlocal((lua_State *)param_3,unaff_EDI,unaff_ESI);
  if (pcVar3 != (char *)0x0) {
    luaA_pushobject(param_1,pCVar2[iVar1].base + param_3 + -1);
  }
  return pcVar3;
}
