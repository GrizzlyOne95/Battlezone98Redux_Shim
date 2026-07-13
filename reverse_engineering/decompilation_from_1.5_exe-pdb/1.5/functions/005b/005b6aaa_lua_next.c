/*
 * Entry: 005b6aaa
 * Name: lua_next
 * Namespace: Global
 * Signature: int lua_next(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_next(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  int iVar2;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  iVar2 = luaH_next(param_1,&((plVar1->value).gc)->h,param_1->top + -1);
  if (iVar2 != 0) {
    param_1->top = param_1->top + 1;
    return iVar2;
  }
  param_1->top = param_1->top + -1;
  return 0;
}
