/*
 * Entry: 005b60d5
 * Name: lua_toboolean
 * Namespace: Global
 * Signature: int lua_toboolean(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_toboolean(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if ((plVar1->tt != 0) && ((plVar1->tt != 1 || ((plVar1->value).gc != (GCObject *)0x0)))) {
    return 1;
  }
  return 0;
}
