/*
 * Entry: 005b9d4b
 * Name: lua_setlocal
 * Namespace: Global
 * Signature: char * lua_setlocal(lua_State * param_1, lua_Debug * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_setlocal(lua_State *param_1,lua_Debug *param_2,int param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  CallInfo *pCVar3;
  lua_TValue *plVar4;
  char *pcVar5;
  int unaff_ESI;
  CallInfo *unaff_EDI;
  
  iVar2 = param_2->i_ci;
  pCVar3 = param_1->base_ci;
  pcVar5 = findlocal((lua_State *)param_3,unaff_EDI,unaff_ESI);
  if (pcVar5 != (char *)0x0) {
    plVar4 = param_1->top;
    plVar1 = pCVar3[iVar2].base + param_3 + -1;
    (plVar1->value).gc = plVar4[-1].value.gc;
    *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)((int)&plVar4[-1].value + 4);
    plVar1->tt = plVar4[-1].tt;
  }
  param_1->top = param_1->top + -1;
  return pcVar5;
}
