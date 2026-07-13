/*
 * Entry: 005b5fe4
 * Name: lua_equal
 * Namespace: Global
 * Signature: int lua_equal(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_equal(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  int unaff_EBP;
  lua_State *unaff_ESI;
  
  plVar1 = index2adr(unaff_ESI,unaff_EBP);
  plVar2 = index2adr(unaff_ESI,unaff_EBP);
  if ((((plVar1 != &luaO_nilobject_) && (plVar2 != &luaO_nilobject_)) && (plVar1->tt == plVar2->tt))
     && (iVar3 = luaV_equalval(param_1,plVar1,plVar2), iVar3 != 0)) {
    return 1;
  }
  return 0;
}
