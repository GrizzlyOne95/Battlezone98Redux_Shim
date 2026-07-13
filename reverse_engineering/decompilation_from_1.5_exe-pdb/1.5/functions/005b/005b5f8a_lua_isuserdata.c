/*
 * Entry: 005b5f8a
 * Name: lua_isuserdata
 * Namespace: Global
 * Signature: int lua_isuserdata(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_isuserdata(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if ((plVar1->tt != 7) && (plVar1->tt != 2)) {
    return 0;
  }
  return 1;
}
