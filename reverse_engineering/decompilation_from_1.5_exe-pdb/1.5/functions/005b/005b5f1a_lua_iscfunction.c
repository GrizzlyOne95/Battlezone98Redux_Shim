/*
 * Entry: 005b5f1a
 * Name: lua_iscfunction
 * Namespace: Global
 * Signature: int lua_iscfunction(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_iscfunction(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if ((plVar1->tt == 6) && (*(char *)((plVar1->value).b + 6) != '\0')) {
    return 1;
  }
  return 0;
}
