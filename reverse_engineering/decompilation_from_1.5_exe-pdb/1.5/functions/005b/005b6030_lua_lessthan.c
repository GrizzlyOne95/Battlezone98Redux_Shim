/*
 * Entry: 005b6030
 * Name: lua_lessthan
 * Namespace: Global
 * Signature: int lua_lessthan(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_lessthan(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  int unaff_EBP;
  lua_State *unaff_ESI;
  
  plVar1 = index2adr(unaff_ESI,unaff_EBP);
  plVar2 = index2adr(unaff_ESI,unaff_EBP);
  if ((plVar1 == &luaO_nilobject_) || (plVar2 == &luaO_nilobject_)) {
    iVar3 = 0;
  }
  else {
    iVar3 = luaV_lessthan(param_1,plVar1,plVar2);
  }
  return iVar3;
}
