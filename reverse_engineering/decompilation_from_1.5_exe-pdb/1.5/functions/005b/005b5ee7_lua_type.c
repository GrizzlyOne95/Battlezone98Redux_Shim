/*
 * Entry: 005b5ee7
 * Name: lua_type
 * Namespace: Global
 * Signature: int lua_type(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_type(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if (plVar1 == &luaO_nilobject_) {
    return -1;
  }
  return plVar1->tt;
}
